//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: node_hash_set.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_NODE_HASH_SET_HPP
#define KMLENGINE_COMMON_UTIL_STL_NODE_HASH_SET_HPP

#pragma once

#include "hash.hpp"
#include <memory_resource>

namespace kml_stl {
	template<typename T,
	        typename Hash = hash_default_hash<T>,
	        typename Equals = hash_default_equals<T>,
	        typename Allocator = phmap::priv::Allocator<T>>
	using node_hash_set = phmap::node_hash_set<T, Hash, Equals, Allocator>;

	namespace pmr {
        template<typename T,
                typename Hash = hash_default_hash<T>,
                typename Equals = hash_default_equals<T>,
                typename Allocator = std::pmr::polymorphic_allocator<T>>
        using node_hash_set = phmap::node_hash_set<T, Hash, Equals, Allocator>;
	}
}

#endif //KMLENGINE_COMMON_UTIL_STL_NODE_HASH_SET_HPP
