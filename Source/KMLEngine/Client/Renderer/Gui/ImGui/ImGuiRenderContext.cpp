//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ImGuiRenderContext.cpp
//------------------------------------------------------------

#include "ImGuiRenderContext.hpp"
#include "../../RenderContext.hpp"
#include "../../../Core/Window/Window.hpp"
#include "../../../../Common/Core/Event/EventBus.hpp"
#include "../../../../Common/Core/Package/PackageLocation.hpp"
#include <imgui/backends/imgui_impl_vulkan.h>
#include <imgui/backends/imgui_impl_sdl.h>
#include <fmt/format.h>
#include <filesystem>

namespace KMLEngine {
    static void SetDarkScheme() {
        ImGui::StyleColorsDark();

        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};
        colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
        colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.0f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.94f, 0.94f, 0.94f, 1.0f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 0.7f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.66f, 0.66f, 0.66f, 1.0f);

        auto& style = ImGui::GetStyle();
        style.WindowPadding.x = 8.0f;
        style.WindowPadding.y = 8.0f;
        style.FramePadding.x = 4.0f;
        style.FramePadding.y = 3.0f;
        style.ItemSpacing.x = 8.0f;
        style.ItemSpacing.y = 4.0f;
        style.ItemInnerSpacing.x = 4.0f;
        style.ItemInnerSpacing.y = 4.0f;
        style.TouchExtraPadding.x = 0.0f;
        style.TouchExtraPadding.y = 0.0f;
        style.IndentSpacing = 21.0f;
        style.ScrollbarSize = 14.0f;
        style.GrabMinSize = 10.0f;
        style.WindowBorderSize = 1.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;
        style.TabBorderSize = 0.0f;
        style.WindowRounding = 0.0f;
        style.ChildRounding = 0.0f;
        style.FrameRounding = 0.0f;
        style.PopupRounding = 0.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 0.0f;
        style.WindowTitleAlign.x = 0.0f;
        style.WindowTitleAlign.y = 0.5f;
        style.WindowMenuButtonPosition = ImGuiDir_Left;
        style.ColorButtonPosition = ImGuiDir_Right;
        style.ButtonTextAlign.x = 0.5f;
        style.ButtonTextAlign.y = 0.5f;
        style.SelectableTextAlign.x = 0.0f;
        style.SelectableTextAlign.y = 0.0f;
        style.DisplaySafeAreaPadding.x = 3.0f;
        style.DisplaySafeAreaPadding.y = 3.0f; //TODO: new scheme????
    }

    static KML_FORCEINLINE void SetConfigDirectory(ImGuiIO& io) {
        const auto configPath = std::filesystem::current_path() / "Configs";
        if(!std::filesystem::exists(configPath)) std::filesystem::create_directory(configPath);
        io.IniFilename = "Configs/Sandbox.ini";
    }

    static void CreateFontsTexture(RenderThreadManager<RenderThreadTransferCollection>& transferManager) {
        auto& threadCollection = transferManager.Acquire();

        auto& commandBuffer = threadCollection.BeginImmediateDirect();

        if(!ImGui_ImplVulkan_CreateFontsTexture(commandBuffer)) {
            throw std::runtime_error(fmt::format("{} failed", "ImGui_ImplVulkan_CreateFontsTexture"));
        }

        threadCollection.EndImmediateDirect();

        transferManager.Release(threadCollection);
    }

    void ImGuiRenderContext::OnDisposing() {
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplSDL2_Shutdown();

        EventBus::GetInstance().Remove<SystemEvent>(m_eventListenerId);

        ImGui::DestroyContext(m_context);
    }

    void ImGuiRenderContext::CreateContext() {
        IMGUI_CHECKVERSION();

        auto& renderContext = RenderContext::GetInstance();

        m_context = ImGui::CreateContext();
        if(!m_context) {
            throw std::runtime_error(fmt::format("{} failed", "ImGui::CreateContext"));
        }

        m_eventListenerId = EventBus::GetInstance().Add<SystemEvent>([](const SystemEvent& event) {
            ImGui_ImplSDL2_ProcessEvent(event.Event);
        });
    }

    void ImGuiRenderContext::CreateBackend() {
        if(!ImGui_ImplSDL2_InitForVulkan(Window::GetInstance().GetHandle())) {
            throw std::runtime_error(fmt::format("{} failed", "ImGui_ImplSDL2_InitForVulkan"));
        }

        auto& renderContext = RenderContext::GetInstance();

        auto& device = renderContext.GetDevice();
        auto& swapchain = renderContext.GetSwapchain();

        const auto& directQueue = device.GetDirectQueue();
        const auto& capabilities = renderContext.GetSurface().GetCapabilities();

        ImGui_ImplVulkan_InitInfo vulkanInitInfo;
        vulkanInitInfo.Instance = renderContext.GetVkInstance();
        vulkanInitInfo.PhysicalDevice = device.GetPhysicalDevice();
        vulkanInitInfo.Device = device;
        vulkanInitInfo.QueueFamily = directQueue.GetFamilyIndex();
        vulkanInitInfo.Queue = directQueue;
        vulkanInitInfo.PipelineCache = VK_NULL_HANDLE;
        vulkanInitInfo.DescriptorPool = device.GetDescriptorPool();
        vulkanInitInfo.Subpass = 0;
        vulkanInitInfo.MinImageCount = capabilities.surfaceCapabilities.minImageCount < 2 ? 2 : capabilities.surfaceCapabilities.minImageCount;
        vulkanInitInfo.ImageCount = swapchain.GetNumImages();
        vulkanInitInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        vulkanInitInfo.Allocator = nullptr;
        vulkanInitInfo.CheckVkResultFn = [](VkResult result) {
            Vulkan::ThrowIfFailed(result, "ImGui vulkan function");
        };

        if(!ImGui_ImplVulkan_Init(&vulkanInitInfo, swapchain.GetRenderPass())) {
            throw std::runtime_error(fmt::format("{} failed", "ImGui_ImplVulkan_Init"));
        }

        CreateFontsTexture(renderContext.GetTransferManager());
    }

    void ImGuiRenderContext::LoadFonts() {
        AddFont(PackageLocation("Resources", "VeraMono.ttf"), 14.0f);
    }

    void ImGuiRenderContext::AddFont(const PackageLocation& location, f32 size) {
        KML_ASSERT(size);

        byte* data;
        usize dataSize;
        location.GetEntry(data, dataSize, *std::pmr::new_delete_resource());

        auto& io = ImGui::GetIO();
        io.Fonts->AddFontFromMemoryTTF(data, static_cast<i32>(dataSize), size);
    }

    void ImGuiRenderContext::Create() {
        auto allocationFunction = [](usize size, void* userData) -> void* { return new byte[size]; };
        auto deallocationFunction = [](void* data, void* userData) { delete[] (byte*)data; }; //TODO: CIV
        ImGui::SetAllocatorFunctions(allocationFunction, deallocationFunction);

        CreateContext();

        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //TODO:io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //TODO: there is a bug when it closes when being clicked inside the window
        SetConfigDirectory(io);

        LoadFonts();
        SetDarkScheme();

        CreateBackend();

        SetInitialized();
    }

    void ImGuiRenderContext::NewFrame() noexcept {
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplSDL2_NewFrame(Window::GetInstance().GetHandle());

        ImGui::NewFrame();
    }

    void ImGuiRenderContext::Render(Vulkan::CommandBuffer& commandBuffer) noexcept {
        ImGui::Render();

        commandBuffer.BeginDebugLabel("ImGui", Color4f(0.022f, 0.372332f, 0.010f));
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
        commandBuffer.EndDebugLabel();
    }

    void ImGuiRenderContext::EndFrame() noexcept {
        ImGui::EndFrame();

        auto& io = ImGui::GetIO();
        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }
}