//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ResourceUploaderStaging.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_UPLOAD_RESOURCEUPLOADERSTAGING_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_UPLOAD_RESOURCEUPLOADERSTAGING_HPP

#pragma once

#include "ResourceUploader.hpp"

namespace KMLEngine {
	class ResourceUploaderStaging final : public ResourceUploader {
	public:
		void CreateAndUploadBuffer(RenderContext& context, Vulkan::Buffer& buffer, const void* data, usize size, VkBufferUsageFlags usage) final;
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_UPLOAD_RESOURCEUPLOADERSTAGING_HPP