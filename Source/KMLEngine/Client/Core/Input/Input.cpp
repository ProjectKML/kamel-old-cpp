//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Input.cpp
//------------------------------------------------------------

#include "Input.hpp"
#include "KeyboardState.hpp"
#include "Mouse.hpp"
#include "MouseState.hpp"
#include "../Window/Window.hpp"

namespace KMLEngine::Input {
    static KeyboardState _LAST_KEYBOARD_STATE;
    static KeyboardState _KEYBOARD_STATE;
    static MouseState _LAST_MOUSE_STATE;
    static MouseState _MOUSE_STATE;

    void Refresh() noexcept {
        _LAST_KEYBOARD_STATE = _KEYBOARD_STATE;
        _KEYBOARD_STATE = KeyboardState::Get();

        _LAST_MOUSE_STATE = _MOUSE_STATE;
        const auto currentState = MouseState::Get();

        const auto deltaPosition = currentState.GetPosition() - _LAST_MOUSE_STATE.GetPosition();
        Mouse::SetPositionCentered(Window::GetInstance());

        _MOUSE_STATE = MouseState::Get();

        const auto newLastState = _MOUSE_STATE.GetState();
        const auto newLastX = _MOUSE_STATE.GetX() + deltaPosition.X;
        const auto newLastY = _MOUSE_STATE.GetY() + deltaPosition.Y;
        _LAST_MOUSE_STATE = MouseState(newLastState, newLastX, newLastY);
    }

    //Current frame
    bool IsKeyDown(EKeys key) noexcept { return _KEYBOARD_STATE.IsKeyDown(key); }
    bool IsKeyUp(EKeys key) noexcept { return _KEYBOARD_STATE.IsKeyUp(key); }

    const KeyboardState& GetKeyboardState() noexcept { return _KEYBOARD_STATE; }

    bool IsMouseButtonDown(EMouseButton button) noexcept { return _MOUSE_STATE.IsButtonDown(button); }
    bool IsMouseButtonUp(EMouseButton button) noexcept { return _MOUSE_STATE.IsButtonUp(button); }

    i32 GetMouseX() noexcept { return _MOUSE_STATE.GetX(); }
    i32 GetMouseY() noexcept { return _MOUSE_STATE.GetY(); }
    PointI32 GetMousePosition() noexcept { return _MOUSE_STATE.GetPosition(); }

    const MouseState& GetMouseState() noexcept { return _MOUSE_STATE; }

    //Last frame
    bool IsLastKeyDown(EKeys key) noexcept { return _LAST_KEYBOARD_STATE.IsKeyDown(key); }
    bool IsLastKeyUp(EKeys key) noexcept { return _LAST_KEYBOARD_STATE.IsKeyUp(key); }

    const KeyboardState& GetLastKeyboardState() noexcept { return _LAST_KEYBOARD_STATE; }

    bool IsLastMouseButtonDown(EMouseButton button) noexcept { return _LAST_MOUSE_STATE.IsButtonDown(button); }
    bool IsLastMouseButtonUp(EMouseButton button) noexcept { return _LAST_MOUSE_STATE.IsButtonUp(button); }

    i32 GetLastMouseX() noexcept { return _LAST_MOUSE_STATE.GetX(); }
    i32 GetLastMouseY() noexcept { return _LAST_MOUSE_STATE.GetY(); }
    PointI32 GetLastMousePosition() noexcept { return _LAST_MOUSE_STATE.GetPosition(); }

    const MouseState& GetLastMouseState() noexcept { return _LAST_MOUSE_STATE; }
}
