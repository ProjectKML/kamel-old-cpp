//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: TimeSpan.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TIME_TIMESPAN_HPP
#define KMLENGINE_COMMON_UTIL_TIME_TIMESPAN_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Platform/Assert/Assert.hpp"
#include <chrono>

namespace KMLEngine {
	class TimeSpan {
	private:
		static constexpr u64 _NANOS_PER_MILLISECOND = 1000000;
		static constexpr u64 _NANOS_PER_SECOND = 1000 * _NANOS_PER_MILLISECOND;
		static constexpr u64 _NANOS_PER_MINUTE = 60 * _NANOS_PER_SECOND;
		static constexpr u64 _NANOS_PER_HOUR = 60 * _NANOS_PER_MINUTE;
		static constexpr u64 _NANOS_PER_DAY = 24 * _NANOS_PER_HOUR;
	private:
		u64 m_nanoValue;
	public:
		explicit constexpr TimeSpan(u64 nanoValue = 0) noexcept : m_nanoValue(nanoValue) {}

		template<typename Rep, typename Period>
		explicit constexpr TimeSpan(std::chrono::duration<Rep, Period> duration) noexcept
			: m_nanoValue(std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count()) {}

		[[nodiscard]] KML_FORCEINLINE constexpr u64 GetTotalNanoseconds() const noexcept { return m_nanoValue; }
		[[nodiscard]] KML_FORCEINLINE constexpr u64 GetTotalMilliseconds() const noexcept { return m_nanoValue / _NANOS_PER_MILLISECOND; }
		[[nodiscard]] KML_FORCEINLINE constexpr u64 GetTotalSeconds() const noexcept { return m_nanoValue / _NANOS_PER_SECOND; }
		[[nodiscard]] KML_FORCEINLINE constexpr u64 GetTotalMinutes() const noexcept { return m_nanoValue / _NANOS_PER_MINUTE; }
		[[nodiscard]] KML_FORCEINLINE constexpr u64 GetTotalHours() const noexcept { return m_nanoValue / _NANOS_PER_HOUR; }
		[[nodiscard]] KML_FORCEINLINE constexpr u64 GetTotalDays() const noexcept { return m_nanoValue / _NANOS_PER_DAY; }

		[[nodiscard]] KML_FORCEINLINE constexpr f64 GetMilliseconds() const noexcept { return m_nanoValue / static_cast<f64>(_NANOS_PER_MILLISECOND); }
		[[nodiscard]] KML_FORCEINLINE constexpr f64 GetSeconds() const noexcept { return m_nanoValue / static_cast<f64>(_NANOS_PER_SECOND); }
		[[nodiscard]] KML_FORCEINLINE constexpr f64 GetMinutes() const noexcept { return m_nanoValue / static_cast<f64>(_NANOS_PER_MINUTE); }
		[[nodiscard]] KML_FORCEINLINE constexpr f64 GetHours() const noexcept { return m_nanoValue / static_cast<f64>(_NANOS_PER_HOUR); }
		[[nodiscard]] KML_FORCEINLINE constexpr f64 GetDays() const noexcept { return m_nanoValue / static_cast<f64>(_NANOS_PER_DAY); }

		[[nodiscard]] KML_FORCEINLINE TimeSpan operator +(const TimeSpan& other) const noexcept {
			return TimeSpan(m_nanoValue + other.m_nanoValue);
		}

		[[nodiscard]] KML_FORCEINLINE TimeSpan operator -(const TimeSpan& other) const noexcept {
			return TimeSpan(m_nanoValue - other.m_nanoValue);
		}

		KML_FORCEINLINE TimeSpan& operator +=(const TimeSpan& other) noexcept {
			m_nanoValue += other.m_nanoValue;
			return *this;
		}

		KML_FORCEINLINE TimeSpan& operator -=(const TimeSpan& other) noexcept {
			m_nanoValue -= other.m_nanoValue;
			return *this;
		}

		[[nodiscard]] KML_FORCEINLINE bool operator <(const TimeSpan& other) const noexcept {
			return m_nanoValue < other.m_nanoValue;
		}

		[[nodiscard]] KML_FORCEINLINE bool operator <=(const TimeSpan& other) const noexcept {
			return m_nanoValue <= other.m_nanoValue;
		}

		[[nodiscard]] KML_FORCEINLINE bool operator >(const TimeSpan& other) const noexcept {
			return m_nanoValue > other.m_nanoValue;
		}

		[[nodiscard]] KML_FORCEINLINE bool operator >=(const TimeSpan& other) const noexcept {
			return m_nanoValue >= other.m_nanoValue;
		}
	public:
		[[nodiscard]] KML_FORCEINLINE static constexpr TimeSpan FromNanoseconds(u64 nanoseconds) noexcept { return TimeSpan(nanoseconds); }
		[[nodiscard]] KML_FORCEINLINE static constexpr TimeSpan FromMilliseconds(u64 milliseconds) noexcept { return TimeSpan(milliseconds * _NANOS_PER_MILLISECOND); }
		[[nodiscard]] KML_FORCEINLINE static constexpr TimeSpan FromSeconds(u64 seconds) noexcept { return TimeSpan(seconds * _NANOS_PER_SECOND); }
		[[nodiscard]] KML_FORCEINLINE static constexpr TimeSpan FromMinutes(u64 minutes) noexcept { return TimeSpan(minutes * _NANOS_PER_MINUTE); }
		[[nodiscard]] KML_FORCEINLINE static constexpr TimeSpan FromHours(u64 hours) noexcept { return TimeSpan(hours * _NANOS_PER_HOUR); }
		[[nodiscard]] KML_FORCEINLINE static constexpr TimeSpan FromDays(u64 days) noexcept { return TimeSpan(days * _NANOS_PER_DAY); }

		[[nodiscard]] KML_FORCEINLINE static constexpr TimeSpan FromFrameLimit(u64 frameLimit) noexcept {
			KML_ASSERT(frameLimit);
			return TimeSpan(_NANOS_PER_SECOND / frameLimit);
		}

		[[nodiscard]] KML_FORCEINLINE static TimeSpan GetCurrentTime() noexcept {
			return TimeSpan(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		}
	};
}

#endif //KMLENGINE_COMMON_UTIL_TIME_TIMESPAN_HPP
