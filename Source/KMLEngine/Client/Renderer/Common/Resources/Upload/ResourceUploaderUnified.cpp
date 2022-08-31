//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ResourceUploaderUnified.cpp
//------------------------------------------------------------

#include "ResourceUploaderUnified.hpp"
#include "../../../RenderContext.hpp"
#include "../../../Vulkan/Buffer/VulkanBuffer.hpp"
#include "../../../../../Platform/PlatformMemory.hpp"

namespace KMLEngine {
    void ResourceUploaderUnified::CreateAndUploadBuffer(RenderContext& context, Vulkan::Buffer& buffer, const void* data, usize size, VkBufferUsageFlags usage) {
        KML_ASSERT(data);
        KML_ASSERT(size);

        buffer.Create(context.GetDevice(), size, VMA_MEMORY_USAGE_CPU_TO_GPU, usage);

        auto* destination = buffer.Map();
        PlatformMemory::Copy(destination, data, size);
        buffer.Unmap();
    }
}
