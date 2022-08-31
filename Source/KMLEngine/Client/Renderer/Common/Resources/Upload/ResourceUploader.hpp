//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ResourceUploader.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_UPLOAD_RESOURCEUPLOADER_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_UPLOAD_RESOURCEUPLOADER_HPP

#pragma once

#include "../../../../../Common/Util/Traits/Uncopyable.hpp"
#include "../../../Vulkan/Util/Vulkan.hpp"

namespace KMLEngine {
	class RenderContext;

	namespace Vulkan {
		class Buffer;
	}
	
	class ResourceUploader : public Uncopyable {
	public:
		virtual ~ResourceUploader() = default;
		
		virtual void CreateAndUploadBuffer(RenderContext& context, Vulkan::Buffer& buffer, const void* data, usize size, VkBufferUsageFlags usage) = 0;
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_UPLOAD_RESOURCEUPLOADER_HPP