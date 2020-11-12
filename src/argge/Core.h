#ifndef ARGGE_CORE_H
#define ARGGE_CORE_H

#ifdef EMSCRIPTEN
    #include <emscripten.h>
#endif

#include <memory>
#include <vector>
#include <rend/rend.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "argge/Exception.h"

namespace argge
{
    //struct Context;
    //struct CacheManager;
    struct Entity;
    //struct Screen;

    struct Core
    {
        static std::shared_ptr<Core> initialize();

        std::shared_ptr<Entity> addEntity();

        void start();

        SDL_Window* window;
        SDL_GLContext glContext;
        std::shared_ptr<rend::Context> context;
        
        //std::weak_ptr<Screen> getScreen();
        //std::shared_ptr<CacheManager> cacheManager;
    private:
        std::vector<std::shared_ptr<Entity>> entities;
        std::weak_ptr<Core> self;
        //std::shared_ptr<Screen> screen;//
        bool Loop();
    };

}
#endif