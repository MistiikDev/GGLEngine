#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#pragma once

#include <algorithm>
#include <vector>
#include <unordered_map>

#include <render/OpenGL/GLTex.h>

#define TEXTURE_BUFF_SIZE 1024 // Reserve 1024 texture as cache by default, expand later

class TextureCache {
    public:

        static bool b_isLoaded( const char* fileName ) {
            return m_texture_cache.find(fileName) != m_texture_cache.end();
        };

        static void Init() {
            m_texture_cache = std::unordered_map<std::string, std::shared_ptr<GLTex>>();
            m_texture_cache.reserve(TEXTURE_BUFF_SIZE);
        };

        static std::shared_ptr<GLTex> GetTexture( const char* fileName ) {
            if (!b_isLoaded( fileName )) {
                std::shared_ptr<GLTex> texture = std::make_shared<GLTex>( fileName );

                m_texture_cache[fileName] = texture;
            }

            return m_texture_cache[fileName];
        }

        static void RemoveTexture( const char* fileName ) {
            if (!b_isLoaded( fileName ))
                return;
            
            m_texture_cache.erase(fileName);
        }

    private:
        static std::unordered_map<std::string, std::shared_ptr<GLTex>> m_texture_cache; // FILE PATH -> TEXTURE
};

#endif // TEXTURE_CACHE_H