#pragma once

#include "abstract_converter.hpp"

namespace mikodev::binary
{
    class generator final
    {
    private:
        std::unordered_map<std::type_index, abstract_converter_interface_ptr> map;

    public:
        template <typename T>
        abstract_converter_ptr<T> get()
        {
            abstract_converter_interface_ptr v = map.at(typeid(T));
            abstract_converter_ptr<T> p = std::dynamic_pointer_cast<abstract_converter<T>>(v);
            return p;
        }

        template <typename Converter, typename ... TArgs, typename std::enable_if<std::is_base_of<abstract_converter_interface, Converter>::value>::type* = nullptr>
        void add()
        {
            abstract_converter_interface_ptr v = std::make_shared<Converter>(get<TArgs>() ...);
            std::type_index k = converter::get_template_argument(v);
            map.emplace(k, v);
        }

        template <template <typename ...> typename Converter, typename ... TArgs, typename std::enable_if<std::is_base_of<abstract_converter_interface, Converter<TArgs ...>>::value>::type* = nullptr>
        void add()
        {
            abstract_converter_interface_ptr v = std::make_shared<Converter<TArgs ...>>(get<TArgs>() ...);
            std::type_index k = converter::get_template_argument(v);
            map.emplace(k, v);
        }
    };
}
