//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ConfigUtils.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_CONFIG_CONFIGUTILS_HPP
#define KMLENGINE_COMMON_UTIL_CONFIG_CONFIGUTILS_HPP

#pragma once

#include <toml++/toml.h>
#include <type_traits>

namespace KMLEngine::ConfigUtils {
    template<typename C>
    class HasRestoreDefaults {
    private:
        template<typename T>
        static constexpr auto TestInvoke(T*) -> typename std::is_same<decltype(std::declval<T>().RestoreDefaults()), void>::type;

        template<typename>
        static constexpr std::false_type TestInvoke(...);

        using Type = decltype(TestInvoke<C>(nullptr));
    public:
        static constexpr bool Value = Type::value;
    };
}

#endif //KMLENGINE_COMMON_UTIL_CONFIG_CONFIGUTILS_HPP
