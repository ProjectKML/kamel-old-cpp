//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ConfigClient.cpp
//------------------------------------------------------------

#include "ConfigClient.hpp"

namespace KMLEngine {
	static const usize _DEFAULT_FRAME_LIMIT = 60;

	static const usize _DEFAULT_WIDTH = 1600;
	static const usize _DEFAULT_HEIGHT = 900;
	static const bool _DEFAULT_FULLSCREEN = false;

	void ConfigClient::Serialize(toml::table& root) const {
		root = toml::table {{
				{
					"Timer", toml::table {{
						{ "FrameLimit", Timer.FrameLimit }
					}}
				},
				{
					"Window", toml::table {{
						{ "Width", Window.Width },
						{ "Height", Window.Height },
						{ "Fullscreen", Window.Fullscreen }
					}}
				}
			}
		};
	}

	void ConfigClient::Deserialize(const toml::table& root) {
		const auto& timer = root["Timer"];
		Timer.FrameLimit = timer["FrameLimit"].value_or(_DEFAULT_FRAME_LIMIT);

		const auto& window = root["Window"];
		Window.Width = window["Width"].value_or(_DEFAULT_WIDTH);
		Window.Height = window["Height"].value_or(_DEFAULT_HEIGHT);
		Window.Fullscreen = window["Fullscreen"].value_or(_DEFAULT_FULLSCREEN);
	}

	void ConfigClient::RestoreDefaults() noexcept {
		Timer.FrameLimit = _DEFAULT_FRAME_LIMIT;

		Window.Width = _DEFAULT_WIDTH;
		Window.Height = _DEFAULT_HEIGHT;
		Window.Fullscreen = false;
	}
}
