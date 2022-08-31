//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Input.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_INPUT_INPUT_HPP
#define KMLENGINE_CLIENT_CORE_INPUT_INPUT_HPP

#pragma once

#include "Keys.hpp"
#include "MouseButton.hpp"
#include "../../../Common/Util/Math/Point.hpp"

namespace KMLEngine {
	class KeyboardState;
	class MouseState;
	namespace Input {
		void Refresh() noexcept;

		//Current frame
		[[nodiscard]] bool IsKeyDown(EKeys key) noexcept;
		[[nodiscard]] bool IsKeyUp(EKeys key) noexcept;

		[[nodiscard]] const KeyboardState& GetKeyboardState() noexcept;

		[[nodiscard]] bool IsMouseButtonDown(EMouseButton button) noexcept;
		[[nodiscard]] bool IsMouseButtonUp(EMouseButton button) noexcept;

		[[nodiscard]] i32 GetMouseX() noexcept;
		[[nodiscard]] i32 GetMouseY() noexcept;
		[[nodiscard]] PointI32 GetMousePosition() noexcept;

		[[nodiscard]] const MouseState& GetMouseState() noexcept;

		//Last frame
		[[nodiscard]] bool IsLastKeyDown(EKeys key) noexcept;
		[[nodiscard]] bool IsLastKeyUp(EKeys key) noexcept;

		[[nodiscard]] const KeyboardState& GetLastKeyboardState() noexcept;
		
		[[nodiscard]] bool IsLastMouseButtonDown(EMouseButton button) noexcept;
		[[nodiscard]] bool IsLastMouseButtonUp(EMouseButton button) noexcept;

		[[nodiscard]] i32 GetLastMouseX() noexcept;
		[[nodiscard]] i32 GetLastMouseY() noexcept;
		[[nodiscard]] PointI32 GetLastMousePosition() noexcept;

		[[nodiscard]] const MouseState& GetLastMouseState() noexcept;
	}
}

#endif //KMLENGINE_CLIENT_CORE_INPUT_INPUT_HPP
