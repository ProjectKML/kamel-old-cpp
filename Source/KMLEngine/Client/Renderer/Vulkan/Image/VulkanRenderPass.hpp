//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanRenderPass.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANRENDERPASS_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANRENDERPASS_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../Util/VulkanUtils.hpp"
#include <vector>

namespace KMLEngine::Vulkan {
    class RenderPass final : public DeviceObject<VkRenderPass, VK_OBJECT_TYPE_RENDER_PASS>, public Disposable<RenderPass> {
        friend Disposable<RenderPass>;
    public:
        class SubpassBuilder {
            friend RenderPass;
        private:
            VkPipelineBindPoint m_bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
            std::vector<VkAttachmentReference> m_inputAttachments;
            std::vector<VkAttachmentReference> m_colorAttachments;
            std::vector<VkAttachmentReference> m_resolveAttachments;

            VkAttachmentReference m_depthStencilAttachment = {};
            bool m_depthStencilAttachmentUsed = false;

            std::vector<u32> m_preserveAttachments;
        public:
            ~SubpassBuilder() noexcept { Reset(); }

            KML_FORCEINLINE void Reset() noexcept {
                m_preserveAttachments.clear();

                m_depthStencilAttachmentUsed = false;
                m_depthStencilAttachment = {};

                m_resolveAttachments.clear();
                m_colorAttachments.clear();
                m_inputAttachments.clear();
                m_bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
            }
            
            KML_FORCEINLINE SubpassBuilder& AddInputAttachment(u32 attachment, VkImageLayout layout) noexcept {
                m_inputAttachments.push_back(Utils::AttachmentReference(attachment, layout));

                return *this;
            }

            KML_FORCEINLINE SubpassBuilder& AddColorAttachment(u32 attachment, VkImageLayout layout) noexcept {
                m_colorAttachments.push_back(Utils::AttachmentReference(attachment, layout));

                return *this;
            }

            KML_FORCEINLINE SubpassBuilder& AddResolveAttachment(u32 attachment, VkImageLayout layout) noexcept {
                m_resolveAttachments.push_back(Utils::AttachmentReference(attachment, layout));

                return *this;
            }

            KML_FORCEINLINE SubpassBuilder& SetDepthStencilAttachment(u32 attachment, VkImageLayout layout) noexcept {
                m_depthStencilAttachment = Utils::AttachmentReference(attachment, layout);
                m_depthStencilAttachmentUsed = true;

                return *this;
            }

            KML_FORCEINLINE SubpassBuilder& AddPreserveAttachment(u32 attachment) noexcept {
                m_preserveAttachments.push_back(attachment);

                return *this;
            }

            KML_FORCEINLINE SubpassBuilder& SetBindPoint(VkPipelineBindPoint bindPoint) noexcept {
                m_bindPoint = bindPoint;
                return *this;
            }
        };

        class Builder {
            friend RenderPass;
        private:
            std::vector<VkAttachmentDescription> m_attachmentDescriptions;
            std::vector<VkSubpassDescription> m_subpassDescriptions;
            std::vector<VkSubpassDependency> m_subpassDependencies;
        public:
            ~Builder() noexcept { Reset(); }

            KML_FORCEINLINE void Reset() noexcept {
                m_subpassDependencies.clear();
                m_subpassDescriptions.clear();
                m_attachmentDescriptions.clear();
            }
            
            KML_FORCEINLINE Builder& AddAttachmentDescription(VkFormat format,
                VkSampleCountFlagBits samples,
                VkAttachmentLoadOp loadOp,
                VkAttachmentStoreOp storeOp,
                VkImageLayout initialLayout,
                VkImageLayout finalLayout,
                VkAttachmentLoadOp stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                VkAttachmentStoreOp stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE) noexcept {
                m_attachmentDescriptions.push_back(Utils::AttachmentDescription(format,
                                                                                samples,
                                                                                loadOp,
                                                                                storeOp,
                                                                                initialLayout,
                                                                                finalLayout,
                                                                                stencilLoadOp,
                                                                                stencilStoreOp));

                return *this;
            }

            KML_FORCEINLINE Builder& AddAttachmentDescription(const VkAttachmentDescription& attachmentDescription) noexcept {
                m_attachmentDescriptions.push_back(attachmentDescription);

                return *this;
            }

            Builder& AddSubpassDescription(const SubpassBuilder& builder) noexcept;

            KML_FORCEINLINE Builder& AddSubpassDependency(u32 srSubpass,
                u32 dstSubpass,
                VkPipelineStageFlags srcStageMask,
                VkPipelineStageFlags dstStageMask,
                VkAccessFlags srcAccessMask,
                VkAccessFlags dstAccessMask,
                VkDependencyFlags dependencyFlags) noexcept {
                m_subpassDependencies.push_back(Utils::SubpassDependency(srSubpass,
                                                                         dstSubpass,
                                                                         srcStageMask,
                                                                         dstStageMask,
                                                                         srcAccessMask,
                                                                         dstAccessMask,
                                                                         dependencyFlags));

                return *this;
            }

            KML_FORCEINLINE Builder& AddSubpassDependency(const VkSubpassDependency& subpassDependency) noexcept {
                m_subpassDependencies.push_back(subpassDependency);

                return *this;
            }
        };
    private:
        void OnDisposing();
    public:
        void Create(Device& device, const Builder& builder);
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANRENDERPASS_HPP
