#include "Component.h"
#include <rend/rend.h>
#include <SDL2/SDL.h>

namespace argge
{
    struct Screen
    {  
        void setWindowSize(SDL_Window* window);
        rend::mat4 getPerspective(float _angle, float _nearPlane, float _farPlane);
        void getOrthographic();//for UI stuff later
    private:
        int w;
        int h;
    };
}