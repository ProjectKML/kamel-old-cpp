//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderFrameCollection.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMECOLLECTION_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMECOLLECTION_HPP

#pragma once

#include "RenderFrameManager.hpp"
#include <functional>
#include <type_traits>

namespace KMLEngine {
    class RenderFrameResources;
    
    template<typename T>
    class RenderFrameCollection final {
    private:
        T* m_objects = nullptr;
        usize m_size = 0;
    public:
        template<typename... Arguments>
        void Create(RenderFrameManager& frameManager, Arguments&&... arguments) {
            m_size = frameManager.GetNumFrameOverlaps();
            m_objects = new T[m_size];

            for(auto ix = 0; ix < m_size; ix++) {
                m_objects[ix].Create(frameManager.GetFrame(ix), std::forward<Arguments>(arguments)...);
            }
        }

        template<typename... Arguments>
        KML_FORCEINLINE void Destroy(Arguments&&... arguments) {
            for(auto ix = 0; ix < m_size; ix++) m_objects[ix].Dispose(std::forward<Arguments>(arguments)...);
            delete[] m_objects;

            m_objects = nullptr;
            m_size = 0;
        }

#ifdef KML_DEBUG
        ~RenderFrameCollection() noexcept {
            KML_ASSERT(!m_objects);
            KML_ASSERT(!m_size);
        }
#endif

        template<typename Function, typename... Arguments> requires(std::is_convertible_v<Function, std::function<void(T&, Arguments&&...)>>)
        KML_FORCEINLINE void ForEach(Function&& function, Arguments&&... arguments) {
            for(auto ix = 0; ix < m_size; ix++) function(m_objects[ix], std::forward<Arguments>(arguments)...); 
        }

        template<typename Function, typename... Arguments> requires(std::is_convertible_v<Function, std::function<void(const T&, Arguments&&...)>>)
        KML_FORCEINLINE void ForEach(Function&& function, Arguments&&... arguments) const {
            for(auto ix = 0; ix < m_size; ix++) function(m_objects[ix], std::forward<Arguments>(arguments)...);
        }

        template<typename Function, typename... Arguments> requires(std::is_convertible_v<Function, std::function<void(RenderFrameResources&, T&, Arguments&&...)>>)
        KML_FORCEINLINE void ForEach(RenderFrameManager& frameManager, Function&& function, Arguments&&... arguments) {
            for(auto ix = 0; ix < m_size; ix++) function(frameManager.GetFrame(ix), m_objects[ix], std::forward<Arguments>(arguments)...);
        }

        template<typename Function, typename... Arguments> requires(std::is_convertible_v<Function, std::function<void(const RenderFrameResources&, const T&, Arguments&&...)>>)
        KML_FORCEINLINE void ForEach(const RenderFrameManager& frameManager, Function&& function, Arguments&&... arguments) const {
            for(auto ix = 0; ix < m_size; ix++) function(frameManager.GetFrame(ix), m_objects[ix], std::forward<Arguments>(arguments)...);
        }

        template<typename RenderFrameResources>
        [[nodiscard]] KML_FORCEINLINE T& Get(const RenderFrameResources& currentFrame) noexcept { return m_objects[currentFrame.GetIndex()]; }

        template<typename RenderFrameResources>
        [[nodiscard]] KML_FORCEINLINE T& operator [](const RenderFrameResources& currentFrame) noexcept { return Get(currentFrame); }

        [[nodiscard]] KML_FORCEINLINE usize GetSize() const noexcept { return m_size; }

        [[nodiscard]] KML_FORCEINLINE T* GetObjects() noexcept { return m_objects; }
        [[nodiscard]] KML_FORCEINLINE const T* GetObjects() const noexcept { return m_objects; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMECOLLECTION_HPP
