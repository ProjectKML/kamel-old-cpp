//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Color4f.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_MATH_COLOR4F_HPP
#define KMLENGINE_COMMON_UTIL_MATH_COLOR4F_HPP

#pragma once

#include "Color3f.hpp"

namespace KMLEngine {
	struct Color4f {
		f32 R, G, B, A;

		Color4f() = default;
		constexpr Color4f(f32 r, f32 g, f32 b, f32 a = 1.0f) noexcept : R(r), G(g), B(b), A(a) {}
		constexpr Color4f(const Color3f& rgb, f32 a = 1.0f) noexcept : R(rgb.R), G(rgb.G), B(rgb.B), A(a) {}

		[[nodiscard]] KML_FORCEINLINE u32 PackRgba() const noexcept {
			const auto br = static_cast<u8>(R * 255.0f);
			const auto bg = static_cast<u8>(G * 255.0f);
			const auto bb = static_cast<u8>(B * 255.0f);
			const auto ba = static_cast<u8>(A * 255.0f);

			return (br << 24u) | (bg << 16u) | (bb << 8u) | ba;
		}

		[[nodiscard]] KML_FORCEINLINE u32 PackAbgr() const noexcept {
			const auto br = static_cast<u8>(R * 255.0f);
			const auto bg = static_cast<u8>(G * 255.0f);
			const auto bb = static_cast<u8>(B * 255.0f);
			const auto ba = static_cast<u8>(A * 255.0f);

			return (ba << 24u) | (bb << 16u) | (bg << 8u) | br;
		}

		[[nodiscard]] KML_FORCEINLINE u32 PackArgb() const noexcept {
			const auto br = static_cast<u8>(R * 255.0f);
			const auto bg = static_cast<u8>(G * 255.0f);
			const auto bb = static_cast<u8>(B * 255.0f);
			const auto ba = static_cast<u8>(A * 255.0f);

			return (ba << 24u) | (br << 16u) | (bg << 8u) | bb;
		}

		[[nodiscard]] KML_FORCEINLINE u32 PackRgb() const noexcept {
			const auto rr = static_cast<u8>(R * 255.0f);
			const auto rg = static_cast<u8>(G * 255.0f);
			const auto rb = static_cast<u8>(B * 255.0f);
			return (rr << 16u) | (rg << 8u) | rb;
		}

		[[nodiscard]] KML_FORCEINLINE Color3f GetRgb() const noexcept { return Color3f(R, G, B); }

		[[nodiscard]] KML_FORCEINLINE bool operator ==(const Color4f& other) const noexcept { return R == other.R && G == other.G && B == other.B && A == other.A; }
		[[nodiscard]] KML_FORCEINLINE bool operator !=(const Color4f& other) const noexcept { return R != other.R || G != other.G || B != other.B || A != other.A; }
	public:
		[[nodiscard]] static constexpr Color4f FromRgba(u32 packedValue) noexcept {
			return Color4f(static_cast<f32>((packedValue >> 24u) & 0xFFu) / 255.0f, static_cast<f32>((packedValue >> 16u) & 0xFFu) / 255.0f,
				static_cast<f32>((packedValue >> 8u) & 0xFFu) / 255.0f, static_cast<f32>(packedValue & 0xFFu) / 255.0f);
		}

		[[nodiscard]] static constexpr Color4f FromArgb(u32 packedValue) noexcept {
			return Color4f(static_cast<f32>(packedValue & 0xFFu) / 255.0f, static_cast<f32>((packedValue >> 24u) & 0xFFu) / 255.0f,
				static_cast<f32>((packedValue >> 16u) & 0xFFu) / 255.0f, static_cast<f32>((packedValue >> 8u) & 0xFFu) / 255.0f);
		}

		[[nodiscard]] static constexpr Color4f FromAbgr(u32 packedValue) noexcept {
			return Color4f(static_cast<f32>(packedValue & 0xFFu) / 255.0f, static_cast<f32>((packedValue >> 8u) & 0xFFu) / 255.0f,
			static_cast<f32>((packedValue >> 16u) & 0xFFu) / 255.0f, static_cast<f32>((packedValue >> 24u) & 0xFFu) / 255.0f);
		}
		
		[[nodiscard]] static KML_FORCEINLINE f32* GetRaw(Color4f& color) noexcept { return &color.R; }
		[[nodiscard]] static KML_FORCEINLINE const f32* GetRaw(const Color4f& color) noexcept { return &color.R; }
	};

	namespace Colors4 {
		constexpr Color4f Black = Color4f(Colors3::Black.R, Colors3::Black.G, Colors3::Black.B, 1.0f);
		constexpr Color4f White = Color4f(Colors3::White.R, Colors3::White.G, Colors3::White.B, 1.0f);
		constexpr Color4f Red = Color4f(Colors3::Red.R, Colors3::Red.G, Colors3::Red.B, 1.0f);
		constexpr Color4f CornflowerBlue = Color4f(Colors3::CornflowerBlue.R, Colors3::CornflowerBlue.G, Colors3::CornflowerBlue.B, 1.0f);
		constexpr Color4f Yellow = Color4f(Colors3::Yellow.R, Colors3::Yellow.G, Colors3::Yellow.B, 1.0f);
		constexpr Color4f Cyan = Color4f(Colors3::Cyan.R, Colors3::Cyan.G, Colors3::Cyan.B, 1.0f);
		constexpr Color4f Green = Color4f(Colors3::Green.R, Colors3::Green.G, Colors3::Green.B, 1.0f);

		namespace Literals {
			[[nodiscard]] constexpr Color4f operator "" _rgba(unsigned long long packedValue) noexcept {
				KML_ASSERT((packedValue & 0xFFFFFFFF00000000) == 0);
				return Color4f::FromRgba(static_cast<u32>(packedValue));
			}

			[[nodiscard]] constexpr Color4f operator "" _argb(unsigned long long packedValue) noexcept {
				KML_ASSERT((packedValue & 0xFFFFFFFF00000000) == 0);
				return Color4f::FromArgb(static_cast<u32>(packedValue));
			}

			[[nodiscard]] constexpr Color4f operator "" _abgr(unsigned long long packedValue) noexcept {
				KML_ASSERT((packedValue & 0xFFFFFFFF00000000) == 0);
				return Color4f::FromAbgr(static_cast<u32>(packedValue));
			}
		}
	}
}

namespace std {
	using namespace KMLEngine;

	template<>
	struct hash<Color4f> {
		KML_FORCEINLINE usize operator()(const Color4f& color) const noexcept { return HashCode::Combine(color.R, color.G, color.B, color.A); }
	};
}

#endif //KMLENGINE_COMMON_UTIL_MATH_COLOR4F_HPP
