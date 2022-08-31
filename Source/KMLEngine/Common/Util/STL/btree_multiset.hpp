//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: btree_multiset.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_BTREE_MULTISET_HPP
#define KMLENGINE_COMMON_UTIL_STL_BTREE_MULTISET_HPP

#pragma once

#include "hash.hpp"
#include <parallel_hashmap/btree.h>
#include <memory_resource>

namespace kml_stl {
    template<typename T,
            typename Compare = less<T>,
            typename Allocator = phmap::priv::Allocator<T>>
    using btree_multiset = phmap::btree_multiset<T, Compare, Allocator>;

    namespace pmr {
        template<typename T,
                typename Compare = less<T>,
                typename Allocator = std::pmr::polymorphic_allocator<T>>
        using btree_multiset = phmap::btree_multiset<T, Compare, Allocator>;
    }
}

#endif //KMLENGINE_COMMON_UTIL_STL_BTREE_MULTISET_HPP
