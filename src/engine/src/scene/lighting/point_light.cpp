#include <scene/lighting/point_light.h>

const char* LIGHT_FRAG_SHADER = "src/game/src/data/shaders/FShaders/light.frag";
const char* LIGHT_VERT_SHADER = "src/game/src/data/shaders/VShaders/light.vert";

PointLight::PointLight(Vector3 position):
    lightPosition(position),
    lightColor(1.0f),
    lightTransform(position),
    m_lightShader( LIGHT_VERT_SHADER, LIGHT_FRAG_SHADER )
{
    lightTransform.Position = glm::vec3(position.x, position.y, position.z);

    m_lightShader.Activate();
    m_lightShader.SetMatrix4f("light_transform", lightTransform.toMatrix());
    m_lightShader.SetVector3f("light_color", lightColor);
    m_lightShader.SetVector3f("light_position", position);
};

void PointLight::Render() {
    m_lightShader.Activate();

    m_lightShader.SetMatrix4f("light_transform", lightTransform.toMatrix());
    m_lightShader.SetVector3f("light_color", lightColor);
    m_lightShader.SetVector3f("light_position", lightPosition);
}

void PointLight::Destroy() {
    m_lightShader.Destroy();
}