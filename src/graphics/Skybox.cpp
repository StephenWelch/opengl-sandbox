//
// Created by Stephen Welch on 8/17/2020.
//

#include "Skybox.h"

#include <utility>

Skybox::Skybox(unsigned int textureUnit, std::array<std::filesystem::path, 6> filePaths) : Model(GL_STATIC_DRAW,
																																																 std::vector<std::shared_ptr<
																																																		 Mesh>>{}) {
	this->cubemap = std::make_shared<TextureCubemap>(Texture::TextureType::DIFFUSE, textureUnit, std::move(filePaths));

	meshes.push_back(std::make_shared<PlainMesh>(GL_STATIC_DRAW,
																							 vertices,
																							 indices,
																							 std::vector<std::shared_ptr<Texture>>{cubemap}));
}
