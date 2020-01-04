#pragma once

#include <glm/glm.hpp>
#include <map>
#include <queue>
#include <graphics\Buffer.h>
#include <util/Log.h>

#define MAX_DIRECTIONAL_LIGHTS 100
#define MAX_POINT_LIGHTS 100
#define MAX_SPOTLIGHTS 100

struct DirectionalLight {
  glm::vec4 direction;

  glm::vec4 ambientIntensity;
  glm::vec4 diffuseIntensity;
  glm::vec4 specularIntensity;

  bool operator < (const DirectionalLight& other) const {
    return  glm::all(glm::lessThan(ambientIntensity, other.ambientIntensity)) ||
            glm::all(glm::lessThan(diffuseIntensity, other.diffuseIntensity)) ||
            glm::all(glm::lessThan(specularIntensity, other.specularIntensity));
  }

};

struct PointLight {
  glm::vec4 position;

  glm::vec4 ambientIntensity;
  glm::vec4 diffuseIntensity;
  glm::vec4 specularIntensity;

  float constant;
  float linear;
  float quadratic;
  float padding;

  bool operator < (const PointLight& other) const {
    return  glm::all(glm::lessThan(ambientIntensity, other.ambientIntensity)) ||
      glm::all(glm::lessThan(diffuseIntensity, other.diffuseIntensity)) ||
      glm::all(glm::lessThan(specularIntensity, other.specularIntensity));
  }

};

struct SpotLight {
  glm::vec4 position;
  glm::vec4 direction;

  glm::vec4 ambientIntensity;
  glm::vec4 diffuseIntensity;
  glm::vec4 specularIntensity;

  float constant;
  float linear;
  float quadratic;

  float cutOff;
  float outerCutOff;
  float padding, padding2, padding3;

  bool operator < (const SpotLight& other) const {
    return  glm::all(glm::lessThan(ambientIntensity, other.ambientIntensity)) ||
      glm::all(glm::lessThan(diffuseIntensity, other.diffuseIntensity)) ||
      glm::all(glm::lessThan(specularIntensity, other.specularIntensity));
  }

};

template<typename LightStruct, int MaxLights>
class LightManager {
protected:
  UniformBuffer buffer;
private:
  struct Data {
    LightStruct lights[MaxLights];
    int numLights;
  } uniformData;

  std::map<LightStruct, int> lights;
  std::queue<int> unfilledIndexes;
  int lastIndex = 0;

public:
  bool addLight(const LightStruct& light)
  {
    if (unfilledIndexes.empty()) {
      if (lastIndex > MaxLights) {
        return false;
      }
      else {
        lights[light] = lastIndex;
        lastIndex++;
      }
    }
    else {
      lights[light] = unfilledIndexes.front();
      unfilledIndexes.pop();
    }
  }

  void removeLight(const LightStruct& light)
  {
    int idx = lights[light];
    lights.erase(light);
    if (idx == lastIndex - 1) {
      lastIndex--;
    }
    else {
      unfilledIndexes.push(idx);
    }
  }

  void init() {
    buffer.init(GL_DYNAMIC_DRAW, sizeof(Data));
  }

  void update(const LightStruct& light) {
    uniformData.lights[lights[light]] = light;
    uniformData.numLights = lights.size();
    buffer.execute([&](auto ubo) {
      ubo->setData(&uniformData);
    });
  }

  void updateAll()
  {
    for (std::pair<LightStruct, int> entry : lights) {
      update(entry.first);
    }
  }

  void setBindingPoint(const int& bindingPoint) {
    buffer.bindShaderProgram(bindingPoint);
  }

  std::map<LightStruct, int> getLights() const
  {
    return lights;
  }
};

typedef LightManager<DirectionalLight, MAX_DIRECTIONAL_LIGHTS> DirectionalLightManager;
typedef LightManager<PointLight, MAX_POINT_LIGHTS> PointLightManager;
typedef LightManager<SpotLight, MAX_SPOTLIGHTS> SpotLightManager;