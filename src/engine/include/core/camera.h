#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <core/scene_window.h>
#include <global/maths/Vector3.h>
#include <render/OpenGL/GLShader.h>

class Camera { 
    public:
        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 LookVector = glm::vec3(0.0f, 0.0f, -1.0f); // Looking at -Z from convention, looking through the screen
        glm::vec3 UpVector = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 CameraMatrix = glm::mat4(1.0f);

        int WIDTH, HEIGHT;

        float CameraSpeed, CameraSensitivity;
        float FieldOfView = 45.0f;

        Camera( int Width, int Height, glm::vec3 position );

        void MatrixRender( GLShader& shader, const char* uniform );
        void ComputeMatrix( float nearClip, float farClip, float FieldOfView );

        void Input( EditorViewport* window );
};

#endif