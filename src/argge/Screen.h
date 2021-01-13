#ifndef ARGGE_SCREEN_H
#define ARGGE_SCREEN_H
#include "Component.h"
#include <rend/rend.h>
#include <SDL2/SDL.h>

namespace argge
{
    struct Screen
    {  
        ///
        ///Set the size of the window
        ///
        void setWindowSize(SDL_Window* window);
        ///
        ///Get the perspective of the screen.
        ///
        rend::mat4 getPerspective(float _angle, float _nearPlane, float _farPlane);
        ///
        ///Get the orthographic veiw. This should be used for the UI of the game. 
        ///
        void getOrthographic();//for UI stuff later
    private:
        int w;
        int h;
    };
}
#endif