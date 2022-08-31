//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: node_hash_map.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_NODE_HASH_MAP_HPP
#define KMLENGINE_COMMON_UTIL_STL_NODE_HASH_MAP_HPP

#pragma once

#include "hash.hpp"
#include <memory_resource>

namespace kml_stl {
    template<typename K,
            typename V,
            typename Hash = hash_default_hash<K>,
            typename Equals = hash_default_equals<K>,
            typename Allocator = phmap::priv::Allocator<phmap::priv::Pair<const K, V>>>
    using node_hash_map = phmap::node_hash_map<K, V, Hash, Equals, Allocator>;

    namespace pmr {
        template<typename K,
                typename V,
                typename Hash = hash_default_hash<K>,
                typename Equals = hash_default_equals<K>,
                typename Allocator = std::pmr::polymorphic_allocator<phmap::priv::Pair<const K, V>>>
        using node_hash_map = phmap::node_hash_map<K, V, Hash, Equals, Allocator>;
    }
}

#endif //KMLENGINE_COMMON_UTIL_STL_NODE_HASH_MAP_HPP
