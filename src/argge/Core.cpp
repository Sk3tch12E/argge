#include "Core.h"
//#include "CacheManager.h"
#include "Entity.h"
#include "Screen.h"
//#include "Transform.h"
#include "argge/Exception.h"
//#include <rend/rend.h>
#ifdef EMSCRIPTEN
	#include <emscripten.h>
#endif // EMSCRIPTEN


namespace argge 
{
		struct transform;
		
		//If using Emscripten
#ifdef EMSCRIPTEN
		std::weak_ptr<Core> _core;
#endif

	std::shared_ptr<Core> Core::initialize()
	{
		//create a shared pointer to itself
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->self = rtn;

		//create the window
		rtn->window = SDL_CreateWindow("ARGGE",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			800, 600,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		//window exceptions
		if (!rtn->window)
		{
			throw Exception("Failed to create window");
		}
		rtn->glContext = SDL_GL_CreateContext(rtn->window);
		if (!rtn->glContext)
		{
			throw Exception("Failed to create OpenGL context");
		}
		rtn->context = rend::Context::initialize();
		//rtn->cacheManager = std::make_shared<CacheManager>();
		//rtn->cacheManager->core = rtn->self;
		//rtn->cacheManager->self = rtn->cacheManager;
		#ifdef EMSCRIPTEN
				_core = rtn;
		#endif
		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->core = self;
		rtn->self = rtn;
		entities.push_back(rtn);
		//get model returns mat4
		rtn->addComponent<Transform>(); //Transform::getModelMat();
		return rtn;
	}

	void Core::start()
	{
		
		bool running = true;
		//Loop handling
		#ifdef EMSCRIPTEN //Emscripten cant use the normal loop
			emscripten_set_main_loop(Loop, 0, 1);
			running = false;
		#else
		
		
		while (running)
		{
			running = Loop();
		}
		#endif
	}

	bool  Core::Loop()
	{
		SDL_Event e = { 0 };
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				#ifdef EMSCRIPTEN //Emscripten cant use the normal loop
					/*emscripten_set_main_loop(Loop, 0, 1);
					emscripten_stop();*/
				#else
				return false;//end the game loop
				#endif
			}
		}
		for (size_t ei = 0; ei < entities.size(); ei++)
		{
			entities.at(ei)->tick();
		}
		glClearColor(0.8f, 0.8f, 0.93f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (size_t ei = 0; ei < entities.size(); ei++)
		{
			entities.at(ei)->render();
		}
		SDL_GL_SwapWindow(window);
		return true;//contiue the game loop
	}

	std::weak_ptr<Screen> Core::getScreen()
	{
		std::weak_ptr<Screen> rtn = screen;
		return rtn;
	}
}