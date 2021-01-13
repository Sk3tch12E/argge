#ifndef ARGGE_TRANSFORM_H
#define ARGGE_TRANSFORM_H

#include "Component.h"
#include <rend/rend.h>

namespace argge
{
    struct Transform : public Component
    {
        ///
        ///Get the model matrix from the entity. This stores the scale, position and rotation.
        ///
        rend::mat4 getModelMat();
        ///
        ///Set the position of the model in  the world (not relative to the current posistion)
        ///
        void setPos(rend::vec3 pos);
        ///
        ///Set the scale of the entity
        ///
        void setScale(float s);
        ///
        ///Move the entity based on its current position in space. 
        ///
        void Translate(rend::vec3 trans);
        ///
        ///Rotate the entity  based on it current rotation.
        ///
        void Rotate(rend::vec3 rotate);
        ///
        ///Get the current position of the model.
        ///
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