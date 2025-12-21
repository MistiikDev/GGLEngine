#ifndef CFRAME_H
#define CFRAME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CFrame {
    public:
        CFrame();
        CFrame( float x, float y, float z );
        CFrame( glm::vec3 pos );
        CFrame( glm::mat4 m4_baseMatrix );

        CFrame toWorldSpace( CFrame cf_localOffsetCFrame );
        CFrame toObjectSpace( CFrame cf_newOriginBase );

        glm::vec3 get_LookVector();
        glm::vec3 get_RightVector();
        glm::vec3 get_Vector();

        glm::mat4 toMatrix();

        glm::vec3 Position;
        glm::quat Rotation;
    private:
        glm::vec3 LookVector;
        glm::vec3 RightVector;
        glm::vec3 UpVector;
};

#endif