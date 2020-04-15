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

class Renderer {
private:
		DirectionalLightManager directionalLightManager;
		PointLightManager pointLightManager;
		SpotLightManager spotLightManager;

		const std::unique_ptr<Camera>& camera;

		int width;
		int height;
		Shader lightingShader = Shader("shaders/lightmap_textured_model.vert",
						"shaders/lightmap_textured_model.frag");

		std::shared_ptr<DirectionalLight> dirLight =
						std::make_shared<DirectionalLight>(
										glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.05f, 0.05f),
										glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));

		std::shared_ptr<PointLight> pointLight1 = std::make_shared<PointLight>(
						glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.5f, 0.5f, 0.5f),
						glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
						0.032);

		std::shared_ptr<PointLight> pointLight2 = std::make_shared<PointLight>(
						glm::vec3(2.3f, -3.3f, -4.0f), glm::vec3(0.05f, 0.05f, 0.05f),
						glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
						0.032);

		std::shared_ptr<PointLight> pointLight3 = std::make_shared<PointLight>(
						glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.05f, 0.05f, 0.05f),
						glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
						0.032);

		std::shared_ptr<PointLight> pointLight4 = std::make_shared<PointLight>(
						glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.05f, 0.05f, 0.05f),
						glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
						0.032);

		std::shared_ptr<SpotLight> spotLight = std::make_shared<SpotLight>(
						glm::vec3(), glm::vec3(), glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09,
						0.032, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));

		Model model = {GL_STATIC_DRAW, "res/nanosuit/nanosuit.obj"};

public:
		Renderer(const std::unique_ptr<Camera>& camera, int width,
						int height)
						:camera(camera), width(width), height(height) { };
		void init();
		void render();
		void cleanup();
		void setWidth(int width);
		void setHeight(int height);
};