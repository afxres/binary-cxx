#include <binary/components/NamedObject.hpp>
#include <binary/components/TupleObject.hpp>

#include <cstdint>
#include <string>

namespace tests::integration::SharedHeaderTests {
struct SharedIntent {
    int32_t X;
    int32_t Y;
};

struct SharedObject {
    int64_t Id;
    std::u8string Name;
};

BINARY_TUPLE_OBJECT_CONVERTER(SharedIntentTupleObjectConverter, SharedIntent) {
    BINARY_TUPLE_MEMBER(X);
    BINARY_TUPLE_MEMBER(Y);
}

BINARY_NAMED_OBJECT_CONVERTER(SharedObjectNamedObjectConverter, SharedObject) {
    BINARY_NAMED_MEMBER(Id);
    BINARY_NAMED_MEMBER(Name);
}
}
