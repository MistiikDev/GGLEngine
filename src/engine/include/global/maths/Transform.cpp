#include "Transform.h"

Transform::Transform() {
    Position = glm::vec3(1.0f);
    Rotation = glm::quat();
    Scale = glm::vec3(1.0f);
}

Transform::Transform( float x, float y, float z ) {
    Position = glm::vec3(x, y, z);

    Scale = glm::vec3(1.0f); 
    Rotation = glm::quat();
}

Transform::Transform( const Vector3& v3_pos ) {
    Position = glm::vec3(v3_pos.x, v3_pos.y, v3_pos.z);

    Scale = glm::vec3(1.0f); 
    Rotation = glm::quat();
}

Transform::Transform( const glm::vec3& v3_pos ) {
    Position = v3_pos;

    Scale = glm::vec3(1.0f); 
    Rotation = glm::quat();
}

Transform::Transform( const glm::mat4& m4_baseMatrix ) {
    Position = m4_baseMatrix[3];

    glm::vec3 rX = glm::normalize(glm::vec3(m4_baseMatrix[0]));
    glm::vec3 rY = glm::normalize(glm::vec3(m4_baseMatrix[1]));
    glm::vec3 rZ = glm::normalize(glm::vec3(m4_baseMatrix[2]));

    float scale_x = glm::length(rX);
    float scale_y = glm::length(rY);
    float scale_z = glm::length(rZ);

    glm::vec3 norm_rX = rX / scale_x;
    glm::vec3 norm_rY = rY / scale_y;
    glm::vec3 norm_rZ = rZ / scale_z;

    glm::mat3 m3_rot = glm::mat3(norm_rX, norm_rY, norm_rZ);
    
    Rotation = glm::quat_cast(m3_rot);
    Scale = glm::vec3(scale_x, scale_y, scale_z);
}

glm::mat4 Transform::toMatrix() const {
    glm::mat4 m4_TransformMatrix = glm::mat4(1.0f);

    m4_TransformMatrix = glm::translate(m4_TransformMatrix, Position);
    m4_TransformMatrix = glm::scale(m4_TransformMatrix, Scale);

    m4_TransformMatrix = m4_TransformMatrix * glm::mat4_cast(Rotation);
    
    return m4_TransformMatrix;
}

Transform Transform::toObjectSpace( const Transform& cf_newOriginBase ) {
    glm::mat4 m4_TransformMatrix = toMatrix();
    glm::mat4 m4_newMatrix = glm::mat4(1.0f);

    m4_newMatrix = glm::inverse( m4_TransformMatrix ) * cf_newOriginBase.toMatrix();

    return Transform( m4_newMatrix );
}

Transform Transform::toWorldSpace( const Transform& cf_localOffsetTransform ) {
    glm::mat4 m4_TransformMatrix = toMatrix();
    glm::mat4 m4_newMatrix = glm::mat4(1.0f);

    m4_newMatrix = m4_TransformMatrix * cf_localOffsetTransform.toMatrix();

    return Transform( m4_newMatrix );
}