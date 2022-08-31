//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ResourceUploaderStaging.cpp
//------------------------------------------------------------

#include "ResourceUploaderStaging.hpp"
#include "../../../RenderContext.hpp"
#include "../../../Vulkan/Buffer/VulkanBuffer.hpp"
#include "../../../../../Platform/PlatformMemory.hpp"

namespace KMLEngine {
    void ResourceUploaderStaging::CreateAndUploadBuffer(RenderContext& context, Vulkan::Buffer& buffer, const void* data, usize size, VkBufferUsageFlags usage) {
        KML_ASSERT(data);
        KML_ASSERT(size);

        auto& device = context.GetDevice();
        buffer.Create(device, size, VMA_MEMORY_USAGE_GPU_ONLY, usage | VK_BUFFER_USAGE_TRANSFER_DST_BIT);

        Vulkan::Buffer stagingBuffer;
        stagingBuffer.Create(device, size, VMA_MEMORY_USAGE_CPU_TO_GPU, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);

        const auto destination = stagingBuffer.Map();
        PlatformMemory::Copy(destination, data, size);
        stagingBuffer.Unmap();

        auto& transferManager = context.GetTransferManager();
        auto& transferCollection = transferManager.Acquire();
        auto& commandBuffer = transferCollection.BeginImmediateTransfer();

        const auto bufferCopy = Vulkan::Utils::BufferCopy(size);
        commandBuffer.CopyBuffer(stagingBuffer, buffer, 1, &bufferCopy);

        transferCollection.EndImmediateTransfer();
        transferManager.Release(transferCollection);

        stagingBuffer.Dispose();
    }
}
