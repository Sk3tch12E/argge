#ifndef ARGGE_CACHEMANAGER_H
#define ARGGE_CACHEMANAGER_H

#include <memory>
#include <vector>
#include "Resource.h"
#include "Core.h"
namespace argge
{
	struct Core;
	struct Resource;
	struct CacheManager
	{
		///
		///Used to load resources. Will call the resources onLoad function where the resource load function should be.
		///
		template <typename T>
		std::shared_ptr<T> load(const char* path)
		{
			std::shared_ptr<T> rtn;

			for (size_t ri = 0; ri < resources.size(); ri++)
			{
				if (resources.at(ri)->path == path)
				{
					rtn = std::dynamic_pointer_cast<T>(resources.at(ri));
					if (!rtn) continue;
					return rtn;
				}
			}
			rtn = std::make_shared<T>();
			rtn->core = core;
			rtn->path = path;
			rtn->onLoad();
			resources.push_back(rtn);
			return rtn;
		}

	private:
		friend struct argge::Core;
		
		std::vector<std::shared_ptr<Resource>> resources;
		std::weak_ptr<CacheManager> self;
		std::weak_ptr<Core> core;
	};
}
#endif // !ARGGE_CACHEMANAGER_H
