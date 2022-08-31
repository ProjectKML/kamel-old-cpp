//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: String.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STRING_STRING_HPP
#define KMLENGINE_COMMON_UTIL_STRING_STRING_HPP

#pragma once

#include <string>
#include <memory_resource>

namespace KMLEngine::String {
#ifdef KML_PLATFORM_WINDOWS
    std::string ToUTF8(const std::wstring_view& str);
    std::pmr::string ToUTF8(const std::wstring_view& str, std::pmr::memory_resource& memoryResource);
	
    std::wstring ToUTF16(const std::string_view& str);
    std::pmr::wstring ToUTF16(const std::string_view& str, std::pmr::memory_resource& memoryResource);
#endif
}

#endif //KMLENGINE_COMMON_UTIL_STRING_STRING_HPP
