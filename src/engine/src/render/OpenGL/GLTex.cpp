#include <render/OpenGL/GLTex.h>
#include <render/texture_cache.h>

GLTex::GLTex( const char* texturePath ) {
    std::cout << "[GLTEX] : " << std::string(texturePath) << std::endl;
    stbi_set_flip_vertically_on_load(true);

    int w, h, channels;
    unsigned char* data = stbi_load(texturePath, &w, &h, &channels, 0);
    
    if (data == nullptr) {
        std::cout << "TEXTURE_LOAD_ERR : FAILED LOADING TEXTURE BYTES" << "\n";

        throw std::logic_error("TEXTURE_LOAD_ERR : FAILED LOADING TEXTURE BYTES");
    }

    this->width  = w;
    this->height = h;

    std::cout << "[GLTEX] : Tex Data -> ID : " << this->TextureId << " / w = " << w << " / h = " << h << " / channels = " << channels << std::endl;

    glGenTextures(1, &this->TextureId);
    glBindTexture(GL_TEXTURE_2D, this->TextureId); // Create Texture object in opengl and bind current id to it

    std::cout << "[GLTEX] : Tex Bind : " << this->TextureId << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping type on the "X" axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT); // Wrapping type on the "Y" axis

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    std::cout << "[GLTEX] : Tex Format : " << format << std::endl;

    // Pass the actual image data onto the texture frame
    glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Cleanup
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture2D object
}

void GLTex::Sample(GLShader& textureShader, GLuint slot, const char* uniform) {
    GLuint texSampleUni = glGetUniformLocation(textureShader.ID, uniform);
    textureShader.Activate();

    glUniform1i(texSampleUni, slot); // Set the sample2D Texture0 (or Texture1234...) to current slot
}

void GLTex::Bind(GLuint slot)
{   
    glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, TextureId);
}

void GLTex::Unbind(GLuint slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTex::Destroy()
{
	glDeleteTextures(1, &TextureId);
}