//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Assert.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_PLATFORM_ASSERT_ASSERT_HPP
#define KMLENGINE_PLATFORM_ASSERT_ASSERT_HPP

#pragma once

#include <cassert>

#define KML_ASSERT(x) assert(x)

#define KML_ASSERT_EQ(a, b) KML_ASSERT(a == b)
#define KML_ASSERT_NOT_EQ(a, b) KML_ASSERT(a != b)
#define KML_UNIMPLEMENTED() KML_ASSERT(0 && "Unimplemented")

#endif //KMLENGINE_PLATFORM_ASSERT_ASSERT_HPP