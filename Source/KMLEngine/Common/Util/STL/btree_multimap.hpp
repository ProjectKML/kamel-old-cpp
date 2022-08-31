//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: btree_multimap.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_BTREE_MULTIMAP_HPP
#define KMLENGINE_COMMON_UTIL_STL_BTREE_MULTIMAP_HPP

#pragma once

#include "hash.hpp"
#include <parallel_hashmap/btree.h>
#include <memory_resource>

namespace kml_stl {
    template<typename K,
            typename V,
            typename Compare = less<K>,
            typename Allocator = phmap::priv::Allocator<phmap::priv::Pair<const K, V>>>
    using btree_multimap = phmap::btree_multimap<K, V, Compare, Allocator>;

    namespace pmr {
        template<typename K,
                typename V,
                typename Compare = less<K>,
                typename Allocator = std::pmr::polymorphic_allocator<phmap::priv::Pair<const K, V>>>
        using btree_multimap = phmap::btree_multimap<K, V, Compare, Allocator>;
    }
}

#endif //KMLENGINE_COMMON_UTIL_STL_BTREE_MULTIMAP_HPP
