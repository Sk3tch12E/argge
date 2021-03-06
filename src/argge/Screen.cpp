#include "Component.h"
#include "Entity.h"
#include <rend/rend.h>
#include <SDL2/SDL.h>
namespace argge
{
	struct Screen
	{		
		void setWindowSize(SDL_Window* window)
		{
			SDL_GetWindowSize(window, &w, &h);
		}

		rend::mat4 getPerspective(float _angle, float _nearPlane, float _farPlane)
		{
			rend::mat4 projection = rend::perspective(glm::radians(_angle),
				float(w / h), _nearPlane, _farPlane);
			return projection;
		}

		void getOrthographic() 
		{
			/*rend::mat4 projection = glm::ortho
			return projection;*/
		}//for UI stuff later

	private:
		int w = 1000;
		int h = 1000;
	};

}