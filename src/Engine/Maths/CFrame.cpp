#include "CFrame.h"

CFrame::CFrame() {
    Position = glm::vec3(1.0f);
    Rotation = glm::quat();
}

CFrame::CFrame(float x, float y, float z) {
    Position = glm::vec3(x, y, z);
}

CFrame::CFrame(glm::vec3 pos) {
    Position = pos;
}

CFrame::CFrame(glm::mat4 baseMatrix) {
    glm::vec3 rX = glm::normalize(glm::vec3(baseMatrix[0]));
    glm::vec3 rY = glm::normalize(glm::vec3(baseMatrix[1]));
    glm::vec3 rZ = glm::normalize(glm::vec3(baseMatrix[2]));

    glm::mat3 rot = glm::mat3(rX, rY, rZ);

    Rotation = glm::quat_cast(rot);
    Position = baseMatrix[3];
}

glm::mat4 CFrame::toMatrix() {
    glm::mat4 cframeMatrix = glm::mat4(1.0f);

    cframeMatrix = glm::mat4_cast(Rotation);
    cframeMatrix[3] = glm::vec4(Position, 1.0f);

    return cframeMatrix;
}

CFrame CFrame::ToObjectSpace(CFrame newOriginBase) {
    glm::mat4 cframeMatrix = toMatrix();
    glm::mat4 newMatrix = glm::mat4(1.0f);

    newMatrix = glm::inverse(cframeMatrix) * newOriginBase.toMatrix();

    return CFrame(newMatrix);
}

CFrame CFrame::ToWorldSpace(CFrame localOffsetCFrame) {
    glm::mat4 cframeMatrix = toMatrix();
    glm::mat4 newMatrix = glm::mat4(1.0f);

    newMatrix = cframeMatrix * localOffsetCFrame.toMatrix();

    return CFrame(newMatrix);
}