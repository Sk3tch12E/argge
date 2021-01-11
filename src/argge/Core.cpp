#include "Core.h"
#include "CacheManager.h"
#include "Entity.h"
#include "Screen.h"
#include "Transform.h"
#include "Input.h"
#include "argge/Exception.h"
//#include <rend/rend.h>
#include <iostream>
#ifdef EMSCRIPTEN
	#include <emscripten.h>
#endif // EMSCRIPTEN


namespace argge 
{
		struct Transform;
		struct Camera;
		struct Input;
		struct CacheManager;

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
			1000, 1000,
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
		rtn->input = std::make_shared<Input>();


		/*rtn->cacheManager = std::make_shared<CacheManager>();		
		rtn->cacheManager->core = rtn->self;
		rtn->cacheManager->self = rtn->cacheManager;*/
		rtn->cacheManager = std::make_shared<CacheManager>();
		rtn->cacheManager->core = rtn;

		#ifdef EMSCRIPTEN
				_core = rtn;
		#endif

		return rtn;
	}

	///
	///Used to create an entity in the scene
	///
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

	///
	///Called before the game loop
	///
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
	///
	///Game loop
	///
	bool  Core::Loop()
	{
		float currentframe = SDL_GetTicks();
		deltaTime = (currentframe - lastframe) /1000.0f;
		lastframe = currentframe;

		SDL_Event e = { 0 };
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) //if quitting
			{
				#ifdef EMSCRIPTEN //Emscripten cant use the normal loop
				emscripten_stop();
				#else
				return false;//end the game loop
				#endif
			}
			else if (e.type == SDL_KEYDOWN) {
				input->keys.push_back(e.key.keysym.sym);
				input->downKeys.push_back(e.key.keysym.sym);
	/*			switch (e.key.keysym.sym)
				{
				case 'w':
					LightPos.z += 1;
					break;
				case 's':
					LightPos.z -= 1;
					break;
				case 'a':
					break;
				case 'd':
					break;
				default:
					break;
				}*/
			}
			else if (e.type == SDL_KEYUP)
			{ 
				for (std::vector<int>::iterator it = input->keys.begin(); it != input->keys.end();)
				{
					if (*it == e.key.keysym.sym)
						it = input->keys.erase(it);
					else 
						it++; 
				}
				input->upKeys.push_back(e.key.keysym.sym);
			}
		}

		//Run tick on all entities
		for (size_t ei = 0; ei < entities.size(); ei++)
		{
			entities.at(ei)->tick();
		}

		glClearColor(0.8f, 0.8f, 0.93f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Render all entities
		for (size_t ei = 0; ei < entities.size(); ei++)
		{
			for (size_t ci = 0; ci < cameras.size(); ci++)
			{
				currentCamera = cameras.at(ci).lock();
				entities.at(ei)->render();
			}
		}
		SDL_GL_SwapWindow(window);
		if (input->downKeys.size() > 0) {
			input->downKeys.clear();
		}
		//input->clearKeysOnFrame();

		return true;//contiue the game loop
	}

	///
	///Get the screen size
	///
	std::weak_ptr<Screen> Core::getScreen()
	{
		std::weak_ptr<Screen> rtn = screen;
		return rtn;
	}

	///
	///Get the input class used to get player inputs
	///
	std::shared_ptr<Input> Core::getInput()
	{
		return input;
	}
	
	///
	///get the current camera
	///
	std::shared_ptr<Camera> Core::getCamera()
	{
		return currentCamera;
	}
	
	///
	///get the cache (Used to store resources like textures and models)
	///
	std::shared_ptr<CacheManager> Core::getCache()
	{
		return cacheManager;
	}
}