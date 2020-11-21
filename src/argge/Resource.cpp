#include "Resource.h"
#include "CacheManager.h"

namespace argge
{
	void Resource::Load()
	{
		onLoad();
		
	}

	std::weak_ptr<Core> Resource::getCore()
	{
		return cache.lock()->getCore();
	}
}