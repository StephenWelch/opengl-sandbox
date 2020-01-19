#pragma once
#include <GLFW/glfw3.h>
#include <engine/Core.h>
#include <glad/glad.h>

#include <string>

class Texture2D {
 public:
  enum class TextureType { SPECULAR, DIFFUSE, EMISSIVE };

  Texture2D(const TextureType& type, const std::string& filePath,
            const unsigned int& textureUnit)
      : type(type),
        filePath(filePath),
        fileExtension(filePath.substr(filePath.find(".") + 1)),
        textureUnit(textureUnit){};

  void init();
  void bind();
  void cleanup();
  TextureType getType() const;
  unsigned int getId() const;
  unsigned int getTextureUnit() const;
  unsigned int getTextureUnitNum() const;

 private:
  std::string filePath;
  std::string fileExtension;
  unsigned int textureUnit;
  unsigned int id;
  TextureType type;

  void createTexture(const int& width, const int& height,
                     const unsigned char* data);
};
