#ifndef WIRE_CORPUS_HPP
#define WIRE_CORPUS_HPP

#include <functional>
#include <map>
#include <string>

namespace tests::binary::wire {
struct Encoded {
    std::string VirtualBare;
    std::string VirtualAuto;
    std::string TemplateBare;
    std::string TemplateAuto;

    // Decodes the table bytes (bare and auto) through both the virtual and the
    // template converters and compares the result to the corpus value with `==`.
    // Returns a description of the first failure, or an empty string on success.
    std::function<std::string(const std::string& bare, const std::string& auto_)> Verify;
};

const std::map<std::string, Encoded>& Entries();
}

#endif
