//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Events.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_EVENT_EVENTS_HPP
#define KMLENGINE_COMMON_CORE_EVENT_EVENTS_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Client/Core/Input/Keys.hpp"
#include "../../../Client/Core/Input/MouseButton.hpp"

union SDL_Event;

namespace KMLEngine {
    struct SystemEvent {
        const SDL_Event* Event;

        SystemEvent() noexcept : Event(nullptr) {}
        explicit SystemEvent(const SDL_Event& event) noexcept : Event(&event) {};
    };

    struct WindowMoveEvent {
        i32 X, Y;

        WindowMoveEvent() noexcept : X(0), Y(0) {}
        WindowMoveEvent(i32 x, i32 y) noexcept : X(x), Y(y) {}
    };

    struct WindowResizeEvent {
        u32 Width, Height;

        WindowResizeEvent() noexcept : Width(0), Height(0) {}
        WindowResizeEvent(u32 width, u32 height) noexcept : Width(width), Height(height) {}
    };

    struct WindowMinimizeEvent {};
    struct WindowMaximizeEvent {};

    struct KeyDownEvent {
        EKeys Key;

        explicit KeyDownEvent(EKeys key) noexcept : Key(key) {}
    };

    struct KeyUpEvent {
        EKeys Key;

        explicit KeyUpEvent(EKeys key) noexcept : Key(key) {}
    };

    struct KeyPressEvent {
        EKeys Key;

        explicit KeyPressEvent(EKeys key) noexcept : Key(key) {}
    };

    struct KeyReleaseEvent {
        EKeys Key;

        explicit KeyReleaseEvent(EKeys key) noexcept : Key(key) {}
    };

    struct MouseButtonDownEvent {
        EMouseButton Button;
        i32 X, Y;

        explicit MouseButtonDownEvent(EMouseButton button, i32 x, i32 y) noexcept : Button(button), X(x), Y(y) {}
    };

    struct MouseButtonUpEvent {
        EMouseButton Button;
        i32 X, Y;

        explicit MouseButtonUpEvent(EMouseButton button, i32 x, i32 y) noexcept : Button(button), X(x), Y(y) {}
    };

    struct MouseMotionEvent {
        i32 X, Y;
        i32 DeltaX, DeltaY;

        explicit MouseMotionEvent(i32 x, i32 y, i32 deltaX, i32 deltaY) noexcept : X(x), Y(y), DeltaX(deltaX), DeltaY(deltaY) {}
    };

    struct MouseScrollEvent {
        i32 X, Y;

        explicit MouseScrollEvent(i32 x, i32 y) noexcept : X(x), Y(y) {}
    };
}

#endif //KMLENGINE_COMMON_CORE_EVENT_EVENTS_HPP
