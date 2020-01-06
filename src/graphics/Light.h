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

  DirectionalLight() = default;
  DirectionalLight(const glm::vec3& direction, const glm::vec3& ambientIntensity, const glm::vec3& diffuseIntensity, const glm::vec3& specularIntensity) :
      direction(direction, 0.0f),
      ambientIntensity(ambientIntensity, 0.0f),
      diffuseIntensity(diffuseIntensity, 0.0f),
      specularIntensity(specularIntensity, 0.0f) {};

  bool operator < (const DirectionalLight& other) const {
    return  glm::length(direction) < glm::length(other.direction) ||
      glm::length(ambientIntensity) < glm::length(other.ambientIntensity) ||
      glm::length(diffuseIntensity) < glm::length(other.diffuseIntensity) ||
      glm::length(specularIntensity) < glm::length(other.specularIntensity);
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

  PointLight() = default;
  PointLight(const glm::vec3& position, const glm::vec3& ambientIntensity, const glm::vec3& diffuseIntensity, const glm::vec3& specularIntensity, const float& constant, const float& linear, const float& quadratic) :
      position(position, 0.0f),
      ambientIntensity(ambientIntensity, 0.0f),
      diffuseIntensity(diffuseIntensity, 0.0f),
      specularIntensity(specularIntensity, 0.0f),
      constant(constant),
      linear(linear),
      quadratic(quadratic) {};

  bool operator < (const PointLight& other) const {
    return  glm::length(position) < glm::length(other.position) ||
      glm::length(ambientIntensity) < glm::length(other.ambientIntensity) ||
      glm::length(diffuseIntensity) < glm::length(other.diffuseIntensity) ||
      glm::length(specularIntensity) < glm::length(other.specularIntensity);
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

  SpotLight() = default;
  SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& ambientIntensity, const glm::vec3& diffuseIntensity, const glm::vec3& specularIntensity, const float& constant, const float& linear, const float& quadratic, const float& cutOff, const float& outerCutOff) :
      position(position, 0.0f),
      direction(direction, 0.0f),
      ambientIntensity(ambientIntensity, 0.0f),
      diffuseIntensity(diffuseIntensity, 0.0f),
      specularIntensity(specularIntensity, 0.0f),
      constant(constant),
      linear(linear),
      quadratic(quadratic),
      cutOff(cutOff),
      outerCutOff(outerCutOff) {};

  bool operator < (const SpotLight& other) const {
    return  glm::length(position) < glm::length(other.position) ||
      glm::length(ambientIntensity) < glm::length(other.ambientIntensity) ||
      glm::length(diffuseIntensity) < glm::length(other.diffuseIntensity) ||
      glm::length(specularIntensity) < glm::length(other.specularIntensity);
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

  std::map<std::shared_ptr<LightStruct>, int> lights;
  std::queue<int> unfilledIndexes;
  int lastIndex = 0;

public:
  bool addLight(const std::shared_ptr<LightStruct>& light)
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
    return true;
  }

  void removeLight(const std::shared_ptr<LightStruct>& light)
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

  void update(const std::shared_ptr<LightStruct>& light) {
    uniformData.lights[lights[light]] = *light;
    uniformData.numLights = lights.size();
    buffer.execute([&](auto ubo) {
      ubo->setData(&uniformData);
    });
  }

  void updateAll()
  {
    for (std::pair<std::shared_ptr<LightStruct>, int> entry : lights) {
      update(entry.first);
    }
  }

  void setBindingPoint(const int& bindingPoint) {
    buffer.bindShaderProgram(bindingPoint);
  }

  auto getLights() const
  {
    return lights;
  }
};

typedef LightManager<DirectionalLight, MAX_DIRECTIONAL_LIGHTS> DirectionalLightManager;
typedef LightManager<PointLight, MAX_POINT_LIGHTS> PointLightManager;
typedef LightManager<SpotLight, MAX_SPOTLIGHTS> SpotLightManager;