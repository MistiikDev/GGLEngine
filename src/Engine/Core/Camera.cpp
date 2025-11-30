#include "Camera.h"

Camera::Camera(int Width, int Height, glm::vec3 position) {
    Position = position;
    WIDTH = Width;
    HEIGHT = Height;

    CameraSpeed = 0.1f;
    CameraSensitivity = 100.0f;
}

void Camera::MatrixRender(float nearClip, float farClip, float FieldOfView, ShaderInstance& shader, const char* uniform) {
    glm::mat4 view_mat = glm::mat4(1.0f);
    glm::mat4 projection_mat = glm::mat4(1.0f);

    view_mat = glm::lookAt(Position, Position + LookVector, UpVector);
    projection_mat = glm::perspective(glm::radians(FieldOfView), (float)(WIDTH / HEIGHT), nearClip, farClip);

    GLuint camera_uniform = glGetUniformLocation(shader.ID, uniform);

    glUniformMatrix4fv(camera_uniform, 1, GL_FALSE, glm::value_ptr(projection_mat * view_mat));
}


void Camera::Input(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Position += CameraSpeed * LookVector;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Position += -CameraSpeed * LookVector;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        Position += CameraSpeed * UpVector;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        Position += -CameraSpeed * UpVector;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Position += CameraSpeed * glm::normalize(glm::cross(LookVector, UpVector)); // (LookVec x UpVec) return RightVec;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Position += -CameraSpeed * glm::normalize(glm::cross(LookVector, UpVector));
    }

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    float rotX = (float)(mouseX - WIDTH / 2) * (CameraSensitivity / 1000.0f);
    float rotY = (float)(mouseY - HEIGHT / 2) * (CameraSensitivity / 1000.0f);

    glm::mat4 yRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-rotY), glm::normalize(glm::cross(LookVector, UpVector)));
    glm::mat4 xRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-rotX), glm::normalize(UpVector));

    glm::mat4 RotationMatrix = yRotationMatrix * xRotationMatrix;  

    LookVector = glm::vec3(RotationMatrix * glm::vec4(LookVector, 1.0f));

    glfwSetCursorPos(window, (WIDTH / 2), (HEIGHT / 2));
}