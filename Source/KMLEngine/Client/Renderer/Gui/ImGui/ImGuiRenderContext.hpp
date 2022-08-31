//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ImGuiRenderContext.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_GUI_IMGUI_IMGUIRENDERCONTEXT_HPP
#define KMLENGINE_CLIENT_RENDERER_GUI_IMGUI_IMGUIRENDERCONTEXT_HPP

#pragma once

#include "../../../../Common/Util/Traits/Disposable.hpp"
#include <imgui/imgui.h>

namespace KMLEngine {
    namespace Vulkan { class CommandBuffer; }

    class PackageLocation;
    class ImGuiRenderContext final : public Disposable<ImGuiRenderContext>{
        friend Disposable<ImGuiRenderContext>;
    private:
        ImGuiContext* m_context = nullptr;

        usize m_eventListenerId = 0;

        void CreateContext();
        void CreateBackend();
        void LoadFonts();
        void AddFont(const PackageLocation& location, f32 size);

        void OnDisposing();
    public:
        void Create();

        void NewFrame() noexcept;
        void Render(Vulkan::CommandBuffer& commandBuffer) noexcept;
        void EndFrame() noexcept;
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_GUI_IMGUI_IMGUIRENDERCONTEXT_HPP