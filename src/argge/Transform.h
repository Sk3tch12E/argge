#ifndef ARGGE_TRANSFORM_H
#define ARGGE_TRANSFORM_H

#include "Component.h"
#include <rend/rend.h>

namespace argge
{
    struct Transform : public Component
    {
        rend::mat4 getModelMat();
    private:
        rend::vec3 position = rend::vec3(0.0f, 0.0f, -5.0f);
        rend::vec3 rotation = rend::vec3(1.0f);
        rend::vec3 scale = rend::vec3(1.0f);  
        //set pos, rot, scale

    };
}
#endif 