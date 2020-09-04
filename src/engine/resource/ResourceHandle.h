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
		pathRegistry[getLastWriteTime(path)] = path;
	}

	ResourceHandle(const std::vector<std::filesystem::path> &paths) {
		for(const auto &path : paths) {
			pathRegistry[getLastWriteTime(path)] = path;
		}
	}

	bool hasBeenModified() {
		bool modified = false;
		for (const auto &path : pathRegistry) {
			if (getLastWriteTime(path.second) > path.first) {
				modified = true;
			}
		}
		return modified;
	}

	void attachResource(const std::shared_ptr<Loadable> &resource) {
		this->resource = resource;
	}

	auto getFilePathRegistry() const { return pathRegistry; }

	auto getResource() const { return resource; }

 private:
	size_t hash;
	std::unordered_map<time_t, std::filesystem::path> pathRegistry;
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
			util::hash_combine(hash, path.second.generic_string());
		}
		return hash;
	}
};
}
