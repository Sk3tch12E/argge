#ifndef ARGGE_RENDERER_H
#define ARGGE_RENDERER_H

#include "Component.h"
#include "Camera.h"
#include "CacheManager.h"

#include <rend/rend.h>
#include <memory>

namespace argge
{
    struct CacheManager;
    struct Camera;
    struct Texture;
    struct Model;
    struct Renderer : public Component
    {
        ///
        ///Initilise the renderer
        ///
        void onInitialize();
        ///
        ///Passes required things to shader then uses the shader to work out what to render
        ///
        void onRender();
        /** @name Set Textures
        * @brief  These functions are used to set the textures. Unless PBR is being used only the texture needs to be set
        * @param  pass in the path of the file you wish to use as the texture. (Only PNG tested)
        */
        ///@{        
        //* The Texture is the texture as is. This is used if PBR is disabled */
        void setTexture     (const char* path);
        //* Albedo is the texture without any baked in lighting (BPR) */
        void setAlbedo      (const char* path);
        //* AO is the ambient lighting on the object to subtle to be calculated (BPR) */
        void setAO          (const char* path);
        //* Height is the texture used to show displacement on the object (BPR) */
        void setHeight      (const char* path);
        //* Used to show the direction a face is looking (BPR) */
        void setNormal      (const char* path);
        //* Show how metal an object is (BPR) */
        void setMetalness   (const char* path);
        //* Shows how rough the surface of the model is (BPR) */
        void setRoughness  (const char* path);
        ///@}

        ///
        ///Set the model of the entity. (Pass it the path of the object)
        ///
        void setModel       (const char* path);

        bool isPBR = true;
    private:
        friend struct argge::Model;
        friend struct argge::Texture;
        //friend struct argge::Core;
        std::shared_ptr<rend::Shader> shader;

        std::shared_ptr<Model> model;

        std::shared_ptr<Texture> texture;
        std::shared_ptr<Texture> albedo;
        std::shared_ptr<Texture> ao;
        std::shared_ptr<Texture> height;
        std::shared_ptr<Texture> normal;
        std::shared_ptr<Texture> metalness;
        std::shared_ptr<Texture> roughness;
    };
}
#endif
