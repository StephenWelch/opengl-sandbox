#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>

class Texture2D {

  enum TextureType {
    SPECULAR,
    DIFFUSE,
    EMISSIVE
  };

private:
  std::string filePath;
  std::string fileExtension;
  GLuint textureUnit;
  GLuint id;

  void createTexture(const int& width, const int& height,
    const unsigned char* data);
public: 
  Texture2D(const std::string& filePath, const GLuint& textureUnit) : 
    filePath(filePath),
  fileExtension(filePath.substr(filePath.find(".") + 1)),
  textureUnit(textureUnit) {};

  void init();
  void bind();
  GLuint getId() const;
  GLuint getTextureUnit() const;
  GLuint getTextureUnitNum() const;
};
