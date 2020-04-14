#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Renderer.h>
#include <util/Log.h>

#include <glm/glm.hpp>

void Renderer::init()
{
		LOG_INFO("Initializing Renderer with {}x{} resolution", width, height);

		LOG_INFO("Loading models");
		model.init();

		LOG_INFO("Loading shaders");
		lightingShader.init();

		lightingShader.use();

		directionalLightManager.init();
		pointLightManager.init();
		spotLightManager.init();

		directionalLightManager.setBindingPoint(0);
		lightingShader.setBindingPoint("uDirectionalLights", 0);
		pointLightManager.setBindingPoint(1);
		lightingShader.setBindingPoint("uPointLights", 1);
		spotLightManager.setBindingPoint(2);
		lightingShader.setBindingPoint("uSpotLights", 2);

		directionalLightManager.addLight(dirLight);
		pointLightManager.addLight(pointLight1);
		pointLightManager.addLight(pointLight2);
		pointLightManager.addLight(pointLight3);
		pointLightManager.addLight(pointLight4);
		spotLightManager.addLight(spotLight);

		directionalLightManager.updateAll();
		pointLightManager.updateAll();
		spotLightManager.updateAll();

		std::unordered_map<Texture2D::TextureType, int> typeCount{};
		for (auto& mesh : model.getMeshes()) {
				for(auto& texture : mesh.getTextures()) {
						std::string type;
						switch (texture.getType()) {
						case Texture2D::TextureType::SPECULAR:
								type = "specular";
								break;
						case Texture2D::TextureType::DIFFUSE:
								type = "diffuse";
								break;
						case Texture2D::TextureType::EMISSIVE:
								type = "emissive";
								break;
						case Texture2D::TextureType::HEIGHT:
								break;
						case Texture2D::TextureType::AMBIENT:
								break;
						}

						int textureNum = typeCount[texture.getType()];

//				LOG_DEBUG("uMaterial." + type + "Texture");
						lightingShader.setInt("uMaterial."+type+"Texture",
										texture.getTextureUnitNum());

						typeCount[texture.getType()] = textureNum++;
				}
		}

		lightingShader.setBool("uEmissionsEnabled", false);
		lightingShader.setFloat("uMaterial.shininess", 64.0f);

		// This only needs to be updated if we are changing camera FOV or other characteristics
		lightingShader.setMat4("uProjection", camera->getProjectionMatrix());

		LOG_INFO("Finished Renderer initialization");
}

void Renderer::render()
{
		lightingShader.use();

		glm::mat4 viewMatrix = camera->getViewMatrix();
		lightingShader.setMat4("uView", viewMatrix);
		lightingShader.setVec3("uViewPos", camera->getPosition());

		// User
		spotLight->position = glm::vec4(camera->getPosition(), 0.0f);
		spotLight->direction = glm::vec4(camera->getTarget(), 0.0f);
		spotLightManager.updateAll();

		glm::mat4 modelMatrix = glm::mat4(1.0f);

		// Impl-specific
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

		lightingShader.setMat4("uModel", modelMatrix);
		lightingShader.setMat3("uNormalMatrix",
						glm::transpose(glm::inverse(modelMatrix)));
		model.draw();

}

void Renderer::cleanup()
{
		/*directionalLightBuffer.cleanup();
		pointLightBuffer.cleanup();
		spotLightBuffer.cleanup();*/
		lightingShader.cleanup();
		model.cleanup();
}

void Renderer::setWidth(int width) { this->width = width; }

void Renderer::setHeight(int height) { this->height = height; }