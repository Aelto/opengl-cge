#include "resource-manager.h"

namespace cge {

  std::map<std::string, cge::Texture2D>    cge::ResourceManager::textures;
  std::map<std::string, cge::Shader>       cge::ResourceManager::shaders;

}