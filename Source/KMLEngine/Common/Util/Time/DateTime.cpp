//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: DateTime.cpp
//------------------------------------------------------------

#include "DateTime.hpp"
#include "../../../Platform/Assert/Assert.hpp"
#include <fmt/chrono.h>
#include <iomanip>

namespace KMLEngine {
    DateTime::DateTime(std::time_t time) : m_time(time) {
        m_timeStruct = fmt::localtime(time);
    }

    std::string DateTime::ToString(const char* format) const {
        KML_ASSERT(format);
        
        std::stringstream stream;
        stream << std::put_time(&m_timeStruct, format);
        return stream.str();
    }
}
