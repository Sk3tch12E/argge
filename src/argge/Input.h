#ifndef ARGGE_INPUT_H
#define ARGGE_INPUT_H

#include <vector>

#ifdef USE_SDL
//#define KEY_A 'a'
//#define KEY_UP SDLK_UP
#else 
#define KEY_A 223
#define KEY_UP GLUT_UPARROW
#endif

namespace argge
{
    struct Core;
    struct Input
    {
        bool getKey(int key);
        /*bool getKeyDown(int key);
        bool getKeyUp(int key);

        bool clearKeysOnFrame();*/
        
    private:
        friend struct argge::Core;

        std::vector<int> keys;
        std::vector<int> downKeys; 
        std::vector<int> upKeys;

    };
}
#endif