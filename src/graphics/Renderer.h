#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Buffer.h>
#include <graphics/Camera.h>
#include <graphics/Light.h>
#include <graphics/Mesh.h>
#include <graphics/Model.h>
#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include <util/util.h>

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include "Skybox.h"

class Renderer {
 private:
	std::shared_ptr<DirectionalLightManager> directionalLightManager = std::make_shared<DirectionalLightManager>();
	std::shared_ptr<PointLightManager> pointLightManager = std::make_shared<PointLightManager>();
	std::shared_ptr<SpotLightManager> spotLightManager = std::make_shared<SpotLightManager>();

	const std::unique_ptr<Camera> &camera;

	int width;
	int height;
	Shader lightingShader = Shader("shaders/lightmap_textured_model.vert",
																 "shaders/lightmap_textured_model.frag");
	Shader skyboxShader = Shader("shaders/skybox.vert", "shaders/skybox.frag");

	std::vector<std::shared_ptr<Model>> models{};
	std::shared_ptr<Skybox> skybox{};

 public:
	Renderer(const std::unique_ptr<Camera> &camera, int width,
					 int height)
			: camera(camera), width(width), height(height) {};
	void init();
	void render();
	void cleanup();
	void setWidth(int width);
	void setHeight(int height);
	void addModel(const std::shared_ptr<Model> &model);
	void setSkybox(const std::shared_ptr<Skybox> &skybox);
	auto &getDirectionalLights() { return this->directionalLightManager; };
	auto &getPointLights() { return this->pointLightManager; };
	auto &getSpotLights() { return this->spotLightManager; };
	const auto &getModels() const { return this->models; };
	const auto &getSkybox() const { return this->skybox; };
};