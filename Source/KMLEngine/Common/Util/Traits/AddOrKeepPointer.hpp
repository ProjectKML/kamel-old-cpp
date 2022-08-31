//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: AddOrKeepPointer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TRAITS_ADDORKEEPPOINTER_HPP
#define KMLENGINE_COMMON_UTIL_TRAITS_ADDORKEEPPOINTER_HPP

#pragma once

namespace KMLEngine {
    template<typename T>
    struct AddOrKeepPointer {
        using Type = T*;
    };
	
    template<typename T>
    struct AddOrKeepPointer<T*> {
        using Type = T*;
    };
}

#endif //KMLENGINE_COMMON_UTIL_TRAITS_ADDORKEEPPOINTER_HPP
