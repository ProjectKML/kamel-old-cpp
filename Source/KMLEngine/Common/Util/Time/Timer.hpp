//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Timer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TIME_TIMER_HPP
#define KMLENGINE_COMMON_UTIL_TIME_TIMER_HPP

#pragma once

#include "../Traits/Disposable.hpp"
#include "TimerEventArgs.hpp"
#include <functional>

namespace KMLEngine {
    class Timer : public Disposable<Timer> {
        friend Disposable<Timer>;
    private:
        TimeSpan m_intervalSpan;
        TimeSpan m_lastTime;

        TimeSpan m_deltaTime;
        TimeSpan m_totalTime;
		
        void OnDisposing();
    public:
        void Create();
	    
        KML_FORCEINLINE void SetIntervalSpan(TimeSpan intervalSpan) noexcept {
            m_intervalSpan = intervalSpan;
            m_deltaTime = intervalSpan;
        }

        void Tick(const std::function<void(const TimerEventArgs&)>& function);
    };
}

#endif //KMLENGINE_COMMON_UTIL_TIME_TIMER_HPP
