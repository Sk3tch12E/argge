#ifndef ARGGE_CORE_H
#define ARGGE_CORE_H

#ifdef EMSCRIPTEN
    #include <emscripten.h>
#endif

#include <memory>
#include <vector>
#include <rend/rend.h>
#include <SDL2/SDL.h>

namespace argge
{
    struct Renderer;
    struct Input;
    struct CacheManager;
    struct Camera;
    struct Entity;
    struct Screen;
    struct Texture;
    struct Model;

    struct Core
    {
        ///
        ///Call to initilize the core when creating it.
        ///
        static std::shared_ptr<Core> initialize();
        ///
        ///Used to create an entity in the scene
        ///
        std::shared_ptr<Entity> addEntity();
        ///
        ///Used to get the screen being used
        ///
        std::weak_ptr<Screen> getScreen();
        ///
        ///Used to get the current camera
        ///
        std::shared_ptr<Camera> getCamera();
        ///
        ///Used to get the input component. When passed a character related to a key on a keyboard it will return true if it is being pressed.
        ///
        std::shared_ptr<Input> getInput();
        ///
        ///used to get the cache where resources like images and models are stored.
        ///
        std::shared_ptr<CacheManager> getCache();
        ///
        /// starts the game loop. Call after creating objects that the player will see after the game loads.
        ///
        void start();
        ///
        ///Returns the time between frames. Use this to make things like physics not frame rate dependant
        ///
        float DeltaTime();

private:
        friend struct argge::Camera;
        friend struct argge::Renderer;
        friend struct argge::Model;
        friend struct argge::Texture;
        //friend struct argge::Input;
        
        SDL_Window* window;
        SDL_GLContext glContext;
        std::shared_ptr<rend::Context> context;
        std::shared_ptr<Input> input;
        std::shared_ptr<CacheManager> cacheManager;        
        std::shared_ptr<Screen> screen;

        std::shared_ptr<Camera> currentCamera;
        std::vector<std::weak_ptr<Camera>> cameras;
        
        std::vector<std::shared_ptr<Entity>> entities;
        std::weak_ptr<Core> self;

        float deltaTime = 0.0f;
        float lastframe = 0.0f;
        bool Loop();
    };

}
#endif