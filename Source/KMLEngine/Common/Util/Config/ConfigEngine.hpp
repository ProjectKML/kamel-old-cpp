//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ConfigEngine.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_CONFIG_CONFIGENGINE_HPP
#define KMLENGINE_COMMON_UTIL_CONFIG_CONFIGENGINE_HPP

#pragma once

#include <toml++/toml.h>

namespace KMLEngine {
    struct ConfigEngine {
        [[nodiscard]] static std::string_view GetName() noexcept {
            using namespace std::string_view_literals;
            return "Engine"sv;
        }

        struct {
            bool ShouldLogToFile;
        } Logger;

        void Serialize(toml::table& root) const;
        void Deserialize(const toml::table& root);

        void RestoreDefaults() noexcept;
    };
}

#endif //KMLENGINE_COMMON_UTIL_CONFIG_CONFIGENGINE_HPP
