#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <unordered_map>
#include <string>

#include <scene/entities/entity.h>

#include <scene/components/transform.h>
#include <scene/components/rigidbody.h>
#include <scene/components/mesh.h>

#define SIZE 1024

class G_scene {
    public:
        std::string SceneName;

        void Load() const;
        void Unload() const;

        void Render();
    private:
        std::vector<Entity> m_entities();
};

#endif

