#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <vector>
#include <memory>
#include <scene/scene.h>

class G_SceneManager {
    public:
        static void AddScene(std::unique_ptr<G_scene> scene);
        static void LoadScene(const std::string& scene_name);
        static void UnloadScene();

        static void ClearScenes();

    private:
        static std::unique_ptr<G_scene> m_current_scene;
        static std::unordered_map<std::string, std::unique_ptr<G_scene>> m_scenes;
};

#endif