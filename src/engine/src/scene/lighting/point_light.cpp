#include <scene/lighting/point_light.h>

const char* LIGHT_FRAG_SHADER = "src/game/data/shaders/FShaders/light.frag";
const char* LIGHT_VERT_SHADER = "src/game/data/shaders/VShaders/light.vert";

PointLight::PointLight(glm::vec3 position):
    lightColor(1.0f),                                   
    lightCFrame(position),                               
    m_lightShader(LIGHT_VERT_SHADER, LIGHT_FRAG_SHADER)
{

    m_lightShader.Activate();
    m_lightShader.SetMatrix4f("light_transform", lightCFrame.toMatrix());
    m_lightShader.SetVector3f("light_color", lightColor);
    m_lightShader.SetVector3f("light_position", position);
};

void PointLight::Render() {
    m_lightShader.Activate();

    m_lightShader.SetMatrix4f("light_transform", lightCFrame.toMatrix());
    m_lightShader.SetVector3f("light_color", lightColor);
    m_lightShader.SetVector3f("light_position", lightCFrame.Position);
}

void PointLight::Destroy() {
    m_lightShader.Destroy();
}