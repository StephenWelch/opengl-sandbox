//
// Created by Stephen Welch on 8/17/2020.
//

#ifndef SKYBOX_H
#define SKYBOX_H

#include "Model.h"
#include <filesystem>
#include <memory>
#include <utility>

class Skybox : public Model {
 public:
	Skybox(unsigned int textureUnit, std::array<std::filesystem::path, 6> filePaths);

 private:
//	std::vector<glm::vec3> vertices{
//			// Back face
//			{-1.0, -1.0, -1.0},  // Bottom-left
//			{1.0, 1.0, -1.0},    // top-right
//			{1.0, -1.0, -1.0},   // bottom-right
//			{1.0, 1.0, -1.0},    // top-right
//			{-1.0, -1.0, -1.0},  // bottom-left
//			{-1.0, 1.0, -1.0},   // top-left
//			// Front face
//			{-1.0, -1.0, 1.0},  // bottom-left
//			{1.0, -1.0, 1.0},   // bottom-right
//			{1.0, 1.0, 1.0},    // top-right
//			{1.0, 1.0, 1.0},    // top-right
//			{-1.0, 1.0, 1.0},   // top-left
//			{-1.0, -1.0, 1.0},  // bottom-left
//			// Left face
//			{-1.0, 1.0, 1.0},    // top-right
//			{-1.0, 1.0, -1.0},   // top-left
//			{-1.0, -1.0, -1.0},  // bottom-left
//			{-1.0, -1.0, -1.0},  // bottom-left
//			{-1.0, -1.0, 1.0},   // bottom-right
//			{-1.0, 1.0, 1.0},    // top-right
//			// Right face
//			{1.0, 1.0, 1.0},    // top-left
//			{1.0, -1.0, -1.0},  // bottom-right
//			{1.0, 1.0, -1.0},   // top-right
//			{1.0, -1.0, -1.0},  // bottom-right
//			{1.0, 1.0, 1.0},    // top-left
//			{1.0, -1.0, 1.0},   // bottom-left
//			// Bottom face
//			{-1.0, -1.0, -1.0},  // top-right
//			{1.0, -1.0, -1.0},   // top-left
//			{1.0, -1.0, 1.0},    // bottom-left
//			{1.0, -1.0, 1.0},    // bottom-left
//			{-1.0, -1.0, 1.0},   // bottom-right
//			{-1.0, -1.0, -1.0},  // top-right
//			// Top face
//			{-1.0, 1.0, -1.0},  // top-left
//			{1.0, 1.0, 1.0},    // bottom-right
//			{1.0, 1.0, -1.0},   // top-right
//			{1.0, 1.0, 1.0},    // bottom-right
//			{-1.0, 1.0, -1.0},  // top-left
//			{-1.0, 1.0, 1.0}    // bottom-left
//	};

	std::vector<glm::vec3> vertices{
			// Back face
			{-1.0, 1.0, -1.0},   // top-left
			{-1.0, -1.0, -1.0},  // bottom-left
			{1.0, 1.0, -1.0},    // top-right
			{1.0, -1.0, -1.0},   // bottom-right
			{1.0, 1.0, -1.0},    // top-right
			{-1.0, -1.0, -1.0},  // Bottom-left
			// Front face
			{-1.0, -1.0, 1.0},  // bottom-left
			{-1.0, 1.0, 1.0},   // top-left
			{1.0, 1.0, 1.0},    // top-right
			{1.0, 1.0, 1.0},    // top-right
			{1.0, -1.0, 1.0},   // bottom-right
			{-1.0, -1.0, 1.0},  // bottom-left
			// Left face
			{-1.0, 1.0, 1.0},    // top-right
			{-1.0, -1.0, 1.0},   // bottom-right
			{-1.0, -1.0, -1.0},  // bottom-left
			{-1.0, -1.0, -1.0},  // bottom-left
			{-1.0, 1.0, -1.0},   // top-left
			{-1.0, 1.0, 1.0},    // top-right
			// Right face
			{1.0, -1.0, 1.0},   // bottom-left
			{1.0, 1.0, 1.0},    // top-left
			{1.0, -1.0, -1.0},  // bottom-right
			{1.0, 1.0, -1.0},   // top-right
			{1.0, -1.0, -1.0},  // bottom-right
			{1.0, 1.0, 1.0},    // top-left
			// Bottom face
			{-1.0, -1.0, -1.0},  // top-right
			{-1.0, -1.0, 1.0},   // bottom-right
			{1.0, -1.0, 1.0},    // bottom-left
			{1.0, -1.0, 1.0},    // bottom-left
			{1.0, -1.0, -1.0},   // top-left
			{-1.0, -1.0, -1.0},  // top-right
			// Top face
			{-1.0, 1.0, 1.0},    // bottom-left
			{-1.0, 1.0, -1.0},  // top-left
			{1.0, 1.0, 1.0},    // bottom-right
			{1.0, 1.0, -1.0},   // top-right
			{1.0, 1.0, 1.0},    // bottom-right
			{-1.0, 1.0, -1.0}  // top-left
	};
	
//	std::vector<glm::vec3> vertices {
//			{-1.0, 1.0, 1.0}, // front-top-left				0
//			{1.0, 1.0, 1.0}, // front-top-right				1
//			{1.0, -1.0, 1.0}, // front-bottom-right		2
//			{-1.0, -1.0, 1.0}, // front-bottom-left		3
//			{-1.0, 1.0, -1.0}, // back-top-left				4
//			{1.0, 1.0, -1.0}, // back-top-right				5
//			{1.0, -1.0, -1.0}, // back-bottom-right		6
//			{-1.0, -1.0, -1.0}, // back-bottom-left		7
//	};

	std::vector<GLuint> indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
															10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
															20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
															30, 31, 32, 33, 34, 35};
	
	std::shared_ptr<TextureCubemap> cubemap;

	std::shared_ptr<Mesh> createSkyboxMesh(unsigned int textureUnit,
																				 std::array<std::filesystem::path, 6> filePaths);
};

#endif //SKYBOX_H
