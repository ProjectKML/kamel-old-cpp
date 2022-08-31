//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanStructureList.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANSTRUCTURELIST_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANSTRUCTURELIST_HPP

#pragma once

#include "Vulkan.hpp"
#include <vector>

namespace KMLEngine::Vulkan {
	class StructureList {
	private:
		std::vector<VkBaseInStructure*> m_elements;

	public:
		KML_FORCEINLINE ~StructureList() noexcept { Clear(); }
		
		KML_FORCEINLINE void Reset() noexcept { m_elements.clear(); }

		KML_FORCEINLINE void Add(void* structure) {
			KML_ASSERT(structure);

			auto* inStructure = static_cast<VkBaseInStructure*>(structure);
			inStructure->pNext = nullptr;
			
			if(!IsEmpty()) m_elements.back()->pNext = inStructure;
			m_elements.push_back(inStructure);
		}

		KML_FORCEINLINE bool TryRemoveLast() {
			if(IsEmpty()) return false;

			m_elements.pop_back();
			if(!IsEmpty()) m_elements.back()->pNext = nullptr;

			return true;
		}

		KML_FORCEINLINE void RemoveLast() {
			const auto result = TryRemoveLast();
			KML_ASSERT(result);
		}

		KML_FORCEINLINE void Clear() noexcept { while(TryRemoveLast()) {} }

		[[nodiscard]] KML_FORCEINLINE usize GetSize() const noexcept { return m_elements.size(); }
		[[nodiscard]] KML_FORCEINLINE bool IsEmpty() const noexcept { return m_elements.empty(); }
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANSTRUCTURELIST_HPP