//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDebugUtils.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEBUGUTILS_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEBUGUTILS_HPP

#pragma once

#include "Util/VulkanObject.hpp"

namespace KMLEngine::Vulkan {
    class DebugUtils final : public InstanceObject<VkDebugUtilsMessengerEXT, VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT>, public Disposable<DebugUtils> {
        friend Disposable<DebugUtils>;
    private:
        void OnDisposing();
    public:
        void Create(Instance& instance);
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEBUGUTILS_HPP
