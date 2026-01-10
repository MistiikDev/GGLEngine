#ifndef Transform_H
#define Transform_H

#include <global/maths/Vector3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
    public:
        Transform();
        Transform( float x, float y, float z );
        Transform( const Vector3& pos );

        Transform( const glm::vec3& pos );
        Transform( const glm::mat4& m4_baseMatrix );

        Transform toWorldSpace( const Transform& cf_localOffsetTransform );
        Transform toObjectSpace( const Transform& cf_newOriginBase );

        glm::mat4 toMatrix() const;

        glm::vec3 Position;
        glm::vec3 Scale;
        glm::quat Rotation;

        Transform operator+(const Vector3& rhs) const {
            return Position + glm::vec3(rhs.x, rhs.y, rhs.z);
        }

    private:
        glm::vec3 LookVector;
        glm::vec3 RightVector;
        glm::vec3 UpVector;
};

#endif