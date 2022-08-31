//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ConfigEngine.cpp
//------------------------------------------------------------

#include "ConfigEngine.hpp"

namespace KMLEngine {
    static const bool _DEFAULT_SHOULD_LOG_TO_FILE = false;

    void ConfigEngine::Serialize(toml::table& root) const {
        root = toml::table {{
            {
                "Logger", toml::table {{
                    { "ShouldLogToFile", Logger.ShouldLogToFile }
                }}
            }
        }};
    }

    void ConfigEngine::Deserialize(const toml::table& root) {
        const auto& logger = root["Logger"];
        Logger.ShouldLogToFile = logger["ShouldLogToFile"].value_or(_DEFAULT_SHOULD_LOG_TO_FILE);
    }

    void ConfigEngine::RestoreDefaults() noexcept {
        Logger.ShouldLogToFile = _DEFAULT_SHOULD_LOG_TO_FILE;
    }
}
