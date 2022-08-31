//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: FontAtlas.cpp
//------------------------------------------------------------

#include "FontAtlas.hpp"
#include "../../../Common/Core/Package/PackageLocation.hpp"
#include <fmt/format.h>
#include <spdlog/spdlog.h>

namespace KMLEngine {
    static const u32 _ATLAS_PADDING_X = 1;
    static const u32 _ATLAS_PADDING_Y = 1;

    void FontAtlas::OnDisposing() {
        delete[] m_data.GlyphInfos;
        
        m_glyphMap.clear();
        if (m_bitmap.IsValid()) m_bitmap.Dispose();

        if (const auto error = FT_Done_Face(m_face); error) {
            throw Exception(fmt::format("Failed to dispose font face: {}", FT_Error_String(error)));
        }

        m_data = {};

        m_preferredWidth = 0;

        m_glyphHeight = 0;
        m_atlasHeight = 0;
        m_atlasWidth = 0;

        m_face = nullptr;
    }

    void FontAtlas::PreLoadGlyph(FT_ULong ch, u32& currentAtlasWidth, u32& maxAtlasWidth, u32& maxGlyphHeight,
                                 std::vector<glm::ivec2>& yData, u32& currentYHeight, u32& currentYOffset,
                                 FT_GlyphSlot glyphSlot) {

        auto error = FT_Load_Char(m_face, ch, FT_LOAD_DEFAULT);
        if (error) {
            spdlog::warn("Generating font atlas: Skipped char {}", ch);
            return;
        }

        error = FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
        if (error) {
            spdlog::warn("Generating font atlas: Skipped char {}", ch);
            return;
        }

        currentAtlasWidth += glyphSlot->bitmap.width + _ATLAS_PADDING_X;
        const auto currentHeight = glyphSlot->bitmap.rows;

        if (currentHeight > currentYHeight) currentYHeight = currentHeight;
        if (currentAtlasWidth > m_preferredWidth) {
            if (currentAtlasWidth > maxAtlasWidth) maxAtlasWidth = currentAtlasWidth;
            currentAtlasWidth = 0;
            currentYHeight += _ATLAS_PADDING_Y;

            yData.emplace_back(currentYHeight, currentYOffset);
            currentYOffset += currentYHeight;
            currentYHeight = 0;
        }

        if (currentHeight > maxGlyphHeight) {
            maxGlyphHeight = currentHeight;
        }
    }

    void FontAtlas::AddAllGlyphs(const std::vector<FT_ULong>& chars, u32 maxGlyphHeight,
                                 const std::vector<glm::ivec2>& yData, FT_GlyphSlot glyphSlot) {
        u32 offsetX = 0, indexY = 0;

        for(FT_ULong ch : chars) {
            auto error = FT_Load_Char(m_face, ch, FT_LOAD_DEFAULT);
            if (error) return;

            error = FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
            if (error) return;

            const auto glyphWidth = glyphSlot->bitmap.width;
            const auto glyphHeight = glyphSlot->bitmap.rows;

            const auto offsetY = yData[indexY].y;

            for (auto iz = 0; iz < glyphWidth; iz++) {
                for (auto iy = 0; iy < glyphHeight; iy++) {
                    const auto value = static_cast<u8>(glyphSlot->bitmap.buffer[iy * glyphWidth + iz]);

                    m_bitmap.SetPixel(offsetX + iz, offsetY + iy, value);
                }
            }

            m_glyphMap.emplace(std::piecewise_construct, std::make_tuple(ch), std::make_tuple(
                                   ch, static_cast<f32>(glyphSlot->advance.x >> 6),
                                   static_cast<f32>(glyphSlot->advance.y >> 6),
                                   static_cast<f32>(glyphWidth), static_cast<f32>(glyphHeight),
                                   static_cast<f32>(glyphSlot->bitmap_left),
                                   static_cast<f32>(glyphSlot->bitmap_top), offsetX,
                                   offsetY));

            offsetX += glyphWidth + _ATLAS_PADDING_X;
            if (offsetX > m_preferredWidth) {
                offsetX = 0;
                indexY++;
            }
        }
    }

    void FontAtlas::Load(FontLibrary& library, const PackageLocation& location, u32 fontSize, u32 faceIndex) {
        std::vector<byte> data;
        location.GetEntry(data);

        auto error = FT_New_Memory_Face(library.GetHandle(), data.data(), static_cast<FT_Long>(data.size()),
                                        faceIndex, &m_face);
        if (error) {
            throw Exception(fmt::format("Failed to load font from location {}: {}", location.ToString(), FT_Error_String(error)));
        }

        error = FT_Select_Charmap(m_face, FT_ENCODING_UNICODE);
        if (error) {
            throw Exception(fmt::format("Failed to select unicode char map: {}", FT_Error_String(error)));
        }

        error = FT_Set_Pixel_Sizes(m_face, 0, fontSize);
        if (error) {
            throw Exception(fmt::format("Failed to set font pixel sizes: {}", FT_Error_String(error)));
        }

        u32 currentAtlasWidth = 0, maxAtlasWidth = 0;
        m_glyphHeight = 0;
        const auto glyphSlot = m_face->glyph;

        m_preferredWidth = fontSize * 16;

        FT_UInt gIndex;

        std::vector<FT_ULong> charCodes;
        charCodes.reserve(256);

        auto charCode = FT_Get_First_Char(m_face, &gIndex);
        if (gIndex == 0) {
            throw Exception("Failed to create font atlas, first char is invalid");
        }

        std::vector<glm::ivec2> yData;
        yData.reserve(32);
        u32 tempYOffset = 0;
        u32 tempYHeight = 0;

        PreLoadGlyph(charCode, currentAtlasWidth, maxAtlasWidth, m_glyphHeight, yData, tempYHeight, tempYOffset,
                     glyphSlot);
        charCodes.push_back(charCode);

        while (gIndex != 0) {
            charCode = FT_Get_Next_Char(m_face, charCode, &gIndex);
            PreLoadGlyph(charCode, currentAtlasWidth, maxAtlasWidth, m_glyphHeight, yData, tempYHeight, tempYOffset,
                         glyphSlot);

            charCodes.push_back(charCode);
        }
        yData.emplace_back(tempYHeight, tempYOffset);

        const auto atlasWidth = maxAtlasWidth;

        const auto& lastYElement = yData.back();
        const auto atlasHeight = lastYElement.x + lastYElement.y;

        m_bitmap.Create(atlasWidth, atlasHeight, true);

        AddAllGlyphs(charCodes, m_glyphHeight, yData, glyphSlot);

        m_data.Size = fontSize;
        m_data.LineSpacing = m_glyphHeight;
        m_data.GlyphCount = static_cast<u32>(m_glyphMap.size());
        m_data.GlyphInfos = new GlyphInfo[m_data.GlyphCount];

        u32 counter = 0;
        for (const auto& glyph : m_glyphMap) {
            m_data.GlyphInfos[counter++] = glyph.second;
        }

        m_size = fontSize;

        SetInitialized();
    }

    void FontAtlas::UnloadBitmap() noexcept {
        KML_ASSERT(m_bitmap.IsValid());
        m_bitmap.Dispose();
    }
}
