#ifndef ARGGE_ENTITY_H
#define ARGGE_ENTITY_H

#include <vector>
#include <memory>
#include "Exception.h"
#include "Transform.h"

namespace argge
{
    struct Component;
    struct Core;
    struct Exception;
    struct Transform;
    struct Entity
    {
        friend struct argge::Core;
        ///
        ///Will call the onTick before calling the tick on all components attached to the entity
        ///
        void tick();
        ///
        ///Calls the entity on render before going through the components and calling their render function
        ///
        void render();
        ///
        ///Get the core
        ///
        std::shared_ptr<Core> getCore();

        ///
        ///Add a component to the entity.
        ///
        template <typename T>
        std::shared_ptr<T> addComponent()
        {
            std::shared_ptr<T> rtn = std::make_shared<T>();
            rtn->entity = self;
            components.push_back(rtn);

            rtn->onInitialize();
            return rtn;
        }        
        ///
        ///Get a component attached to the entity
        ///
        template <typename T>
        std::shared_ptr<T> getComponent()
        {
            for (size_t ci = 0; ci < components.size(); ci++)
            {
                std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(components.at(ci));
                if (rtn)
                {
                    return rtn;
                }
            }
            throw Exception("Requested component was not found");
        }
        ///
        ///Get the transform of the entity
        ///
        std::shared_ptr<Transform> getTransform();
    
    private:
        std::vector<std::shared_ptr<Component>> components; //maybe change to list
        
        std::weak_ptr<Core> core;
        std::weak_ptr<Entity> self;
    };
}
#endif
