//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: FontLibrary.cpp
//------------------------------------------------------------

#include "FontLibrary.hpp"
#include <fmt/format.h>
#include <stdexcept>

namespace KMLEngine {
    template<> FontLibrary* Singleton<FontLibrary>::_INSTANCE = nullptr;

    void FontLibrary::OnDisposing() {
        if(const auto error = FT_Done_FreeType(m_library); error) {
            throw std::runtime_error(fmt::format("{} failed: {}", "FT_Done_FreeType", FT_Error_String(error)));
        }

        m_library = nullptr;

        DetachSingleton();
    }

    void FontLibrary::Create() {
        AttachSingleton();

        if(const auto error = FT_Init_FreeType(&m_library); error) {
            throw std::runtime_error(fmt::format("{} failed: {}", "FT_Init_FreeType",  FT_Error_String(error)));
        }
    }
}
