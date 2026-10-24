#include <binary/components/NamedObjectConverter.hpp>
#include <binary/components/TupleObjectConverter.hpp>

#include <cstdint>
#include <string>
#include <tuple>

namespace tests::integration::SharedHeaderTests {
struct SharedIntent {
    int32_t X;
    int32_t Y;
};

struct SharedObject {
    int64_t Id;
    std::u8string Name;
};

struct SharedIntentSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::TupleMember{&SharedIntent::X},
        ::binary::components::TupleMember{&SharedIntent::Y},
    };
};

using SharedIntentTupleObjectConverter = ::binary::components::TupleObjectConverter<SharedIntent, SharedIntentSchema>;

struct SharedObjectSchema {
    static constexpr auto Members = std::tuple{
        ::binary::components::NamedMember{"Id", &SharedObject::Id},
        ::binary::components::NamedMember{"Name", &SharedObject::Name},
    };
};

using SharedObjectNamedObjectConverter = ::binary::components::NamedObjectConverter<SharedObject, SharedObjectSchema>;
}
