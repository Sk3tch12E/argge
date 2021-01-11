#ifndef ARGGE_RENDERER_H
#define ARGGE_RENDERER_H

#include "Component.h"
//#include "Texture.h"
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
        
        void setTexture(const char* path);
        void setAlbedo(const char* path);
        void setAO(const char* path);
        void setHeight(const char* path);
        void setNormal(const char* path);
        void setMetalness(const char* path);
        void setRoughnesse(const char* path);

        void setModel(std::shared_ptr<Model> _model);

    private:
        //friend struct argge::Core;
        std::shared_ptr<rend::Shader> shader;

        //std::shared_ptr<rend::Mesh> shape;
        std::shared_ptr<Model> model;

        std::shared_ptr<rend::Texture> texture;
        std::shared_ptr<rend::Texture> albedo;
        std::shared_ptr<rend::Texture> ao;
        std::shared_ptr<rend::Texture> height;
        std::shared_ptr<rend::Texture> normal;
        std::shared_ptr<rend::Texture> metalness;
        std::shared_ptr<rend::Texture> roughness;
    };
}
#endif
