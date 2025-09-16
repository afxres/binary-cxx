#ifndef BINARY_INTERNAL_GENERATORINVOKEFUNCTION_HPP
#define BINARY_INTERNAL_GENERATORINVOKEFUNCTION_HPP

#include "binary/IGenerator.hpp"
#include "binary/internal/Module.hpp"

namespace binary::internal {
template <typename T>
struct GeneratorInvokeHelper;

template <template <typename...> typename T, typename... E>
    requires std::same_as<T<E...>, std::remove_cv_t<T<E...>>> && (std::same_as<E, std::remove_cv_t<E>> && ...)
struct GeneratorInvokeHelper<T<E...>> {
    static auto Invoke(const IGenerator& generator) {
        return T{::binary::internal::GetConverter<E>(generator.GetConverter(typeid(E)))...};
    }
};
}

#endif
