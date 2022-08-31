//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: btree_set.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_BTREE_SET_HPP
#define KMLENGINE_COMMON_UTIL_STL_BTREE_SET_HPP

#pragma once

#include "hash.hpp"
#include <parallel_hashmap/btree.h>
#include <memory_resource>

namespace kml_stl {
    template<typename T,
            typename Compare = less<T>,
            typename Allocator = phmap::priv::Allocator<T>>
    using btree_set = phmap::btree_set<T, Compare, Allocator>;

    namespace pmr {
        template<typename T,
                typename Compare = less<T>,
                typename Allocator = std::pmr::polymorphic_allocator<T>>
        using btree_set = phmap::btree_set<T, Compare, Allocator>;
    }
}

#endif //KMLENGINE_COMMON_UTIL_STL_BTREE_SET_HPP
