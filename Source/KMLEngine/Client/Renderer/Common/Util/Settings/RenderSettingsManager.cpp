//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderSettingsManager.cpp
//------------------------------------------------------------

#include "RenderSettingsManager.hpp"
#include "../../../RenderContext.hpp"

namespace KMLEngine {
    void RenderSettingsManager::OnDisposing() {
        m_enabledSettings = {};
        m_lastEnabledSettings = {};
        m_supportedSettings = {};
    }

    void RenderSettingsManager::Create(RenderContext& context) {
        auto& device = context.GetDevice();

        //Query supported settings
        m_supportedSettings.MeshShading = device.IsExtensionEnabled(VK_NV_MESH_SHADER_EXTENSION_NAME);

        //TODO:
        m_enabledSettings.MeshShading = m_supportedSettings.MeshShading;

        SetInitialized();
    }
}