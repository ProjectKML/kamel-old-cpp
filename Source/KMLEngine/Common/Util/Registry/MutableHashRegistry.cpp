//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MutableHashRegistry.cpp
//------------------------------------------------------------

#include "MutableHashRegistry.hpp"
#include "../../Core/Package/PackageLocation.hpp"

//Classes
#include "../../../Client/Renderer/Vulkan/Pipeline/VulkanPipelineLayout.hpp"

namespace KMLEngine {
	template<typename K, typename V, typename C>
	void MutableHashRegistry<K, V, C>::OnDisposing() {
		for(const auto& [key, value] : m_writeMap) {
			value->Object.Dispose();
			delete value;
		}
		m_writeMap.clear();

		for(const auto& [key, value] : m_readMap) {
			value->Object.Dispose();
			delete value;
		}
		m_readMap.clear();

		m_context = nullptr;
		m_releaseCallback = {};
		m_releasedObjects.clear();
	}
	
	template<typename K, typename V, typename C>
	void MutableHashRegistry<K, V, C>::Create(C& context, std::function<void(Reference*)> releaseCallback) noexcept {
		m_context = &context;
		m_releaseCallback = std::move(releaseCallback);

		this->SetInitialized();
	}
	
	template<typename K, typename V, typename C>
	V& MutableHashRegistry<K, V, C>::Acquire(const K& key) {
		if(const auto iterator = m_readMap.find(key); iterator != m_readMap.end()) {
			++iterator->second->RefCount;
			return iterator->second->Object;
		}

		m_mutex.lock();
		if(const auto writeIterator = m_writeMap.find(key); writeIterator != m_writeMap.end()) {
			auto& object = writeIterator->second->Object;
			++writeIterator->second->RefCount;
			m_mutex.unlock();

			return object;
		}

		auto* value = new Reference;
		value->Object.Create(*m_context, key);
		m_writeMap.insert(std::make_pair(key, value));
		m_mutex.unlock();
        
		return value->Object;
	}
	
	template<typename K, typename V, typename C>
	void MutableHashRegistry<K, V, C>::Release(const K& key) {
		if(const auto iterator = m_readMap.find(key); iterator != m_readMap.end()) {
			if(!--iterator->second->RefCount) {
				m_mutex.lock();
				m_releasedObjects.push_back(*iterator);
				m_mutex.unlock();
			}
			return;
		}

		m_mutex.lock();
		const auto writeIterator = m_writeMap.find(key);
		KML_ASSERT(writeIterator != m_writeMap.end());

		if(!--writeIterator->second->RefCount) {
			auto* value = writeIterator->second;
			m_writeMap.erase(key);

			if(m_releaseCallback) m_releaseCallback(value);
		    else delete value;
		}
		m_mutex.unlock();
	}
	
	template<typename K, typename V, typename C>
	void MutableHashRegistry<K, V, C>::Release(const V& value) {
		if constexpr(std::is_same_v<K, PackageLocation>) {
			Release(value.GetLocation());
		} else Release(value.GetDesc());
	}
	
	template<typename K, typename V, typename C>
	void MutableHashRegistry<K, V, C>::Update() {
		for(const auto& pair : m_writeMap) m_readMap.insert(pair);
		m_writeMap.clear();

		for(const auto& pair : m_releasedObjects) {
			auto* value = pair.second;
			m_readMap.erase(pair.first);
    
			if(m_releaseCallback) m_releaseCallback(value);
		}
	}

	//Classes
	template class MutableHashRegistry<Vulkan::DescriptorSetLayout::HashableDesc, Vulkan::DescriptorSetLayout, Vulkan::Device>;
	template class MutableHashRegistry<Vulkan::PipelineLayout::HashableDesc, Vulkan::PipelineLayout, Vulkan::Device>;
	template class MutableHashRegistry<Vulkan::Sampler::HashableDesc, Vulkan::Sampler, Vulkan::Device>;
}
