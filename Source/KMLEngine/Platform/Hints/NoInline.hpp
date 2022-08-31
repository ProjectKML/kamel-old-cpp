//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: NoInline.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_PLATFORM_HINTS_NOINLINE_HPP
#define KMLENGINE_PLATFORM_HINTS_NOINLINE_HPP

#pragma once

#ifdef KML_COMPILER_MSVC
#define KML_NOINLINE __declspec(noinline)
#elif defined(KML_COMPILER_GCC) || defined(KML_COMPILER_CLANG)
#define KML_NOINLINE inline __attribute__((noinline))
#endif

#endif //KMLENGINE_PLATFORM_HINTS_NOINLINE_HPP