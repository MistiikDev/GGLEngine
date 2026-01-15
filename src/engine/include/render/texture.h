#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb/stb_image.h>
#include <render/scene_renderer.h>

class Texture {
    public:
        int width;
        int height; 
        int colorChannelNum;

        virtual void Render(const RenderContext& ctx);
        virtual void Unbind();
        virtual void Destroy();
};

#endif