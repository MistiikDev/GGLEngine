#include <render/texture_cache.h>

std::unordered_map<std::string, std::shared_ptr<GLTex>> TextureCache::m_texture_cache;