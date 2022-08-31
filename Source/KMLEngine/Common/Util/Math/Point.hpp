//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Point.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_MATH_POINT_HPP
#define KMLENGINE_COMMON_UTIL_MATH_POINT_HPP

#pragma once

#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Platform/Types.hpp"
#include "../HashCode.hpp"
#include <type_traits>

namespace KMLEngine {
	template<typename T>
	struct Point {
		T X, Y;

		constexpr Point() noexcept : X(static_cast<T>(0)), Y(static_cast<T>(0)) {}
		constexpr Point(T x, T y) noexcept : X(x), Y(y) {}

		template<typename U>
		[[nodiscard]] KML_FORCEINLINE Point<U> Cast() const noexcept { return Point<U>(static_cast<U>(X), static_cast<U>(Y)); }

		[[nodiscard]] KML_FORCEINLINE Point<T> operator +(const Point<T>& other) const noexcept {
			return Point<T>(X + other.X, Y + other.Y);
		}

		[[nodiscard]] KML_FORCEINLINE Point<T> operator -(const Point<T>& other) const noexcept {
			return Point<T>(X - other.X, Y - other.Y);
		}

		[[nodiscard]] KML_FORCEINLINE Point<T> operator *(const Point<T>& other) const noexcept {
			return Point<T>(X * other.X, Y * other.Y);
		}

		template<typename U>
		[[nodiscard]] KML_FORCEINLINE Point<T> operator *(const U& other) const noexcept {
			return Point<T>(X * static_cast<T>(other), Y * static_cast<T>(other));
		}

		[[nodiscard]] KML_FORCEINLINE Point<T> operator /(const Point<T>& other) const noexcept {
			return Point<T>(X / other.X, Y / other.Y);
		}

		template<typename U>
		[[nodiscard]] KML_FORCEINLINE Point<T> operator /(const U& other) const noexcept {
			return Point<T>(X / static_cast<T>(other), Y / static_cast<T>(other));
		}

		KML_FORCEINLINE Point<T>& operator +=(const Point<T>& other) noexcept {
			X += other.X;
			Y += other.Y;

			return *this;
		}

		KML_FORCEINLINE Point<T>& operator -=(const Point<T>& other) noexcept {
			X -= other.X;
			Y -= other.Y;

			return *this;
		}

		KML_FORCEINLINE Point<T>& operator *=(const Point<T>& other) noexcept {
			X *= other.X;
			Y *= other.Y;

			return *this;
		}

		template<typename U>
		KML_FORCEINLINE Point<T>& operator *=(const U& other) noexcept {
			X *= static_cast<T>(other);
			Y *= static_cast<T>(other);

			return *this;
		}

		KML_FORCEINLINE Point<T>& operator /=(const Point<T>& other) noexcept {
			X /= other.X;
			Y /= other.Y;

			return *this;
		}

		template<typename U>
		KML_FORCEINLINE Point<T>& operator /=(const U& other) noexcept {
			X /= static_cast<T>(other);
			Y /= static_cast<T>(other);

			return *this;
		}

		[[nodiscard]] KML_FORCEINLINE bool operator ==(const Point<T>& other) const noexcept {
			return X == other.X && Y == other.Y;
		}

		[[nodiscard]] KML_FORCEINLINE bool operator !=(const Point<T>& other) const noexcept {
			return X != other.X || Y != other.Y;
		}

		[[nodiscard]] static constexpr Point<T> Zero() noexcept { return Point<T>(); }
		[[nodiscard]] static constexpr Point<T> One() noexcept { return Point<T>(static_cast<T>(1), static_cast<T>(1)); }
	};

	using PointU8 = Point<u8>;
	using PointI8 = Point<i8>;
	using PointU16 = Point<u16>;
	using PointI16 = Point<i16>;
	using PointU32 = Point<u32>;
	using PointI32 = Point<i32>;
	using PointU64 = Point<u64>;
	using PointI64 = Point<i64>;
	using PointF32 = Point<f32>;
	using PointF64 = Point<f64>;
}

namespace std {
	using namespace KMLEngine;

	template<typename T>
	struct hash<Point<T>> {
		KML_FORCEINLINE usize operator ()(const Point<T>& point) const noexcept { return HashCode::Combine(point.X, point.Y); }
	};
}

#endif //KMLENGINE_COMMON_UTIL_MATH_POINT_HPP
