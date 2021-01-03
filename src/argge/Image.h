#ifndef ARGGE_IMAGE_H
#define ARGGE_IMAGE_H

#include "Component.h"

namespace argge
{
    struct Image : public Component
    {        
        std::vector<rend::vec4> data;
        void getImage();
        rend::vec4 getPixel(unsigned int x, unsigned int y);
    };
}
#endif