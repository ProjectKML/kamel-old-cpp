//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Color3f.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_MATH_COLOR3F_HPP
#define KMLENGINE_COMMON_UTIL_MATH_COLOR3F_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Common/Util/HashCode.hpp"
#include <functional>

namespace KMLEngine {
	struct Color3f {
		f32 R, G, B;

		Color3f() = default;
		constexpr Color3f(f32 r, f32 g, f32 b) noexcept
			: R(r)
			, G(g)
			, B(b) {
		}
		
		[[nodiscard]] KML_FORCEINLINE u32 Pack() const noexcept {
			const auto rr = static_cast<u8>(R * 255.0f);
			const auto rg = static_cast<u8>(G * 255.0f);
			const auto rb = static_cast<u8>(B * 255.0f);
			return (rr << 16u) | (rg << 8u) | rb;
		}

		[[nodiscard]] KML_FORCEINLINE u32 PackRgba(u8 alpha = 255) const noexcept {
			const auto rr = static_cast<u8>(R * 255.0f);
			const auto rg = static_cast<u8>(G * 255.0f);
			const auto rb = static_cast<u8>(B * 255.0f);

			return (rr << 24u) | (rg << 16u) | (rb << 8u) | alpha;
		}

		[[nodiscard]] KML_FORCEINLINE u32 PackArgb(u8 alpha = 255) const noexcept {
			const auto rr = static_cast<u8>(R * 255.0f);
			const auto rg = static_cast<u8>(G * 255.0f);
			const auto rb = static_cast<u8>(B * 255.0f);

			return (alpha << 24u) | (rr << 16u) | (rg << 8u) << rb;
		}

		[[nodiscard]] KML_FORCEINLINE bool operator ==(const Color3f& other) const noexcept { return R == other.R && G == other.G && B == other.B; }
		[[nodiscard]] KML_FORCEINLINE bool operator !=(const Color3f& other) const noexcept { return R != other.R || G != other.G || B != other.B; }

	public:
		[[nodiscard]] static constexpr Color3f FromRgb(u32 packedValue) noexcept {
			return Color3f(static_cast<f32>((packedValue >> 16u) & 0xFFu) / 255.0f, static_cast<f32>((packedValue >> 8u) & 0xFFu) / 255.0f,
			               static_cast<f32>(packedValue & 0xFFu) / 255.0f);
		}

		[[nodiscard]] static constexpr Color3f FromBgr(u32 packedValue) noexcept {
			return Color3f(static_cast<f32>(packedValue & 0xFFu) / 255.0f, static_cast<f32>((packedValue >> 8u) & 0xFFu) / 255.0f,
			               static_cast<f32>((packedValue >> 16u) & 0xFFu) / 255.0f);
		}

		[[nodiscard]] static KML_FORCEINLINE f32* GetRaw(Color3f& color) noexcept { return &color.R; }
		[[nodiscard]] static KML_FORCEINLINE const f32* GetRaw(const Color3f& color) noexcept { return &color.R; }
	};

	namespace Colors3 {
		constexpr Color3f Black = Color3f(0.0f, 0.0f, 0.0f);
		constexpr Color3f White = Color3f(1.0f, 1.0f, 1.0f);
		constexpr Color3f Red = Color3f(1.0f, 0.0f, 0.0f);
		constexpr Color3f CornflowerBlue = Color3f(100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f);
		constexpr Color3f Yellow = Color3f::FromRgb(0xFFD800);
		constexpr Color3f Cyan = Color3f::FromRgb(0x00FFAE);
		constexpr Color3f Green = Color3f(0.1f, 1.0f, 0.1f);

		namespace Literals {
			[[nodiscard]] constexpr Color3f operator "" _rgb(unsigned long long packedValue) noexcept {
				KML_ASSERT((packedValue & 0xFFFFFFFF00000000) == 0);
				return Color3f::FromRgb(static_cast<u32>(packedValue));
			}

			[[nodiscard]] constexpr Color3f operator "" _bgr(unsigned long long packedValue) noexcept {
				KML_ASSERT((packedValue & 0xFFFFFFFF00000000) == 0);
				return Color3f::FromBgr(static_cast<u32>(packedValue));
			}
		}
	}
}

namespace std {
	using namespace KMLEngine;

	template<>
	struct hash<Color3f> {
		KML_FORCEINLINE usize operator()(const Color3f& color) const noexcept { return HashCode::Combine(color.R, color.G, color.B); }
	};
}

#endif //KMLENGINE_COMMON_UTIL_MATH_COLOR3F_HPP
