//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: TimerEventArgs.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TIME_TIMEREVENTARGS_HPP
#define KMLENGINE_COMMON_UTIL_TIME_TIMEREVENTARGS_HPP

#pragma once

#include "TimeSpan.hpp"

namespace KMLEngine {
    struct TimerEventArgs {
        TimeSpan DeltaTime;
        TimeSpan TotalTime;

        constexpr TimerEventArgs(TimeSpan deltaTime, TimeSpan totalTime) noexcept : DeltaTime(deltaTime), TotalTime(totalTime) {}
    };
}

#endif //KMLENGINE_COMMON_UTIL_TIME_TIMEREVENTARGS_HPP
