//
// Created by Stephen Welch on 9/2/2020.
//

#pragma once

#include <unordered_map>
#include <util/util.h>
#include <memory>
#include <filesystem>
#include "Loadable.h"

class ResourceHandle {
 public:

	ResourceHandle(const std::filesystem::path &path) {
		pathRegistry.emplace_back(path, getLastWriteTime(path));
	}

	ResourceHandle(const std::vector<std::filesystem::path> &paths) {
		for(const auto &path : paths) {
			pathRegistry.emplace_back(path, getLastWriteTime(path));
		}
	}

	bool hasBeenModified() {
		bool modified = false;
		for (auto &path : pathRegistry) {
			auto lastWriteTime = getLastWriteTime(path.first);
			if (lastWriteTime > path.second) {
				modified = true;
				path.second = lastWriteTime;
			}
		}
		return modified;
	}

	void attachResource(const std::shared_ptr<Loadable> &resource) {
		this->resource = resource;
	}

	void setLoadFunction(const std::function<std::shared_ptr<ResourceHandle>()> &loadFunction) {
		this->loadFunction = loadFunction;
	}

	auto getFilePathRegistry() const { return pathRegistry; }

	auto getResource() const { return resource; }

	auto load() const {
		return loadFunction();
	}

 private:
	std::vector<std::pair<std::filesystem::path, time_t>> pathRegistry;
	std::function<std::shared_ptr<ResourceHandle>()> loadFunction;
	std::shared_ptr<Loadable> resource;

	static time_t getLastWriteTime(const std::filesystem::path &path) {
		return util::to_time_t(std::filesystem::last_write_time(path));
	}
};

namespace std {
template<>
struct std::hash<ResourceHandle> {
	std::size_t operator()(ResourceHandle const &resource) {
		size_t hash = 0;
		for (const auto &path : resource.getFilePathRegistry()) {
			util::hash_combine(hash, path.first.generic_string());
		}
		return hash;
	}
};
}
