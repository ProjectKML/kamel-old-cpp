//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderThreadManager.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADMANAGER_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADMANAGER_HPP

#pragma once

#include "../../../../Platform/Assert/Assert.hpp"
#include "../../../../Platform/Types.hpp"
#include "../../../../Platform/Hints/ForceInline.hpp"
#include "../../../../Common/Util/Traits/Disposable.hpp"
#include <moodycamel/blockingconcurrentqueue.h>
#include <optional>

namespace KMLEngine {
    namespace Vulkan { class Device; }
    
    template<typename T>
    class RenderThreadManager : public Disposable<RenderThreadManager<T>> {
        friend Disposable<RenderThreadManager<T>>;
    public:
        class ScopedHandle {
        private:
            T* m_collection = nullptr;
            RenderThreadManager* m_threadManager = nullptr;
        public:
            ScopedHandle() = default;
            ScopedHandle(RenderThreadManager* threadManager, T* collection) noexcept : m_collection(collection), m_threadManager(threadManager) {
                KML_ASSERT(threadManager);
                KML_ASSERT(collection);
            }

            virtual ~ScopedHandle() {
                if(m_collection) {
                    m_threadManager->Release(m_collection);
                    m_collection = nullptr;
                    m_threadManager = nullptr;    
                }
            }

            [[nodiscard]] KML_FORCEINLINE T* operator ->() noexcept {
                KML_ASSERT(m_collection);
                return m_collection;
            }

            [[nodiscard]] KML_FORCEINLINE const T* operator ->() const noexcept {
                KML_ASSERT(m_collection);
                return m_collection;
            }

            [[nodiscard]] KML_FORCEINLINE T& operator *() noexcept {
                KML_ASSERT(m_collection);
                return *m_collection;
            }

            [[nodiscard]] KML_FORCEINLINE const T& operator *() const noexcept {
                KML_ASSERT(m_collection);
                return *m_collection;
            }

            [[nodiscard]] KML_FORCEINLINE T** operator &() noexcept {
                KML_ASSERT(m_collection);
                return &m_collection;
            }

            [[nodiscard]] KML_FORCEINLINE T* const* operator &() const noexcept {
                KML_ASSERT(m_collection);
                return &m_collection;
            }

            [[nodiscard]] KML_FORCEINLINE operator T*() noexcept {
                KML_ASSERT(m_collection);
                return m_collection;
            }

            [[nodiscard]] KML_FORCEINLINE operator const T*() const noexcept {
                KML_ASSERT(m_collection);
                return m_collection;
            }
        };

        using Handle = T&;
    private:
        T* m_collections = nullptr;
        usize m_numThreads = 0;

        moodycamel::BlockingConcurrentQueue<T*> m_availableCollections;

        void OnDisposing() {
            for(auto ix = 0; ix < m_numThreads; ix++) m_collections[ix].Dispose();
            delete[] m_collections;

            m_collections = nullptr;
            m_numThreads = 0;
        }
    public:
        template<typename... Arguments>
        void Create(Vulkan::Device& device, u32 numThreads, Arguments&&... arguments) {
            KML_ASSERT(numThreads);

            m_numThreads = numThreads;

            m_collections = new T[numThreads];
            for(auto ix = 0; ix < numThreads; ix++) {
                m_collections[ix].Create(device, std::forward<Arguments>(arguments)...);

                const auto result = m_availableCollections.enqueue(m_collections + ix);
                KML_ASSERT(result);
            }

            this->SetInitialized();
        }

        [[nodiscard]] Handle Acquire() noexcept {
            T* collection;
            m_availableCollections.wait_dequeue(collection);
            return *collection;
        }

        [[nodiscard]] std::optional<Handle> TryAcquire() noexcept {
            T* collection;
            if(m_availableCollections.try_dequeue(collection)) return std::make_optional(collection);
            return std::nullopt;
        }

        [[nodiscard]] ScopedHandle AcquireScoped() noexcept {
            T* collection;
            m_availableCollections.wait_dequeue(collection);

            return ScopedHandle(this, collection);
        }

        void Release(T& collection) noexcept {
            const auto result = m_availableCollections.enqueue(&collection);
            KML_ASSERT(result);
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADMANAGER_HPP
