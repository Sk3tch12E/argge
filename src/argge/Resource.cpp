#include "Resource.h"
#include "CacheManager.h"

namespace argge
{
	void Resource::Load()
	{
		onLoad();		
	}

	std::string Resource::getPath()
	{
		return path;
	}

	std::weak_ptr<Core> Resource::getCore()
	{
		return core.lock();
	}
}