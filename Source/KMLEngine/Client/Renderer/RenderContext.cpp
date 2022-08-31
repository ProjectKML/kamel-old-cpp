//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderContext.cpp
//------------------------------------------------------------

#include "RenderContext.hpp"
#include "Vulkan/VulkanDeviceResources.hpp"
#include "Common/Resources/Upload/ResourceUploaderStaging.hpp"
#include "Common/Resources/Upload/ResourceUploaderUnified.hpp"
#include "../Core/Window/Window.hpp"

namespace KMLEngine {
    template<> RenderContext* Singleton<RenderContext>::_INSTANCE = nullptr;
    
    void RenderContext::OnDisposing() {
        DetachSingleton();

        delete m_resourceUploader;
        m_frameManager.Dispose();
        m_transferManager.Dispose();

        DestroyDeviceAndSwapchain();
    }

    void RenderContext::AddDeviceExtensions() {
        m_device.AddExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        
        m_device.AddExtension(VK_NV_MESH_SHADER_EXTENSION_NAME);
    }

    void RenderContext::CreateDeviceAndSwapchain() {
        m_instance.Initialize();
        m_instance.AddExtension(VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME);
		
        m_instance.Create(m_debugLevel > 0);
        if(m_debugLevel) m_instance.PrintProperties();

        const auto physicalDevice = m_instance.GetOptimalPhysicalDevice();
        m_surface.Create(m_instance, physicalDevice);
        if(m_debugLevel) m_surface.PrintProperties();

        m_physicalDevice.Create(physicalDevice, m_surface);
        m_device.Initialize(m_instance, m_physicalDevice);

        AddDeviceExtensions();

        //Enable features
        Vulkan::StructureList enabledFeaturesList;
        
        VkPhysicalDeviceFeatures2 enabledFeatures = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };

        VkPhysicalDeviceVulkan11Features enabledFeatures11 = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES };

        VkPhysicalDeviceVulkan12Features enabledFeatures12 = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
        enabledFeatures12.uniformAndStorageBuffer8BitAccess = VK_TRUE;

        VkPhysicalDeviceDescriptorIndexingFeatures enabledDescriptorIndexingFeatures = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES };

        VkPhysicalDeviceMeshShaderFeaturesNV enabledMeshShaderFeatures = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV };
        enabledMeshShaderFeatures.meshShader = VK_TRUE;
        enabledMeshShaderFeatures.taskShader = VK_TRUE;

        enabledFeaturesList.Add(&enabledFeatures);
        enabledFeaturesList.Add(&enabledFeatures11);
        if(m_physicalDevice.IsVulkan12Supported()) enabledFeaturesList.Add(&enabledFeatures12);
        else {
            if(m_physicalDevice.IsExtensionSupported(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME)) enabledFeaturesList.Add(&enabledDescriptorIndexingFeatures);
        }

        if(m_physicalDevice.IsExtensionSupported(VK_NV_MESH_SHADER_EXTENSION_NAME)) enabledFeaturesList.Add(&enabledMeshShaderFeatures);

        //Create device and swapchain
        m_device.Create(enabledFeatures);
        if(m_debugLevel) m_device.PrintProperties();

        auto& window = Window::GetInstance();
        m_swapchain.Create(m_device, m_surface, false, window.IsFullscreen()); //TODO: verticalSync
    }
	
    void RenderContext::DestroyDeviceAndSwapchain() {
        m_swapchain.Dispose();
        m_device.Dispose();
        m_physicalDevice.Dispose();
        m_surface.Dispose();
        m_instance.Dispose();
    }
	
    void RenderContext::Create(u32 debugLevel) {
        m_debugLevel = debugLevel;
		
        CreateDeviceAndSwapchain();

        const auto numThreads = 4; //TODO:
        m_transferManager.Create(m_device, numThreads);
        m_frameManager.Create(m_device, m_swapchain, 2, numThreads);

        if(m_physicalDevice.HasDedicatedMemory()) m_resourceUploader = new ResourceUploaderStaging;
        else m_resourceUploader = new ResourceUploaderUnified;
        
        AttachSingleton();

        SetInitialized();
    }

    void RenderContext::Update() {
        m_device.GetResources().Update();
    }
}
