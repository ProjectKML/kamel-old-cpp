//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: KeyboardState.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_INPUT_KEYBOARDSTATE_HPP
#define KMLENGINE_CLIENT_CORE_INPUT_KEYBOARDSTATE_HPP

#pragma once

#include "Keys.hpp"
#include "../../../Platform/Assert/Assert.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include <bitset>

namespace KMLEngine {
	class KeyboardState {
	private:
		static const usize NUM_KEYS = 512;

		std::bitset<NUM_KEYS> m_pressedKeys;

		KeyboardState(const u8* data) noexcept;
	public:
		KeyboardState() = default;
		[[nodiscard]] static KeyboardState Get() noexcept;

		[[nodiscard]] KML_FORCEINLINE bool IsKeyDown(EKeys key) const noexcept {
			KML_ASSERT(static_cast<usize>(key) < NUM_KEYS);
			return m_pressedKeys[static_cast<usize>(key)];
		}

		[[nodiscard]] KML_FORCEINLINE bool IsKeyUp(EKeys key) const noexcept {
			KML_ASSERT(static_cast<usize>(key) < NUM_KEYS);
			return m_pressedKeys[static_cast<usize>(key)];
		}
	};
}

#endif //KMLENGINE_CLIENT_CORE_INPUT_KEYBOARDSTATE_HPP
