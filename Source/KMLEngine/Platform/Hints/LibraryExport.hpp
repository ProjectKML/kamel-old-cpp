//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: LibraryExport.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_PLATFORM_HINTS_LIBRARYEXPORT_HPP
#define KMLENGINE_PLATFORM_HINTS_LIBRARYEXPORT_HPP

#pragma once

#ifdef KML_PLATFORM_WINDOWS
#ifdef KML_COMPILER_MSVC
#define KML_LIBRARY_EXPORT __declspec(dllexport)
#elif defined(KML_COMPILER_GCC) || defined(KML_COMPILER_CLANG)
#define KML_LIBRARY_EXPORT __attribute__ ((dllexport))
#endif
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_LINUX)
#if defined(KML_COMPILER_GCC) || defined(KML_COMPILER_CLANG)
#define KML_LIBRARY_EXPORT __attribute__ ((visibility ("default")))
#endif
#endif

#endif //KMLENGINE_PLATFORM_HINTS_LIBRARYEXPORT_HPP