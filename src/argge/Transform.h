#ifndef ARGGE_TRANSFORM_H
#define ARGGE_TRANSFORM_H

#include "Component.h"
#include <rend/rend.h>

namespace argge
{
    struct Transform : public Component
    {
        Transform();
        rend::mat4 getModelMat();
        void setPos(rend::vec3 pos);
        void setScale(float s);
        void Translate(rend::vec3 trans);
        void Rotate(rend::vec3 rotate);
        rend::vec3 Transform::getPos();
    private:
        rend::vec3 position = rend::vec3(0.0f, 0.0f, 0.0f);
        rend::vec3 rotation = rend::vec3(1.0f);
        rend::vec3 scale = rend::vec3(1.0f);  
        //rend::mat4 model = rend::mat4(1.0f);;
        //set pos, rot, scale

    };
}
#endif 