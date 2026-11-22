#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Corpus.hpp"

#ifndef BINARY_WIRE_TESTS_FIXTURE
#define BINARY_WIRE_TESTS_FIXTURE "fixtures/wire.tsv"
#endif

namespace {
struct Row {
    std::string Name;
    std::string Bare;
    std::vector<std::string> AutoForms;
    std::string Langs;
};

// A length header is 1 byte below 128 and 4 bytes otherwise, and both widths are
// legal for any length, so the auto column may list several accepted forms
// separated by `|`. Producing any of them passes; producing anything else fails,
// with no decode fallback (see the comment in the C# repository's WireCheck).
std::vector<std::string> SplitForms(const std::string& cell) {
    std::vector<std::string> forms;
    std::stringstream stream(cell);
    std::string form;
    while (std::getline(stream, form, '|')) {
        forms.push_back(form);
    }
    return forms;
}

std::string JoinForms(const std::vector<std::string>& forms) {
    std::string result;
    for (const auto& form : forms) {
        if (!result.empty()) {
            result += '|';
        }
        result += form;
    }
    return result;
}

std::vector<Row> LoadRows(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::fprintf(stderr, "cannot open fixture: %s\n", path.c_str());
        std::exit(2);
    }
    std::vector<Row> rows;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty() || line.front() == '#') {
            continue;
        }
        std::vector<std::string> columns;
        std::stringstream stream(line);
        std::string column;
        while (std::getline(stream, column, '\t')) {
            columns.push_back(column);
        }
        if (columns.size() != 4) {
            std::fprintf(stderr, "expected 4 columns: %s\n", line.c_str());
            std::exit(2);
        }
        rows.push_back(Row{columns[0], columns[1], SplitForms(columns[2]), columns[3]});
    }
    return rows;
}

bool HasCxx(const std::string& langs) {
    std::stringstream stream(langs);
    std::string part;
    while (std::getline(stream, part, ',')) {
        if (part == "cxx") {
            return true;
        }
    }
    return false;
}

std::string Expand(const std::string& hex) {
    return hex == "-" ? std::string() : hex;
}

// Frames a payload with a 1 or 4 byte length header, `payload` being hex.
std::string Frame(size_t width, const std::string& payload) {
    char header[9] = {};
    auto length = static_cast<unsigned>(payload.size() / 2);
    if (width == 1) {
        std::snprintf(header, sizeof(header), "%02x", length);
    } else {
        std::snprintf(header, sizeof(header), "%08x", 0x80000000u | length);
    }
    return std::string(header) + payload;
}

// The width of the form's own length header, or 0 when it has none: a form only
// carries one when it ends with the bare payload. The extra length alone is not
// enough, because a tuple object writes its members' prefixes while adding nothing
// of its own (`tuple_i32_str` is `01000000 0161` against a 5 byte bare).
size_t HeaderWidth(const std::string& form, const std::string& payload) {
    if (payload.empty()) {
        return (form.size() == 2 || form.size() == 8) ? form.size() / 2 : 0;
    }
    if (form.size() <= payload.size()) {
        return 0;
    }
    auto width = (form.size() - payload.size()) / 2;
    if ((width != 1 && width != 4) || (payload.size() + width * 2 != form.size())) {
        return 0;
    }
    return form.compare(form.size() - payload.size(), payload.size(), payload) == 0 ? width : 0;
}

// Both header widths a reader has to accept, whether or not the table lists them.
// A decoder that only handles the width its own writer emits is a split decoder,
// and the table's 1 byte form hides that.
std::vector<std::string> DecodeForms(const Row& row) {
    auto payload = Expand(row.Bare);
    std::vector<std::string> forms;
    for (const auto& form : row.AutoForms) {
        if (HeaderWidth(Expand(form), payload) == 0) {
            forms.push_back(form);
            continue;
        }
        if (payload.size() / 2 < 128) {
            forms.push_back(Frame(1, payload));
        }
        forms.push_back(Frame(4, payload));
    }
    std::vector<std::string> unique;
    for (const auto& form : forms) {
        if (std::find(unique.begin(), unique.end(), form) == unique.end()) {
            unique.push_back(form);
        }
    }
    return unique;
}
}

int main(int argc, char** argv) {
    std::string path = argc > 1 ? argv[1] : BINARY_WIRE_TESTS_FIXTURE;
    auto rows = LoadRows(path);
    const auto& entries = tests::binary::wire::Entries();

    size_t checked = 0;
    size_t widened = 0;
    size_t skipped = 0;
    size_t failed = 0;
    auto report = [&failed](const std::string& name, const char* api, const char* column, const std::string& expected, const std::string& actual) {
        if (expected == actual) {
            return;
        }
        ++failed;
        std::fprintf(stderr, "FAIL %s [%s / %s]\n  table %s\n  actual %s\n", name.c_str(), api, column, expected.c_str(), actual.c_str());
    };

    for (const auto& row : rows) {
        if (!HasCxx(row.Langs)) {
            continue;
        }
        auto item = entries.find(row.Name);
        if (item == entries.end()) {
#if defined(BINARY_HAS_INT128)
            ++failed;
            std::fprintf(stderr, "FAIL %s: no C++ value for this row\n", row.Name.c_str());
#else
            // A platform without 128-bit integers has no corpus entry for those
            // rows, and that absence is capability, not a forgotten registration.
            ++skipped;
            std::fprintf(stderr, "SKIP %s: no C++ value on this platform\n", row.Name.c_str());
#endif
            continue;
        }
        ++checked;
        const auto& encoded = item->second;

        // Encode: byte-for-byte, no tolerance.
        report(row.Name, "virtual", "Encode", Expand(row.Bare), encoded.VirtualBare);
        report(row.Name, "template", "Encode", Expand(row.Bare), encoded.TemplateBare);

        // EncodeAuto: the table lists the legal header widths for this row, so the
        // produced bytes must equal one of them.
        auto reportAuto = [&failed](const std::string& name, const char* api, const std::vector<std::string>& forms, const std::string& actual) {
            if (std::find(forms.begin(), forms.end(), actual) != forms.end()) {
                return;
            }
            ++failed;
            std::fprintf(stderr, "FAIL %s [%s / EncodeAuto]\n  table %s\n  actual %s\n", name.c_str(), api, JoinForms(forms).c_str(), actual.c_str());
        };
        reportAuto(row.Name, "virtual", row.AutoForms, encoded.VirtualAuto);
        reportAuto(row.Name, "template", row.AutoForms, encoded.TemplateAuto);

        // Decode: every width of the header is an input, the corpus value is the
        // oracle. `Verify` decodes both bare and auto through both converters and
        // checks structural equality, which is the reverse of the encode direction.
        auto forms = DecodeForms(row);
        if (forms.size() > 1) {
            ++widened;
        }
        for (const auto& form : forms) {
            auto decodeError = encoded.Verify(row.Bare, form);
            if (!decodeError.empty()) {
                ++failed;
                std::fprintf(stderr, "FAIL %s [Decode / %s]\n  %s\n", row.Name.c_str(), form.c_str(), decodeError.c_str());
            }
        }
    }

    std::vector<std::string> unused;
    for (const auto& item : entries) {
        auto found = std::find_if(rows.begin(), rows.end(), [&item](const Row& row) {
            return row.Name == item.first && HasCxx(row.Langs);
        });
        if (found == rows.end()) {
            unused.push_back(item.first);
        }
    }
    for (const auto& name : unused) {
        ++failed;
        std::fprintf(stderr, "FAIL %s: C++ value without a row carrying `cxx`\n", name.c_str());
    }

    std::printf("%zu rows, %zu with cxx, %zu checked (%zu in both header widths), %zu skipped, %zu failed\n", rows.size(), checked, checked, widened, skipped, failed);
    return failed == 0 ? 0 : 1;
}
