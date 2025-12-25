#include <render/texture.h>

Texture::Texture(const char* texturePath, GLuint slot, GLenum textureType, GLenum textureFormat, GLenum textureScaleType, GLenum textureWrapType) {
    stbi_set_flip_vertically_on_load(true);

    unsigned char* image_bytes = stbi_load(texturePath, &this->width, &this->height, &this->colorChannelNum, 0);

    if (image_bytes == nullptr) {
        std::cerr << "TEXTURE_LOAD_ERR : FAILED LOADING TEXTURE BYTES" << "\n";

        throw std::logic_error("TEXTURE_LOAD_ERR : FAILED LOADING TEXTURE BYTES");
    }

    glGenTextures(1, &this->TextureId);
    glActiveTexture(slot);
    glBindTexture(textureType, this->TextureId); // Create Texture object in opengl and bind current id to it

    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, textureScaleType);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, textureScaleType);

    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, textureWrapType); // Wrapping type on the "X" axis
    glTexParameteri(textureType, GL_TEXTURE_WRAP_R, textureWrapType); // Wrapping type on the "Y" axis
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, textureWrapType); // Wrapping type on the "Z" axis

    // Pass the actual image data onto the texture frame
    glTexImage2D(textureType, 0, GL_RGBA, this->width, this->height, 0, textureFormat, GL_UNSIGNED_BYTE, image_bytes);
    glGenerateMipmap(textureType);

    this->TextureType = textureType;

    // Cleanup
    stbi_image_free(image_bytes);
    glBindTexture(textureType, 0); // Unbind texture2D object
}

void Texture::Sample(GLShader& textureShader, const char* uniform, GLuint slot) {
    GLuint texSampleUni = glGetUniformLocation(textureShader.ID, uniform);
    textureShader.Activate();

    glUniform1i(texSampleUni, slot); // Set the sample2D Texture0 (or Texture1234...) to current slot
}

void Texture::Bind()
{
	glBindTexture(TextureType, TextureId);
}

void Texture::Unbind()
{
	glBindTexture(TextureType, 0);
}

void Texture::Destroy()
{
	glDeleteTextures(1, &TextureId);
}