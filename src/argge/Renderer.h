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
        void onInitialize();
        void onRender();
        
        void setTexture     (const char* path);
        void setAlbedo      (const char* path);
        void setAO          (const char* path);
        void setHeight      (const char* path);
        void setNormal      (const char* path);
        void setMetalness   (const char* path);
        void setRoughnesse  (const char* path);

        void setModel       (const char* path);

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
