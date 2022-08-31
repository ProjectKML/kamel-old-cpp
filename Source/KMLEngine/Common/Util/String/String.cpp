//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: String.cpp
//------------------------------------------------------------

#include "String.hpp"
#include "../../../Platform/Assert/Assert.hpp"

#ifdef KML_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace KMLEngine::String {
#ifdef KML_PLATFORM_WINDOWS
    std::string ToUTF8(const std::wstring_view& str) {
        std::string buffer;

        if(const auto newLength = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.length()), nullptr, 0, nullptr, nullptr); newLength) {
            buffer.resize(newLength);
            const auto convertedLength = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.length()), buffer.data(), newLength, nullptr, nullptr);
            KML_ASSERT_EQ(newLength, convertedLength);
        }

        return buffer;
    }

    std::pmr::string ToUTF8(const std::wstring_view& str, std::pmr::memory_resource& memoryResource) {
        std::pmr::string buffer(&memoryResource);

        if(const auto newLength = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.length()), nullptr, 0, nullptr, nullptr); newLength) {
            buffer.resize(newLength);
            const auto convertedLength = WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.length()), buffer.data(), newLength, nullptr, nullptr);
            KML_ASSERT_EQ(newLength, convertedLength);
        }

        return buffer;
    }

    std::wstring ToUTF16(const std::string_view& str) {
        std::wstring buffer;

        if(const auto newLength = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), nullptr, 0); newLength) {
            buffer.resize(newLength);
            const auto convertedLength = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), buffer.data(), newLength);
            KML_ASSERT_EQ(newLength, convertedLength);
        }

        return buffer;
    }

    std::pmr::wstring ToUTF16(const std::string_view& str, std::pmr::memory_resource& memoryResource) {
        std::pmr::wstring buffer(&memoryResource);

        if(const auto newLength = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), nullptr, 0); newLength) {
            buffer.resize(newLength);
            const auto convertedLength = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), buffer.data(), newLength);
            KML_ASSERT_EQ(newLength, convertedLength);
        }

        return buffer;
    }
#endif
}
