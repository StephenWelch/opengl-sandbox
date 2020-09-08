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
//			texture->init();
			resourceHandle->attachResource(texture);

			resourcesToLoad.push({texture, [resourceHandle, path](const std::shared_ptr<Loadable> &resourcePtr) -> std::shared_ptr<ResourceHandle> {
				auto texture = std::dynamic_pointer_cast<Texture2d>(resourcePtr);
				auto data = std::make_shared<Texture2d::TextureData>(path);
				texture->setData(data);
				texture->init();

				return resourceHandle;
			}});

			return texture;
		}
	}

	void start() {
		loadThread = std::thread([&]() {
			while(true) {
				if (!resourcesToLoad.empty()) {
					auto nextToLoad = resourcesToLoad.top();
					std::shared_ptr<ResourceHandle> resourceHandle = nextToLoad.second(nextToLoad.first);

					resourcesToLoad.pop();

					std::hash<ResourceHandle> hash;
					size_t resHash = hash(*resourceHandle);
					LOG_DEBUG("Loaded {}", resHash);
					loadedResources.insert(resourceHandle);
				}

				std::this_thread::sleep_for(50ms);
			}
		});
	}

	void stop() {
		loadThread.join();
	}

	auto isDoneLoading() const { return resourcesToLoad.empty(); }

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
	std::stack<std::pair<std::shared_ptr<Loadable>, std::function<std::shared_ptr<ResourceHandle>(const std::shared_ptr<Loadable>&)>>> resourcesToLoad;
	std::unordered_set<std::shared_ptr<ResourceHandle>> loadedResources;
};