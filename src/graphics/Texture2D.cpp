#include "Texture2D.h"

#include <stb_image.h>
#include <util/util.h>

#include "util/Log.h"

void Texture2D::init() {
  LOG_DEBUG("Loading texture {}", filePath);
  stbi_set_flip_vertically_on_load(true);

  // Allocate texture
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char* data =
      stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

  ENGINE_ASSERT(data, "Failed to load texture {}", filePath);
  createTexture(width, height, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  LOG_DEBUG("Loaded texture {} with extension {} into id {} on unit {}.",
            filePath, fileExtension, id, textureUnit);
}

void Texture2D::bind() {
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::cleanup() {}

Texture2D::TextureType Texture2D::getType() const { return type; }

GLuint Texture2D::getId() const { return id; }

GLuint Texture2D::getTextureUnit() const { return textureUnit; }

GLuint Texture2D::getTextureUnitNum() const {
  return textureUnit - GL_TEXTURE0;
}

void Texture2D::createTexture(const int& width, const int& height,
                              const unsigned char* data) {
  GLuint colorChannels = GL_RGBA;
  if (fileExtension == "jpg") {
    colorChannels = GL_RGB;
  } else if (fileExtension == "png") {
    colorChannels = GL_RGBA;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, colorChannels, width, height, 0, colorChannels,
               GL_UNSIGNED_BYTE, data);
}