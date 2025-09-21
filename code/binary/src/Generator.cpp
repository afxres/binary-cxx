#include "binary/Generator.hpp"

#include <format>

namespace binary {
void Generator::AddConverter(const std::shared_ptr<IConverter>& converter) {
    this->converters.emplace(converter->GetGenericArgument(), converter);
}

std::shared_ptr<IConverter> Generator::GetConverter(std::type_index type) const {
    const auto& converters = this->converters;
    const auto& iterator = converters.find(type);
    if (iterator != converters.end()) {
        return iterator->second;
    }
    throw std::invalid_argument(std::format("converter not found, argument type: {}", type.name()));
}
}
