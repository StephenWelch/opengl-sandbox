#pragma once

#include <glm/glm.hpp>

class DirectionalLight {
public:
  struct Data {
    glm::vec4 direction;

    glm::vec4 ambientIntensity;
    glm::vec4 diffuseIntensity;
    glm::vec4 specularIntensity;
  };
};

class PointLight {
public:
  struct Data {
    glm::vec4 position;

    glm::vec4 ambientIntensity;
    glm::vec4 diffuseIntensity;
    glm::vec4 specularIntensity;

    float constant;
    float linear;
    float quadratic;
    float padding;
  };
};

class SpotLight {
public:
  struct Data {
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
};