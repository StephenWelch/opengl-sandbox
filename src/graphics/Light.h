#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <queue>
#include <graphics\Buffer.h>

#define MAX_DIRECTIONAL_LIGHTS 100
#define MAX_POINT_LIGHTS 100
#define MAX_SPOTLIGHTS 100


struct DirectionalLight {
  glm::vec4 direction;

  glm::vec4 ambientIntensity;
  glm::vec4 diffuseIntensity;
  glm::vec4 specularIntensity;
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

  std::unordered_map<LightStruct, int> lights;
  std::queue<int> unfilledIndexes;
  int lastIndex = 0;
  int maxLights;

public:
  bool addLight(const LightStruct& light)
  {
    if (unfilledIndexes.empty()) {
      if (lastIndex > maxLights) {
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
    buffer.init(GL_DYNAMIC_DRAW, sizeof(LightStruct));
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

  int getMaxLights() const
  {
    return maxLights;
  }

  std::unordered_map<LightStruct, int> getLights() const
  {
    return lights;
  }
};

class DirectionalLightManager : public LightManager<DirectionalLight, MAX_DIRECTIONAL_LIGHTS> {

};