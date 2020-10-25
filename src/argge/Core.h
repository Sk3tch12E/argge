#ifndef ARGGE_CORE_H
#define ARGGE_CORE_H

#include <memory>
#include <vector>
#include <rend/rend.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <argge/Exception.h>

namespace argge
{
    struct Entity;

    struct Core
    {
        static std::shared_ptr<Core> initialize();

        std::shared_ptr<Entity> addEntity();

        void start();

        SDL_Window* window;
        SDL_GLContext glContext;
        std::shared_ptr<rend::Context> context;
    private:
        std::vector<std::shared_ptr<Entity>> entities;
        std::weak_ptr<Core> self;
    };

}
#endif