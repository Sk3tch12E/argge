#ifndef ARGGE_COMPONENT_H
#define ARGGE_COMPONENT_H
#include <memory>

namespace argge
{
    struct Core;
    struct Entity;
    struct Transform;
    struct Component
    {
        friend struct argge::Entity;
        
        void onInitialize() {};
        void tick();
        virtual void onTick();
        void render();
        virtual void onRender();
        std::shared_ptr<Core> getCore();
        std::shared_ptr<Entity> getEntity();
        std::shared_ptr<Transform> getTransform();

    private:
        std::weak_ptr<Entity> entity;
    };
}

#endif
