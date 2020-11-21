#ifndef ARGGE_RESOURCE_H
#define ARGGE_RESOURCE_H

#include <memory>
#include <string>
namespace argge
{
	struct CacheManager;
	struct Core;
	struct Resource
	{
		friend struct argge::CacheManager;
		void Load();
		virtual void onLoad() {};
		std::weak_ptr<Core> getCore();

	protected:
		std::string path;
		std::weak_ptr<CacheManager> cache;
	};

}

#endif // !ARGGE_RESOURCE_H
