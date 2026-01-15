#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include <render/OpenGL/GLMesh.h> 
#include <scene/components.h>
#include <render/scene_renderer.h>
#include <core/scene_window.h>

struct MESH : Component {
/*
    TODO : Make it later so that the MESH component chooses GLMesh / VulkanMesh... depending on render settings
    Have an upper class "Mesh" that holds either a GLMesh / VulkanMesh, and use that upper class evertwhere else
*/ 
    public:
        MESH( const char* meshReference ) {
            std::string mesh_extension = Engine::string::getFileExtension(meshReference);

            if (mesh_extension == "obj") {
                GLMesh_Data GLMesh_data;
                GLMaterial_Data mtl_data;

                OBJImport::_loadOBJ( meshReference, &GLMesh_data, &mtl_data );
            } else {
                Engine::log::print("[COMPONENT ERR] : ", "Following mesh extension is not handled : .", mesh_extension);
            }

        }; // Somehow load, independently from the file format, verticies and indicies from this

        void Tick(unsigned int deltaTime) override {
            // Find a way to do this efficiently m_mesh.Draw( GetCurrentCamera() );
        }

    private:
        GLMesh* m_mesh;

};

#endif