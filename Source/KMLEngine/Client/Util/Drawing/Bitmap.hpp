//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Bitmap.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_UTIL_DRAWING_BITMAP_HPP
#define KMLENGINE_CLIENT_UTIL_DRAWING_BITMAP_HPP

#pragma once

#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Platform/Types.hpp"
#include "../../../Common/Util/Traits/Disposable.hpp"
#include "../../../Platform/Assert/Assert.hpp"
#include "../../../Platform/PlatformMemory.hpp"
#include <memory_resource>

namespace KMLEngine {
    template <typename T>
    class Bitmap : public Disposable<Bitmap<T>> {
        friend Disposable<Bitmap<T>>;
    private:
        std::pmr::memory_resource* m_memoryResource;

        T* m_buffer = nullptr;

        u32 m_width = 0;
        u32 m_height = 0;

        void OnDisposing() {
            m_memoryResource->deallocate(m_buffer, m_width * m_height * sizeof(T), alignof(T));
            m_buffer = nullptr;
        }

    public:
        KML_FORCEINLINE void Create(u32 width, u32 height, bool zeroMemory = false,
                                   std::pmr::memory_resource* memoryResource = std::pmr::get_default_resource()) {
            KML_ASSERT(memoryResource);

            m_memoryResource = memoryResource;

            m_width = width;
            m_height = height;

            const auto size = width * height * sizeof(T);
            m_buffer = static_cast<T*>(m_memoryResource->allocate(size, alignof(T)));

            if (zeroMemory) PlatformMemory::Zero(m_buffer, size);

            this->SetInitialized();
        }

        [[nodiscard]] KML_FORCEINLINE const T GetPixel(u32 x, u32 y) const noexcept { return m_buffer[y * m_width + x]; }
        KML_FORCEINLINE void SetPixel(u32 x, u32 y, T pixel) noexcept { m_buffer[y * m_width + x] = pixel; }

        [[nodiscard]] KML_FORCEINLINE const u32 GetWidth() const noexcept { return m_width; }
        [[nodiscard]] KML_FORCEINLINE const u32 GetHeight() const noexcept { return m_height; }
        [[nodiscard]] KML_FORCEINLINE const u32 GetBytesPerPixel() const noexcept { return sizeof(T); }

        [[nodiscard]] KML_FORCEINLINE bool IsValid() const noexcept { return m_buffer != nullptr; }

        [[nodiscard]] KML_FORCEINLINE const T* GetData() const noexcept { return m_buffer; }
    };
}

#endif //KMLENGINE_CLIENT_UTIL_DRAWING_BITMAP_HPP
