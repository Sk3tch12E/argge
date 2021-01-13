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
        ///
        ///Initialize the component
        ///
        void onInitialize() {};
        ///
        ///Will run the component onTick function
        ///
        void tick();
        ///
        ///Use this funtion in your own components to make them do something every tick
        ///
        virtual void onTick();
        ///
        ///Calls the onRender function after the entity is rendered on screen
        ///
        void render();
        ///
        ///Use this funtion in your own components to make them do something after the entity is rendered
        ///
        virtual void onRender();
        ///
        ///Get the game engine core
        ///
        std::shared_ptr<Core> getCore();
        ///
        ///The the entity the component is attached to.
        ///
        std::shared_ptr<Entity> getEntity();
        ///
        ///Get the transform component. This Component is required on all entities.
        ///
        std::shared_ptr<Transform> getTransform();

    private:
        std::weak_ptr<Entity> entity;
    };
}

#endif
