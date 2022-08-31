//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageFile.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEFILE_HPP
#define KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEFILE_HPP

#pragma once

#include "../../Util/Traits/Uncopyable.hpp"
#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Platform/Assert/Assert.hpp"
#include <filesystem>
#include <vector>
#include <memory_resource>

namespace KMLEngine {
	class PackageFile final : public Uncopyable {
	private:
		void* m_handle = nullptr;

		std::string m_name;
		std::filesystem::path m_path;

	public:
		explicit PackageFile(const char* name);
		~PackageFile();

		void GetEntry(const char* entryName, std::vector<byte>& buffer) const;
		void GetEntry(const char* entryName, std::pmr::vector<byte>& buffer, std::pmr::memory_resource& memoryResource) const;
		void GetEntry(const char* entryName, std::string& buffer) const;
		void GetEntry(const char* entryName, std::pmr::string& buffer, std::pmr::memory_resource& memoryResource) const;

        void GetEntry(const char* entryName, byte*& data, usize& size, std::pmr::memory_resource& memoryResource) const;

		bool Exists(const char* entryName) const noexcept;

		[[nodiscard]] KML_FORCEINLINE const std::string& GetName() const noexcept { return m_name; }
		[[nodiscard]] KML_FORCEINLINE const std::filesystem::path& GetTotalPath() const noexcept { return m_path; }
		
		[[nodiscard]] KML_FORCEINLINE void* GetHandle() const noexcept {
			KML_ASSERT(m_handle);
			return m_handle;
		}
	};
}

#endif //KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEFILE_HPP
