#include "CFrame.h"

CFrame::CFrame() {
    Position = glm::vec3(1.0f);
    Rotation = glm::quat();
}

CFrame::CFrame( float x, float y, float z ) {
    Position = glm::vec3(x, y, z);
}

CFrame::CFrame( Vector3 v3_pos ) {
    Position = glm::vec3(v3_pos.x, v3_pos.y, v3_pos.z);
}

CFrame::CFrame( glm::vec3 v3_pos ) {
    Position = v3_pos;
}

CFrame::CFrame( glm::mat4 m4_baseMatrix ) {
    glm::vec3 rX = glm::normalize(glm::vec3(m4_baseMatrix[0]));
    glm::vec3 rY = glm::normalize(glm::vec3(m4_baseMatrix[1]));
    glm::vec3 rZ = glm::normalize(glm::vec3(m4_baseMatrix[2]));

    glm::mat3 m3_rot = glm::mat3(rX, rY, rZ);

    Rotation = glm::quat_cast(m3_rot);
    Position = m4_baseMatrix[3];
}

glm::mat4 CFrame::toMatrix() {
    glm::mat4 m4_cframeMatrix = glm::mat4(1.0f);

    m4_cframeMatrix = glm::mat4_cast(Rotation);
    m4_cframeMatrix[3] = glm::vec4(Position, 1.0f);

    return m4_cframeMatrix;
}

CFrame CFrame::toObjectSpace( CFrame cf_newOriginBase ) {
    glm::mat4 m4_cframeMatrix = toMatrix();
    glm::mat4 m4_newMatrix = glm::mat4(1.0f);

    m4_newMatrix = glm::inverse( m4_cframeMatrix ) * cf_newOriginBase.toMatrix();

    return CFrame( m4_newMatrix );
}

CFrame CFrame::toWorldSpace( CFrame cf_localOffsetCFrame ) {
    glm::mat4 m4_cframeMatrix = toMatrix();
    glm::mat4 m4_newMatrix = glm::mat4(1.0f);

    m4_newMatrix = m4_cframeMatrix * cf_localOffsetCFrame.toMatrix();

    return CFrame( m4_newMatrix );
}