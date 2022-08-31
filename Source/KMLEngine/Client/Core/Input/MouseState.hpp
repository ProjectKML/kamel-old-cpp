//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MouseState.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_INPUT_MOUSESTATE_HPP
#define KMLENGINE_CLIENT_CORE_INPUT_MOUSESTATE_HPP

#pragma once

#include "MouseButton.hpp"
#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Common/Util/Math/Point.hpp"

namespace KMLEngine {
	class MouseState {
	private:
		u32 m_state;

		i32 m_x, m_y;
	public:
		MouseState() noexcept : m_state(0), m_x(0), m_y(0) {}
		MouseState(u32 state, i32 x, i32 y) noexcept : m_state(state), m_x(x), m_y(y) {}

		[[nodiscard]] static MouseState Get() noexcept;

		[[nodiscard]] bool IsButtonDown(EMouseButton button) const noexcept;
		[[nodiscard]] bool IsButtonUp(EMouseButton button) const noexcept;

		[[nodiscard]] KML_FORCEINLINE i32 GetX() const noexcept { return m_x; }
		[[nodiscard]] KML_FORCEINLINE i32 GetY() const noexcept { return m_y; }

		[[nodiscard]] KML_FORCEINLINE u32 GetState() const noexcept { return m_state; }

		[[nodiscard]] KML_FORCEINLINE PointI32 GetPosition() const noexcept { return PointI32(m_x, m_y); }
	};
}

#endif //KMLENGINE_CLIENT_CORE_INPUT_MOUSESTATE_HPP
