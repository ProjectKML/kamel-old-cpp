//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: CustomFlagFormatters.cpp
//------------------------------------------------------------

#include "CustomFlagFormatters.hpp"
#include "../../Util/Thread/ThreadExtensions.hpp"

namespace KMLEngine {
    void LogThreadNameFormatter::format(const spdlog::details::log_msg& message, const std::tm&, spdlog::memory_buf_t& buffer) {
        auto name = ThreadExtensions::GetCurrentThreadName();
        if(name.empty()) name = fmt::format("{}", message.thread_id);
        buffer.append(name);
    }
}