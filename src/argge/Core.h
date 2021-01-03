#ifndef ARGGE_CORE_H
#define ARGGE_CORE_H

#ifdef EMSCRIPTEN
    #include <emscripten.h>
#endif

#include <memory>
#include <vector>
#include <rend/rend.h>
#include <SDL2/SDL.h>
//#include "Camera.h"


namespace argge
{
    struct Renderer;
    struct Input;
    struct CacheManager;
    struct Camera;
    struct Entity;
    struct Screen;
    struct Texture;

    struct Core
    {
        static std::shared_ptr<Core> initialize();

        std::shared_ptr<Entity> addEntity();
        std::weak_ptr<Screen> getScreen();
        std::shared_ptr<Camera> getCamera();
        std::shared_ptr<Input> getInput();
        //std::shared_ptr<rend::Context> context;
        void start();
        rend::vec3 LightPos = rend::vec3(0, 0, 0);

private:
        friend struct argge::Camera;
        friend struct argge::Renderer;
        //friend struct argge::Model;
        friend struct argge::Texture;
        //friend struct argge::Input;
        
        SDL_Window* window;
        SDL_GLContext glContext;
        std::shared_ptr<rend::Context> context;
        std::shared_ptr<Input> input;
        std::shared_ptr<CacheManager> cacheManager;        
        std::shared_ptr<Screen> screen;
        std::vector<std::shared_ptr<Entity>> entities;
        std::weak_ptr<Core> self;
        

        std::shared_ptr<Camera> currentCamera;
        std::vector<std::weak_ptr<Camera>> cameras;

        bool Loop();
    };

}
#endif