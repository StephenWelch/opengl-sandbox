#include "Texture2D.h"
#include <stb_image.h>
#include <util/util.h>
#include "util/Log.h"

void Texture2D::init() {
  Log::getLogger()->debug("Loading texture {}", filePath);
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
  if (data) {
    createTexture(width, height, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    Log::getLogger()->error("Failed to load texture {}", filePath);
  }

  stbi_image_free(data);

  Log::getLogger()->debug("Loaded texture id {} on unit {} from {} with extension {}.", id, textureUnit, filePath, fileExtension);
}

void Texture2D::bind() {
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_2D, id);
}

GLuint Texture2D::getId() const {
  return id;
}

GLuint Texture2D::getTextureUnit() const {
  return textureUnit;
}

GLuint Texture2D::getTextureUnitNum() const
{
  return textureUnit - GL_TEXTURE0;
}

void Texture2D::createTexture(const int& width, const int& height, const unsigned char* data) {
  GLuint colorChannels = GL_RGBA;
  if (fileExtension == "jpg") {
    colorChannels = GL_RGB;
    Log::getLogger()->debug("Loading RGB texture");
  }
  else if (fileExtension == "png") {
    colorChannels = GL_RGBA;
    Log::getLogger()->debug("Loading RGBA texture");
  }
  glTexImage2D(GL_TEXTURE_2D, 0, colorChannels, width, height, 0, colorChannels,
    GL_UNSIGNED_BYTE, data);
}