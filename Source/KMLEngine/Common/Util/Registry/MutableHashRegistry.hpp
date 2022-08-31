//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MutableHashRegistry.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_REGISTRY_MUTABLEHASHREGISTRY_HPP
#define KMLENGINE_COMMON_UTIL_REGISTRY_MUTABLEHASHREGISTRY_HPP

#pragma once

#include "../Traits/Disposable.hpp"
#include "../STL/flat_hash_map.hpp"
#include <vector>
#include <functional>
#include <atomic>
#include <mutex>

namespace KMLEngine {
	template<typename K, typename V, typename C>
	class MutableHashRegistry : public Disposable<MutableHashRegistry<K, V, C>> {
		friend Disposable<MutableHashRegistry<K, V, C>>;
	public:
		struct Reference {
			std::atomic_uint32_t RefCount;
			V Object;

			Reference() : RefCount(1) {}
		};
	
	private:
		kml_stl::flat_hash_map<K, Reference*> m_readMap;
		kml_stl::flat_hash_map<K, Reference*> m_writeMap;
		std::vector<std::pair<K, Reference*>> m_releasedObjects;
		std::function<void(Reference*)> m_releaseCallback;
		std::mutex m_mutex;

		C* m_context = nullptr;

		void OnDisposing();
	public:
		void Create(C& context, std::function<void(Reference*)> releaseCallback = {}) noexcept;

		V& Acquire(const K& key);
		void Release(const K& key);
		void Release(const V& value);

		void Update();
	};
}

#endif //KMLENGINE_COMMON_UTIL_REGISTRY_MUTABLEHASHREGISTRY_HPP