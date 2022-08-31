//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ForceInline.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_PLATFORM_HINTS_FORCEINLINE_HPP
#define KMLENGINE_PLATFORM_HINTS_FORCEINLINE_HPP

#pragma once

#ifdef KML_COMPILER_MSVC
#define KML_FORCEINLINE __forceinline
#elif defined(KML_COMPILER_GCC) || defined(KML_COMPILER_CLANG)
#define KML_FORCEINLINE inline __attribute__((always_inline))
#endif

#endif //KMLENGINE_PLATFORM_HINTS_FORCEINLINE_HPP