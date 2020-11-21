#ifndef ARGGE_CACHEMANAGER_H
#define ARGGE_CACHEMANAGER_H

#include <memory>
#include <vector>

namespace argge
{
	struct Core;
	struct Resource;
	struct CacheManager
	{
		friend struct argge::Core;

		template <typename T>
		std::shared_ptr<T> loadResources(const char* path)
		{

			for (size_t ri = 0; ri < resources.size(); ri++)
			{
				if (resources.at(ri)->path.c_str() == path)
				{
					std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(resources.at(ri));
					return rtn;
				}
			}
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->cache = self;
			rtn->path = path;
			rtn->onLoad();
			resources.push_back(rtn);
			return rtn;
		}

		std::shared_ptr<Core> getCore() { return core.lock(); };

	private:
		std::weak_ptr<CacheManager> self;
		std::weak_ptr<Core> core;
		std::vector<std::shared_ptr<Resource>> resources;
	};
}
#endif // !ARGGE_CACHEMANAGER_H
