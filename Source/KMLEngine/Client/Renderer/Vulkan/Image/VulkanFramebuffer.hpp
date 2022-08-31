//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanFramebuffer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANFRAMEBUFFER_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANFRAMEBUFFER_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../../../../Common/Util/Math/Point.hpp"
#include <vector>

namespace KMLEngine::Vulkan {
    class Framebuffer final : public DeviceObject<VkFramebuffer, VK_OBJECT_TYPE_FRAMEBUFFER>, public Disposable<Framebuffer> {
            friend Disposable<Framebuffer>;
        public:
        class Builder final {
            friend class Framebuffer;
        private:
            std::vector<VkImageView> m_attachments;
            VkRenderPass m_renderPass = VK_NULL_HANDLE;

            u32 m_width = 0;
            u32 m_height = 0;
            u32 m_layers = 0;
        public:
            ~Builder() noexcept { Reset(); }

            KML_FORCEINLINE void Reset() noexcept {
                m_layers = 0;
                m_height = 0;
                m_width = 0;

                m_renderPass = VK_NULL_HANDLE;
                m_attachments.clear();
            }
			
            KML_FORCEINLINE Builder& AddAttachment(VkImageView imageView) noexcept {
                KML_ASSERT(imageView);
                m_attachments.push_back(imageView);

                return *this;
            }

            KML_FORCEINLINE Builder& SetRenderPass(VkRenderPass renderPass) noexcept {
                KML_ASSERT(renderPass);
                m_renderPass = renderPass;

                return *this;
            }

            KML_FORCEINLINE Builder& SetSize(u32 width, u32 height, u32 layers) noexcept {
                KML_ASSERT(width);
                KML_ASSERT(height);
                KML_ASSERT(layers);

                m_width = width;
                m_height = height;
                m_layers = layers;

                return *this;
            }
        };
    private:
        VkRenderPass m_renderPass = VK_NULL_HANDLE;

        PointU32 m_size;
        u32 m_layers = 0;
		
        void OnDisposing();
    public:
        void Create(Device& device, const Builder& builder);

        [[nodiscard]] KML_FORCEINLINE u32 GetWidth() const noexcept { return m_size.X; }
        [[nodiscard]] KML_FORCEINLINE u32 GetHeight() const noexcept { return m_size.Y; }
        [[nodiscard]] KML_FORCEINLINE u32 GetLayers() const noexcept { return m_layers; }

        [[nodiscard]] KML_FORCEINLINE PointU32 GetSize() const noexcept { return m_size; }

        [[nodiscard]] KML_FORCEINLINE VkRenderPass& GetRenderPass() noexcept {
            KML_ASSERT(m_renderPass);
            return m_renderPass;
        }

        [[nodiscard]] KML_FORCEINLINE const VkRenderPass& GetRenderPass() const noexcept {
            KML_ASSERT(m_renderPass);
            return m_renderPass;
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANFRAMEBUFFER_HPP