//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: EventBus.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_EVENT_EVENTBUS_HPP
#define KMLENGINE_COMMON_CORE_EVENT_EVENTBUS_HPP

#pragma once

#include "../../Util/Traits/Singleton.hpp"
#include "../../Util/Traits/Uncopyable.hpp"
#include "Events.hpp"
#include <type_traits>
#include <tuple>
#include <vector>
#include <functional>

namespace KMLEngine {
    class EventBus : public Uncopyable, public Singleton<EventBus> {
    private:
        template<typename T>
        using FunctionType = std::conditional_t<std::is_empty_v<T>, std::function<void()>, std::function<void(const T&)>>;

        template<typename T>
        struct FunctionWrapper {
            FunctionType<T> Function;

            FunctionWrapper() noexcept = default;
            FunctionWrapper(FunctionType<T> function) noexcept : Function(std::move(function)) {}

            template<typename... Arguments>
            KML_FORCEINLINE void operator ()(Arguments&&... arguments) { Function(std::forward<Arguments>(arguments)...); }
        };
        
        template<typename... Events>
        class RegistryContainer {
        private:
            std::tuple<std::vector<FunctionWrapper<Events>>...> m_registries;
        public:
            template<typename T>
            [[nodiscard]] KML_FORCEINLINE std::vector<FunctionWrapper<T>>& Get() noexcept { return std::get<std::vector<FunctionWrapper<T>>>(m_registries); }

            template<typename T>
            [[nodiscard]] KML_FORCEINLINE const std::vector<FunctionWrapper<T>>& Get() const noexcept { return std::get<std::vector<FunctionWrapper<T>>>(m_registries); }
        };

        template<typename T, typename F> requires(std::is_same_v<F, std::function<void()>> || std::is_same_v<F, std::function<void(const T&)>>)
        KML_FORCEINLINE usize AddInternal(F function) noexcept {
            KML_ASSERT(function);

            auto& registry = m_registryContainer.Get<T>();
            const auto id = registry.size();
            registry.push_back(std::move(function));
            
            return id;
        }
        
        RegistryContainer<SystemEvent,
                          WindowMoveEvent,
                          WindowResizeEvent,
                          WindowMinimizeEvent,
                          WindowMaximizeEvent,
                          KeyDownEvent,
                          KeyUpEvent,
                          KeyPressEvent,
                          KeyReleaseEvent,
                          MouseButtonDownEvent,
                          MouseButtonUpEvent,
                          MouseMotionEvent,
                          MouseScrollEvent> m_registryContainer;
    public:
        EventBus();
        ~EventBus();

        template<typename T> requires(std::is_empty_v<T>)
        KML_FORCEINLINE usize Add(std::function<void()> function) {
            KML_ASSERT(function);
            return AddInternal<T, std::function<void()>>(function);
        }

        template<typename T> requires(!std::is_empty_v<T>)
        KML_FORCEINLINE usize Add(std::function<void(const T&)> function) {
            KML_ASSERT(function);
            return AddInternal<T, std::function<void(const T&)>>(function);
        }

        template<typename T>
        void Remove(usize id) {
            auto& registry = m_registryContainer.Get<T>();
            registry.erase(registry.begin() + id);
        }

        template<typename T, typename... Arguments>
        KML_FORCEINLINE void Post(Arguments&&... arguments) {
            for(auto& registry = m_registryContainer.Get<T>(); auto& listener : registry) listener(std::forward<Arguments>(arguments)...);
        }
        
        template<typename T, typename... Arguments>
        KML_FORCEINLINE void PostEmplace(Arguments&&... arguments) {
            if constexpr(std::is_empty_v<T>) {
                static_assert(sizeof...(Arguments) == 0, "Static events do not have arguments!");
                Post<T>();
            }
            else Post<T>(T(std::forward<Arguments>(arguments)...));
        }
    };
}

#endif //KMLENGINE_COMMON_CORE_EVENT_EVENTBUS_HPP
