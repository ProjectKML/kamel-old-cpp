//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ViewportSizeManager.cpp
//------------------------------------------------------------

#include "ViewportSizeManager.hpp"
#include "../../../Core/Window/Window.hpp"

namespace KMLEngine {
    void ViewportSizeManager::Create() noexcept { m_size = Window::GetInstance().GetSize(); }

    bool ViewportSizeManager::Update() noexcept {
        const auto size = Window::GetInstance().GetSize();
        if(size == m_size) return false;

        m_size = size;
        return true;
    }
}
