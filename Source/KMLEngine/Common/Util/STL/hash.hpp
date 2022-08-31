//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: hash.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_HASH_HPP
#define KMLENGINE_COMMON_UTIL_STL_HASH_HPP

#pragma once

#include <parallel_hashmap/phmap.h>
#include <functional>

namespace kml_stl {
    template<typename T>
    using hash_default_equals = phmap::priv::hash_default_eq<T>;

    template<typename T>
    using hash_default_hash = phmap::priv::hash_default_hash<T>;

    template<typename T>
    using less = phmap::Less<T>;
}

#endif //KMLENGINE_COMMON_UTIL_STL_HASH_HPP
