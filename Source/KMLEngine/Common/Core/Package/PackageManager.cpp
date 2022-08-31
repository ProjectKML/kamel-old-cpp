//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageManager.cpp
//------------------------------------------------------------

#include "PackageManager.hpp"
#include "PackageFile.hpp"

namespace KMLEngine {
	template<> PackageManager* Singleton<PackageManager>::_INSTANCE = nullptr;
	
	PackageManager::PackageManager() {
		AttachSingleton();
	}
	
	PackageManager::~PackageManager() {
		DetachSingleton();

		for(auto& [name, packageFile] : m_packages) {
			delete packageFile;
		}

		m_packages.clear();
	}

	PackageFile* PackageManager::Get(const std::string_view& name) {
		std::lock_guard lock(m_mutex);

		const auto iterator = m_packages.find(name);
		if(iterator == m_packages.end()) {
			auto* packageFile = new PackageFile(name.data());

			m_packages.insert(std::make_pair(packageFile->GetName(), packageFile));
			return packageFile;
		}

		return iterator->second;
	}
}
