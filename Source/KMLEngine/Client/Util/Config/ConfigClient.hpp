//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ConfigClient.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_UTIL_CONFIG_CONFIGCLIENT_HPP
#define KMLENGINE_CLIENT_UTIL_CONFIG_CONFIGCLIENT_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include <toml++/toml.h>

namespace KMLEngine {
    struct ConfigClient {
        [[nodiscard]] static std::string_view GetName() noexcept {
            using namespace std::string_view_literals;
            return "Client"sv;
        }

        struct {
            u32 Width;
            u32 Height;
            bool Fullscreen;
        } Window;

        struct {
            u32 FrameLimit;
        } Timer;

        void Serialize(toml::table& root) const;
        void Deserialize(const toml::table& root);

        void RestoreDefaults() noexcept;
    };
}

#endif //KMLENGINE_CLIENT_UTIL_CONFIG_CONFIGCLIENT_HPP
