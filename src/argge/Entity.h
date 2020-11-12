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

    struct Entity
    {
        friend struct argge::Core;
        template <typename T>
        std::shared_ptr<T> addComponent()
        {
            std::shared_ptr<T> rtn = std::make_shared<T>();
            rtn->entity = self;
            components.push_back(rtn);

            rtn->onInitialize();
            return rtn;
        }

        void tick();
        void render();
        std::shared_ptr<Core> getCore();
        
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

    private:
        std::vector<std::shared_ptr<Component>> components; //maybe change to list
        std::weak_ptr<Core> core;
        std::weak_ptr<Entity> self;
    };
}
#endif
