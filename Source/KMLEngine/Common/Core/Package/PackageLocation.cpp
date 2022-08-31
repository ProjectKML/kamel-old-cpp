//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageLocation.cpp
//------------------------------------------------------------

#include "PackageLocation.hpp"
#include "PackageException.hpp"
#include "PackageManager.hpp"
#include "PackageFile.hpp"

namespace KMLEngine {
	PackageLocation::PackageLocation(const std::string_view& fullName) {
		if(fullName.empty()) return;

		const auto size = fullName.size();
		const auto sizeMinusOne = fullName.size() - 1;

		auto splitPos = std::string_view::npos;

		for(auto ix = 0; ix < size; ix++) {
			const auto c = fullName[ix];
			if(c == ':') {
				if(ix == 0 || ix == sizeMinusOne || splitPos != std::string_view::npos) throw PackageException("Invalid location");
				splitPos = ix;
			}
		}

		if(splitPos == std::string_view::npos) throw PackageException("Invalid location");

		m_fileName = std::string(fullName.data(), splitPos);
		m_entryName = std::string(fullName.data() + splitPos + 1, fullName.size() - splitPos - 1);
	}

	PackageLocation PackageLocation::GetPrefixed(const std::string_view& prefix) const {
		return PackageLocation(m_fileName, fmt::format("{}{}", prefix, m_entryName));
	}

	PackageLocation PackageLocation::GetSuffixed(const std::string_view& suffix) const {
		return PackageLocation(m_fileName, fmt::format("{}{}", m_entryName, suffix));
	}

	static void GetParentPath(std::string& path) {
	    while(!path.empty() && !path.ends_with('/')) path.pop_back();
	    if(!path.empty()) path.pop_back();
	}

	static KML_FORCEINLINE void AppendPath(std::string& path, const std::string_view& p) {
	    if(!path.empty() && !path.ends_with('/')) path.push_back('/');
	    path.append(p);
	}

    PackageLocation PackageLocation::GetRelativeToCurrent(const std::string_view& relativePath) const {
	    std::string newPath = m_entryName;

        GetParentPath(newPath);

	    u32 state = 0, startIndex = 0, endIndex = 0;

	    for(auto i = 0; i < relativePath.size(); i++) {
	        const auto c = relativePath[i];

	        if(state == 0 && c == '.') state = 1;
	        else if(state == 1) {
	            if(c == '.') state = 2;
	            else if(c == '/') state = 3;
	            else state = 0;
	        }
	        if(c == '/') {
	            if(state == 0 && startIndex != endIndex) {
                    AppendPath(newPath, std::string_view(relativePath.begin() + startIndex, relativePath.begin() + endIndex - 1));
	                startIndex = endIndex;
	            }
	            else if(state == 2) {
	                startIndex += 3;
	                endIndex = startIndex;

                    GetParentPath(newPath);
	                state = 0;
	            }
	            else if(state == 3) {
	                startIndex += 2;
	                endIndex = startIndex;
	                state = 0;
	            }
	        }

	        if(i == relativePath.length() - 1 && startIndex != endIndex) {
                AppendPath(newPath, std::string_view(relativePath.begin() + startIndex, relativePath.begin() + endIndex));
	        }
	        ++endIndex;
	    }

        return PackageLocation(m_fileName, newPath);
    }

    bool PackageLocation::Exists() const noexcept {
		return PackageManager::GetInstance().Get(m_fileName)->Exists(m_entryName.c_str());
	}

	void PackageLocation::GetEntry(std::vector<byte>& buffer) const {
		KML_ASSERT(*this);
		KML_ASSERT(buffer.empty());

		PackageManager::GetInstance().Get(m_fileName)->GetEntry(m_entryName.c_str(), buffer);
	}
	
	void PackageLocation::GetEntry(std::pmr::vector<byte>& buffer, std::pmr::memory_resource& memoryResource) const {
		KML_ASSERT(*this);
		KML_ASSERT(buffer.empty());

		PackageManager::GetInstance().Get(m_fileName)->GetEntry(m_entryName.c_str(), buffer, memoryResource);
	}
	
	void PackageLocation::GetEntry(std::string& buffer) const {
		KML_ASSERT(*this);
		KML_ASSERT(buffer.empty());

		PackageManager::GetInstance().Get(m_fileName)->GetEntry(m_entryName.c_str(), buffer);
	}
	
	void PackageLocation::GetEntry(std::pmr::string& buffer, std::pmr::memory_resource& memoryResource) const {
		KML_ASSERT(*this);
		KML_ASSERT(buffer.empty());

		PackageManager::GetInstance().Get(m_fileName)->GetEntry(m_entryName.c_str(), buffer, memoryResource);
	}

    void PackageLocation::GetEntry(byte*& data, usize& size, std::pmr::memory_resource& memoryResource) const {
        KML_ASSERT(*this);

        PackageManager::GetInstance().Get(m_fileName)->GetEntry(m_entryName.c_str(), data, size, memoryResource);
    }
}
