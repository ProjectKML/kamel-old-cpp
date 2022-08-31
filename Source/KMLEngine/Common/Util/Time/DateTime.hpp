//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: DateTime.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TIME_DATETIME_HPP
#define KMLENGINE_COMMON_UTIL_TIME_DATETIME_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include <ctime>
#include <string>

namespace KMLEngine {
    class DateTime final {
    private:
        std::time_t m_time;
        std::tm m_timeStruct;
    public:
        DateTime(std::time_t time);

        [[nodiscard]] std::string ToString(const char* format) const;

        [[nodiscard]] KML_FORCEINLINE i32 GetSeconds() const noexcept { return m_timeStruct.tm_sec; }
        [[nodiscard]] KML_FORCEINLINE i32 GetMinutes() const noexcept { return m_timeStruct.tm_min; }
        [[nodiscard]] KML_FORCEINLINE i32 GetHours() const noexcept { return m_timeStruct.tm_hour; }
        [[nodiscard]] KML_FORCEINLINE i32 GetDayOfMonth() const noexcept { return m_timeStruct.tm_mday; }
        [[nodiscard]] KML_FORCEINLINE i32 GetMonth() const noexcept { return m_timeStruct.tm_mon + 1; }
        [[nodiscard]] KML_FORCEINLINE i32 GetYear() const noexcept { return m_timeStruct.tm_year + 1900; }
        [[nodiscard]] KML_FORCEINLINE i32 GetDayOfWeek() const noexcept { return m_timeStruct.tm_wday; }
        [[nodiscard]] KML_FORCEINLINE i32 GetDayOfYear() const noexcept { return m_timeStruct.tm_yday; }

        [[nodiscard]] KML_FORCEINLINE std::time_t GetTime() const noexcept { return m_time; }
        [[nodiscard]] KML_FORCEINLINE const std::tm& GetTimeStruct() const noexcept { return m_timeStruct; }
    public:
        KML_FORCEINLINE static DateTime Now() { return DateTime(std::time(nullptr)); }
    };
}

#endif //KMLENGINE_COMMON_UTIL_TIME_DATETIME_HPP
