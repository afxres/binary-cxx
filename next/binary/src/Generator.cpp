#include "binary/Generator.hpp"

namespace binary {
void Generator::AddConverter(std::shared_ptr<IConverter> converter) {
    this->converters.emplace(converter->GetGenericArgument(), converter);
}

std::shared_ptr<IConverter> Generator::GetConverter(std::type_index type) const {
    return this->converters.at(type);
}
}
