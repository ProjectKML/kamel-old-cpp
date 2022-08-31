//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ViewportSizeManager.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_VIEWPORTSIZEMANAGER_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_VIEWPORTSIZEMANAGER_HPP

#pragma once

#include "../../../../Common/Util/Math/Point.hpp"

namespace KMLEngine {
    class ViewportSizeManager {
    private:
        PointU32 m_size;
    public:
        ViewportSizeManager() = default;

        void Create() noexcept;
        bool Update() noexcept;

        [[nodiscard]] KML_FORCEINLINE u32 GetWidth() const noexcept { return m_size.X; }
        [[nodiscard]] KML_FORCEINLINE u32 GetHeight() const noexcept { return m_size.Y; }
        [[nodiscard]] KML_FORCEINLINE PointU32 GetSize() const noexcept { return m_size; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_VIEWPORTSIZEMANAGER_HPP
