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
#include <chrono>
#include <utility>
#include <queue>

using namespace std::chrono_literals;

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

	std::shared_ptr<Texture2d> loadTexture2d(Texture::TextureType type,
																					 unsigned int unit,
																					 const std::filesystem::path &path) {
		auto resourceHandle = std::make_shared<ResourceHandle>(path);

		auto resourcePtr = getCached<Texture2d>(resourceHandle);

		if (resourcePtr!=nullptr) {
			return resourcePtr;
		} else {
			auto texture = std::make_shared<Texture2d>(type, unit);
			texture->init();
			resourceHandle->attachResource(texture);
			resourceHandle->setLoadFunction([texture, resourceHandle, path]() -> std::shared_ptr<ResourceHandle> {

				texture->setData(std::make_shared<Texture::TextureData>(path));

				return resourceHandle;
			});

			resourcesToLoad.push(resourceHandle);


			return texture;
		}
	}

	void start() {
		loadThread = std::thread([&]() {
			while(true) {
				if (!resourcesToLoad.empty()) {
					std::shared_ptr<ResourceHandle> resourceHandle = resourcesToLoad.top()->load();
					resourcesToLoad.pop();
					resourcesToInit.push(resourceHandle);
				} else {
					for(auto &resource : loadedResources) {
						if(resource->hasBeenModified()) {
							LOG_DEBUG("Detected resource to hot-reload");
							resourcesToLoad.push(resource);
						}
					}
				}

				std::this_thread::sleep_for(50ms);
			}
		});
	}

	void initializeLoaded() {
		while(!resourcesToInit.empty()) {
			auto resourceHandle = resourcesToInit.front();
			resourceHandle->getResource()->init();
			loadedResources.insert(resourceHandle);
			resourcesToInit.pop();
		}
	}

	void stop() {
		loadThread.join();
	}

	auto isDoneLoading() const { return resourcesToLoad.empty(); }
	auto isDoneInitializing() const { return resourcesToInit.empty(); }

 private:
	ResourceManager() = default;

	template<class T>
	std::shared_ptr<T> getCached(const std::shared_ptr<ResourceHandle> &resource) {
		if (!std::is_base_of<Loadable, T>::value) {
			return nullptr;
		}

		auto search = loadedResources.find(resource);
		if (search!=loadedResources.end()) {
			return std::dynamic_pointer_cast<T>((*search)->getResource());
		} else {
			return nullptr;
		}
	}

	std::thread loadThread;
	std::stack<std::shared_ptr<ResourceHandle>> resourcesToLoad;
	std::queue<std::shared_ptr<ResourceHandle>> resourcesToInit;
	std::unordered_set<std::shared_ptr<ResourceHandle>> loadedResources;
};