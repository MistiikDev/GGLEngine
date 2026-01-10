#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <unordered_map>
#include <string>

#include <scene/entities/entity.h>

#define SIZE 1024

class G_scene {
    public:
        std::string SceneName;

        const void Load() const;
        const void Unload() const;

        const void Render();
    private:
        std::vector<Entity> m_entities();
};

#endif

