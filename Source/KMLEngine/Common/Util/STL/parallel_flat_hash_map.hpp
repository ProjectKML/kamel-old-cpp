//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: parallel_flat_hash_map.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_PARALLEL_FLAT_HASH_MAP_HPP
#define KMLENGINE_COMMON_UTIL_STL_PARALLEL_FLAT_HASH_MAP_HPP

#pragma once

#include "hash.hpp"
#include "../../../Platform/Types.hpp"
#include <memory_resource>

namespace kml_stl {
    using namespace KMLEngine;

    template<typename K,
            typename V,
            typename Hash = hash_default_hash<K>,
            typename Equals = hash_default_equals<K>,
            typename Allocator = phmap::priv::Allocator<phmap::priv::Pair<const K, V>>,
            usize N = 4,
            typename Mutex = phmap::NullMutex>
    using parallel_flat_hash_map = phmap::parallel_flat_hash_map<K, V, Hash, Equals, Allocator, N, Mutex>;

    namespace pmr {
        template<typename K,
                typename V,
                typename Hash = hash_default_hash<K>,
                typename Equals = hash_default_equals<K>,
                typename Allocator = std::pmr::polymorphic_allocator<phmap::priv::Pair<const K, V>>,
                usize N = 4,
                typename Mutex = phmap::NullMutex>
        using parallel_flat_hash_map = phmap::parallel_flat_hash_map<K, V, Hash, Equals, Allocator, N, Mutex>;
    }
}

#endif //KMLENGINE_COMMON_UTIL_STL_PARALLEL_FLAT_HASH_MAP_HPP
