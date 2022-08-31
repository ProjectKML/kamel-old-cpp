//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderSettings.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_RENDERSETTINGS_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_RENDERSETTINGS_HPP

#pragma once

namespace KMLEngine {
    struct RenderSettings {
        bool MeshShading = false;

        RenderSettings() = default;
        RenderSettings(bool meshShading) noexcept : MeshShading(meshShading) {}

        [[nodiscard]] KML_FORCEINLINE bool operator ==(const RenderSettings& other) const noexcept {
            return MeshShading == other.MeshShading;
        }

        [[nodiscard]] KML_FORCEINLINE bool operator !=(const RenderSettings& other) const noexcept {
            return MeshShading != other.MeshShading;
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_RENDERSETTINGS_HPP