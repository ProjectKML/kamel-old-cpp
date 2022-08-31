//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: FontLibrary.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_FONTLIBRARY_HPP
#define KMLENGINE_CLIENT_CORE_FONTLIBRARY_HPP

#pragma once

#include "../../../Common/Util/Traits/Singleton.hpp"
#include "../../../Common/Util/Traits/Disposable.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace KMLEngine {
    class FontLibrary final : public Singleton<FontLibrary>, public Disposable<FontLibrary>{
        friend Disposable<FontLibrary>;
    private:
        FT_Library m_library = nullptr;

        void OnDisposing();
    public:
        FontLibrary() = default;

        void Create();
        
        [[nodiscard]] KML_FORCEINLINE FT_Library GetHandle() const noexcept { return m_library; }
    };
}

#endif //KMLENGINE_CLIENT_CORE_FONTLIBRARY_HPP
