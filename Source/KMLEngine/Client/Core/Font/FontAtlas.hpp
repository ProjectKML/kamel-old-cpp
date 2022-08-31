//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: FontAtlas.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_FONT_FONTATLAS_HPP
#define KMLENGINE_CLIENT_CORE_FONT_FONTATLAS_HPP

#pragma once

#include "FontLibrary.hpp"
#include "../../../Common/Util/STL/flat_hash_map.hpp"
#include "../../Util/Drawing/Bitmap.hpp"
#include <glm/glm.hpp>

namespace KMLEngine {
    class PackageLocation;

    class FontAtlas final : public Disposable<FontAtlas> {
        friend Disposable<FontAtlas>;
    public:
        class Exception final : public std::runtime_error {
        public:
            explicit Exception(const char* message) noexcept : std::runtime_error(message) { KML_ASSERT(message); }
            explicit Exception(const std::string& message) noexcept : std::runtime_error(message) {}
        };
        
        struct GlyphInfo {
            u32 Value;
            f32 XAdvance;
            f32 YAdvance;
            f32 Width;
            f32 Height;
            f32 OffsetX;
            f32 OffsetY;
            f32 TexCoordX;
            f32 TexCoordY;

            KML_FORCEINLINE GlyphInfo() = default;

            KML_FORCEINLINE GlyphInfo(u32 value, f32 xAdvance, f32 yAdvance, f32 width, f32 height,
                                      f32 offsetX,
                                      f32 offsetY, f32 texCoordX, f32 texCoordY) noexcept :
                Value(value), XAdvance(xAdvance), YAdvance(yAdvance), Width(width), Height(height),
                OffsetX(offsetX),
                OffsetY(offsetY), TexCoordX(texCoordX), TexCoordY(texCoordY) {
            }
        };

        struct Data {
            f32 Size;
            f32 LineSpacing;
            GlyphInfo* GlyphInfos;
            u32 GlyphCount;
        };

    private:
        FT_Face m_face = nullptr;
        u32 m_atlasWidth = 0;
        u32 m_atlasHeight = 0;
        u32 m_glyphHeight = 0;
        Bitmap<u8> m_bitmap;
        u32 m_size = 0;

        u32 m_preferredWidth = 0;

        kml_stl::flat_hash_map<u32, GlyphInfo> m_glyphMap;
        Data m_data = {};

        void PreLoadGlyph(FT_ULong ch, u32& currentAtlasWidth, u32& maxAtlasWidth, u32& maxGlyphHeight,
                          std::vector<glm::ivec2>& yData, u32& currentYHeight, u32& currentYOffset,
                          FT_GlyphSlot glyphSlot);

        void AddAllGlyphs(const std::vector<FT_ULong>& chars, u32 maxGlyphHeight,
                          const std::vector<glm::ivec2>& yData,
                          FT_GlyphSlot glyphSlot);

        void OnDisposing();

    public:
        void Load(FontLibrary& library, const PackageLocation& location, u32 fontSize, u32 faceIndex = 0);
        void UnloadBitmap() noexcept;

		[[nodiscard]] KML_FORCEINLINE const GlyphInfo* GetGlyph(u32 value) const noexcept {
            const auto iterator = m_glyphMap.find(value);
            if (iterator != m_glyphMap.end()) return &iterator->second;
            return nullptr;
        }

        [[nodiscard]] KML_FORCEINLINE const Bitmap<u8>& GetBitmap() const noexcept { return m_bitmap; }
        [[nodiscard]] KML_FORCEINLINE const kml_stl::flat_hash_map<u32, GlyphInfo>& GetGlyphMap() const noexcept { return m_glyphMap; }

		[[nodiscard]] KML_FORCEINLINE u32 GetSize() const noexcept { return m_size; }
		[[nodiscard]] KML_FORCEINLINE u32 GetGlyphHeight() const noexcept { return m_glyphHeight; }

		[[nodiscard]] KML_FORCEINLINE const Data* GetData() const noexcept { return &m_data; }
		[[nodiscard]] KML_FORCEINLINE Data* GetData() noexcept { return &m_data; }

		[[nodiscard]] KML_FORCEINLINE FT_Face GetHandle() noexcept { return m_face; }
    };

}

#endif //KMLENGINE_CLIENT_CORE_FONT_FONTATLAS_HPP
