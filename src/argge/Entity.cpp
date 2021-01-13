#include "Entity.h"
#include "Component.h"

namespace argge
{
    void Entity::tick()
    {
		//onTick();
        for(size_t ci = 0; ci < components.size(); ci++)
        {
            components.at(ci)->tick();
        }
    }

	//void Component::onTick() {}

	//void Component::onRender() {}

	void Entity::render()
	{
		for (size_t ci = 0; ci < components.size(); ci++)
		{
			components.at(ci)->render();
		}
	}
	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();
	}

	std::shared_ptr<Transform> Entity::getTransform()
	{
		return getComponent<Transform>();
	}
}

