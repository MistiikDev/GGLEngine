#include <scene/scene_manager.h>

std::unordered_map<std::string, std::unique_ptr<G_scene>> G_SceneManager::m_scenes;
std::unique_ptr<G_scene> G_SceneManager::m_current_scene;

void G_SceneManager::AddScene(std::unique_ptr<G_scene> _scene) {
    if (m_scenes.find(_scene->SceneName) != m_scenes.end()) {
        return;
    }

    m_scenes[_scene->SceneName] = std::move(_scene);
}

void G_SceneManager::LoadScene(const std::string& scene_name) {
    if (m_scenes.find(scene_name) == m_scenes.end()) {
        return;
    }

    G_scene* scene = m_scenes[scene_name].get();
    scene->Load();
}