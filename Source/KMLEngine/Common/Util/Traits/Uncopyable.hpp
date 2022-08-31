//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Uncopyable.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TRAITS_UNCOPYABLE_HPP
#define KMLENGINE_COMMON_UTIL_TRAITS_UNCOPYABLE_HPP

#pragma once

namespace KMLEngine {
    class Uncopyable {
    public:
        Uncopyable() noexcept = default;
        
        Uncopyable(const Uncopyable&) = delete;
        Uncopyable(Uncopyable&&) = delete;
        Uncopyable& operator =(const Uncopyable&) = delete;
        Uncopyable& operator =(Uncopyable&&) = delete;
    };
}

#endif //KMLENGINE_COMMON_UTIL_TRAITS_UNCOPYABLE_HPP
