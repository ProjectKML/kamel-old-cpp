//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageFile.cpp
//------------------------------------------------------------

#include "PackageFile.hpp"
#include "PackageException.hpp"
#include <fmt/format.h>
#include <zip/zip.h>

namespace KMLEngine {
	PackageFile::PackageFile(const char* name) {
		KML_ASSERT(name);

		m_name = name;
		m_path = std::filesystem::current_path() / "Common" / (m_name + ".kmlpak");

		m_handle = zip_open(m_path.string().c_str(), 0, 'r');
		if(!m_handle) throw PackageException(fmt::format("Failed to open file: {}.kmlpak", name));
	}
	
	PackageFile::~PackageFile() {
		zip_close(static_cast<zip_t*>(m_handle));
		m_handle = nullptr;
	}
	
	void PackageFile::GetEntry(const char* entryName, std::vector<byte>& buffer) const {
		KML_ASSERT(entryName);
		KML_ASSERT(buffer.empty());

		if(zip_entry_open(static_cast<zip_t*>(m_handle), entryName) < 0) throw PackageException(fmt::format("Open entry failed: {}", entryName));

		const auto size = zip_entry_size(static_cast<zip_t*>(m_handle));
		buffer.resize(size);

		if(zip_entry_noallocread(static_cast<zip_t*>(m_handle), buffer.data(), buffer.size()) < 0)
			throw PackageException(fmt::format("Reading entry failed: {}", entryName));

		zip_entry_close(static_cast<zip_t*>(m_handle));
	}
	
	void PackageFile::GetEntry(const char* entryName, std::pmr::vector<byte>& buffer, std::pmr::memory_resource& memoryResource) const {
		KML_ASSERT(entryName);
		KML_ASSERT(buffer.empty());

		if(zip_entry_open(static_cast<zip_t*>(m_handle), entryName) < 0) throw PackageException(fmt::format("Open entry failed: {}", entryName));

		const auto size = zip_entry_size(static_cast<zip_t*>(m_handle));
		buffer = std::pmr::vector<byte>(&memoryResource);
		buffer.resize(size);

		if(zip_entry_noallocread(static_cast<zip_t*>(m_handle), buffer.data(), buffer.size()) < 0)
			throw PackageException(fmt::format("Reading entry failed: {}", entryName));

		zip_entry_close(static_cast<zip_t*>(m_handle));
	}
	
	void PackageFile::GetEntry(const char* entryName, std::string& buffer) const {
		KML_ASSERT(entryName);
		KML_ASSERT(buffer.empty());

		if(zip_entry_open(static_cast<zip_t*>(m_handle), entryName) < 0) throw PackageException(fmt::format("Open entry failed: {}", entryName));
		const auto size = zip_entry_size(static_cast<zip_t*>(m_handle));
		buffer.resize(size);

		if(zip_entry_noallocread(static_cast<zip_t*>(m_handle), buffer.data(), buffer.size()) < 0)
			throw PackageException(fmt::format("Reading entry failed: {}", entryName));

		zip_entry_close(static_cast<zip_t*>(m_handle));
	}

	void PackageFile::GetEntry(const char* entryName, std::pmr::string& buffer, std::pmr::memory_resource& memoryResource) const {
		KML_ASSERT(entryName);
		KML_ASSERT(buffer.empty());

		if(zip_entry_open(static_cast<zip_t*>(m_handle), entryName) < 0) throw PackageException(fmt::format("Open entry failed: {}", entryName));
		const auto size = zip_entry_size(static_cast<zip_t*>(m_handle));

		buffer = std::pmr::string(&memoryResource);
		buffer.resize(size);

		if(zip_entry_noallocread(static_cast<zip_t*>(m_handle), buffer.data(), buffer.size()) < 0)
			throw PackageException(fmt::format("Reading entry failed: {}", entryName));

		zip_entry_close(static_cast<zip_t*>(m_handle));
	}

    void PackageFile::GetEntry(const char* entryName, byte*& data, usize& size, std::pmr::memory_resource& memoryResource) const {
        KML_ASSERT(entryName);

        if(zip_entry_open(static_cast<zip_t*>(m_handle), entryName) < 0) throw PackageException(fmt::format("Open entry failed: {}", entryName));
        size = zip_entry_size(static_cast<zip_t*>(m_handle));
        data = static_cast<byte*>(memoryResource.allocate(size));

        if(zip_entry_noallocread(static_cast<zip_t*>(m_handle), data, size) < 0)
            throw PackageException(fmt::format("Reading entry failed: {}", entryName));

        zip_entry_close(static_cast<zip_t*>(m_handle));
    }

	bool PackageFile::Exists(const char* entryName) const noexcept {
		KML_ASSERT(entryName);

		const auto result = zip_entry_open(static_cast<zip_t*>(m_handle), entryName) >= 0;
		if(result) zip_entry_close(static_cast<zip_t*>(m_handle));
		return result;
	}
}
