#ifndef GGLENGINE_CFRAME_H
#define GGLENGINE_CFRAME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CFrame {
    public:
        CFrame();
        CFrame(float x, float y, float z);
        CFrame(glm::vec3 pos);
        CFrame(glm::mat4 baseMatrix);

        CFrame ToWorldSpace(CFrame localOffsetCFrame);
        CFrame ToObjectSpace(CFrame newOriginBase);

        glm::mat4 toMatrix();

        glm::vec3 Position;
        glm::quat Rotation;
    private:
};

#endif