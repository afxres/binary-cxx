#pragma once

#include "converters/little_endian_converter.hpp"
#include "converters/string_converter.hpp"

namespace mikodev::binary {
class generator final {
private:
    using key_t = abstract_converter_interface_ptr;

    using map_t = std::unordered_map<std::type_index, key_t>;

    map_t map_;

    std::vector<key_t> create_predefined_converters__() {
        std::vector<key_t> vector = {};
        vector.push_back(std::make_shared<converters::string_converter>());
        vector.push_back(std::make_shared<converters::little_endian_converter<int8_t>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<int16_t>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<int32_t>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<int64_t>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<uint8_t>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<uint16_t>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<uint32_t>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<uint64_t>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<float>>());
        vector.push_back(std::make_shared<converters::little_endian_converter<double>>());
        return vector;
    }

public:
    generator() {
        map_t map = {};
        std::vector<key_t> converters = create_predefined_converters__();
        for (const key_t& i : converters)
            map.emplace(converter::get_template_argument(i), i);
        assert(map_.size() == 0);
        map_ = map;
    }

    template <typename T>
    abstract_converter_ptr<T> get() {
        key_t v = map_.at(typeid(T));
        abstract_converter_ptr<T> p = std::dynamic_pointer_cast<abstract_converter<T>>(v);
        return p;
    }

    template <
        typename Converter, typename... TArgs,
        typename std::enable_if<std::is_base_of<abstract_converter_interface, Converter>::value>::type* = nullptr>
    void add() {
        key_t v = std::make_shared<Converter>(get<TArgs>()...);
        std::type_index k = converter::get_template_argument(v);
        map_.emplace(k, v);
    }

    template <
        template <typename...>
        typename Converter,
        typename... TArgs,
        typename std::enable_if<std::is_base_of<abstract_converter_interface, Converter<TArgs...>>::value>::type* = nullptr>
    void add() {
        key_t v = std::make_shared<Converter<TArgs...>>(get<TArgs>()...);
        std::type_index k = converter::get_template_argument(v);
        map_.emplace(k, v);
    }
};
}
