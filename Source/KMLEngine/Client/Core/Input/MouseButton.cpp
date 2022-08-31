//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MouseButton.cpp
//------------------------------------------------------------

#include "MouseButton.hpp"

namespace KMLEngine::MouseButton {
	const char* GetName(EMouseButton button) noexcept {
		switch(button) {
		case EMouseButton::Left:
			return "Left";
		case EMouseButton::Middle:
			return "Middle";
		case EMouseButton::Right:
			return "Right";
		case EMouseButton::X1:
			return "X1";
		case EMouseButton::X2:
			return "X2";
		default:
			return "Unknown";
		}
	}
}