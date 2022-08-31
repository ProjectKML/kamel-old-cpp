//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderSettingsManager.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_SETTINGS_RENDERSETTINGSMANAGER_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_SETTINGS_RENDERSETTINGSMANAGER_HPP

#pragma once

#include "../../../../../Platform/Hints/ForceInline.hpp"
#include "../../../../../Common/Util/Traits/Disposable.hpp"
#include "RenderSettings.hpp"
#include <functional>

namespace KMLEngine {
    class RenderContext;

    class RenderSettingsManager final : public Disposable<RenderSettingsManager> {
        friend Disposable<RenderSettingsManager>;
    private:
        RenderSettings m_supportedSettings;

        RenderSettings m_lastEnabledSettings;
        RenderSettings m_enabledSettings;

        void OnDisposing();
    public:
        void Create(RenderContext& context);

        template<typename Function>
        KML_FORCEINLINE void Update(Function&& callback) {
            if(m_lastEnabledSettings != m_enabledSettings) callback(m_lastEnabledSettings, m_enabledSettings);
            m_lastEnabledSettings = m_enabledSettings;
        }

        [[nodiscard]] KML_FORCEINLINE const RenderSettings& GetSupportedSettings() const noexcept { return m_supportedSettings; }

        [[nodiscard]] KML_FORCEINLINE RenderSettings& GetEnabledSettings() noexcept { return m_enabledSettings; }
        [[nodiscard]] KML_FORCEINLINE const RenderSettings& GetEnabledSettings() const noexcept { return m_enabledSettings; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_UTIL_SETTINGS_RENDERSETTINGSMANAGER_HPP