//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanObject.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANOBJECT_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANOBJECT_HPP

#pragma once

#include "Vulkan.hpp"
#include "../../../../Common/Util/Traits/Disposable.hpp"

namespace KMLEngine::Vulkan {
	template<typename T, VkObjectType ObjectType>
	class Object {
	protected:
		T m_handle = VK_NULL_HANDLE;

	public:
		[[nodiscard]] static constexpr VkObjectType GetObjectType() noexcept { return ObjectType; }
		
		[[nodiscard]] KML_FORCEINLINE T& GetHandle() noexcept {
			KML_ASSERT(m_handle);
			return m_handle;
		}

		[[nodiscard]] KML_FORCEINLINE const T& GetHandle() const noexcept {
			KML_ASSERT(m_handle);
			return m_handle;
		}

		[[nodiscard]] KML_FORCEINLINE operator T&() noexcept { return GetHandle(); }
		[[nodiscard]] KML_FORCEINLINE operator const T&() const noexcept { return GetHandle(); }
	};

	class Instance;
	class Surface;
	class PhysicalDevice;
	class Device;

	namespace Detail {
		class InstanceHolder {
		protected:
			Instance* m_instance = nullptr;

		public:
			[[nodiscard]] KML_FORCEINLINE Instance& GetVkInstance() noexcept {
				KML_ASSERT(m_instance);
				return *m_instance;
			}

			[[nodiscard]] KML_FORCEINLINE const Instance& GetVkInstance() const noexcept {
				KML_ASSERT(m_instance);
				return *m_instance;
			}
		};

		class SurfaceHolder {
		protected:
			Surface* m_surface = nullptr;

		public:
			[[nodiscard]] KML_FORCEINLINE Surface& GetSurface() noexcept {
				KML_ASSERT(m_surface);
				return *m_surface;
			}

			[[nodiscard]] KML_FORCEINLINE const Surface& GetSurface() const noexcept {
				KML_ASSERT(m_surface);
				return *m_surface;
			}
		};

		class PhysicalDeviceHolder {
		protected:
			PhysicalDevice* m_physicalDevice = nullptr;

		public:
			[[nodiscard]] KML_FORCEINLINE PhysicalDevice& GetPhysicalDevice() noexcept {
				KML_ASSERT(m_physicalDevice);
				return *m_physicalDevice;
			}

			[[nodiscard]] KML_FORCEINLINE const PhysicalDevice& GetPhysicalDevice() const noexcept {
				KML_ASSERT(m_physicalDevice);
				return *m_physicalDevice;
			}
		};

		class DeviceHolder {
		protected:
			Device* m_device = nullptr;

		public:
			[[nodiscard]] KML_FORCEINLINE Device& GetDevice() noexcept {
				KML_ASSERT(m_device);
				return *m_device;
			}

			[[nodiscard]] KML_FORCEINLINE const Device& GetDevice() const noexcept {
				KML_ASSERT(m_device);
				return *m_device;
			}
		};
	}

	template<typename T, VkObjectType ObjectType>
	class InstanceObject : public Object<T, ObjectType>, public Detail::InstanceHolder {};

	template<typename T, VkObjectType ObjectType>
	class SurfaceObject : public Object<T, ObjectType>, public Detail::SurfaceHolder {};

	template<typename T, VkObjectType ObjectType>
	class PhysicalDeviceObject : public Object<T, ObjectType>, public Detail::PhysicalDeviceHolder {};

	template<typename T, VkObjectType ObjectType>
	class InstancePhysicalDeviceObject : public Object<T, ObjectType>, public Detail::InstanceHolder, public Detail::PhysicalDeviceHolder {};

	template<typename T, VkObjectType ObjectType>
	class DeviceObject : public Object<T, ObjectType>, public Detail::DeviceHolder {};

	template<typename T, VkObjectType ObjectType>
	class SurfaceDeviceObject : public Object<T, ObjectType>, public Detail::SurfaceHolder, public Detail::DeviceHolder {};

	template<typename T, VkObjectType ObjectType>
	class InstanceDeviceObject : public Object<T, ObjectType>, public Detail::InstanceHolder, public Detail::DeviceHolder {};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANOBJECT_HPP