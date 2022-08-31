//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Timer.cpp
//------------------------------------------------------------

#include "Timer.hpp"

namespace KMLEngine {
    void Timer::OnDisposing() {}
	
    void Timer::Create() { SetInitialized(); }
	
    void Timer::Tick(const std::function<void(const TimerEventArgs&)>& function) {
        KML_ASSERT(function);

        const auto startTime = TimeSpan::GetCurrentTime();
        const auto targetTime = startTime + m_intervalSpan;

        const TimerEventArgs timerEventArgs(m_deltaTime, m_totalTime);
        function(timerEventArgs);

        if(const auto endTime = TimeSpan::GetCurrentTime(); endTime < targetTime) {
            const auto sleepTime = targetTime - endTime;
            while(TimeSpan::GetCurrentTime() < targetTime); //TODO: see timing things
        }

        m_totalTime = TimeSpan::GetCurrentTime();
        m_deltaTime = m_totalTime - startTime;
    }
}