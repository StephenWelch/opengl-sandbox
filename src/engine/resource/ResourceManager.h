//
// Created by Stephen Welch on 8/31/2020.
//

#pragma once

#include <functional>
#include <unordered_set>
#include <stack>
#include <filesystem>
#include <util/util.h>
#include <memory>
#include <engine/resource/ResourceHandle.h>
#include <graphics/Texture.h>
#include <type_traits>

class ResourceManager {
 public:

	ResourceManager(const ResourceManager &) = delete;
	ResourceManager &operator=(const ResourceManager &) = delete;
	ResourceManager(ResourceManager
									&&) = delete;
	ResourceManager &operator=(ResourceManager &&)
	= delete;

	static auto &get() {
		static ResourceManager inst;
		return inst;
	}

	std::shared_ptr<Texture2d> loadTexture2d(const std::filesystem::path &path) {
		auto resourceHandle = std::make_shared<ResourceHandle>(path);

		auto resourcePtr = getCached<Texture2d>(resourceHandle);

		if(resourcePtr != nullptr) {
			return resourcePtr;
		} else {

			resourcesToLoad.push([&](){
				auto texture = std::make_shared<Texture2d>(Texture::TextureType::DIFFUSE, 0, path);
				texture->init();
				// Some init stuff here

				resourceHandle->attachResource(texture);
				loadedResources.insert(resourceHandle);
			});

			return resourcePtr;
		}
	}

	void start() {
		while(!resourcesToLoad.empty()) {
			resourcesToLoad.top()();
		}
	}

 private:
	ResourceManager() = default;

	template<class T>
	std::shared_ptr<T> getCached(const std::shared_ptr<ResourceHandle> &resource) {
		if(!std::is_base_of<Loadable, T>::value) {
			return nullptr;
		}

		auto search = loadedResources.find(resource);
		if(search != loadedResources.end()) {
			return std::dynamic_pointer_cast<T>((*search)->getResource());
		} else {
			return nullptr;
		}
	}

	std::stack<std::function<void()>> resourcesToLoad;
	std::unordered_set<std::shared_ptr<ResourceHandle>> loadedResources;
};