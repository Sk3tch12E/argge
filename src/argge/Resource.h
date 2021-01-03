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
		void Load();
		virtual void onLoad() {};
		std::weak_ptr<Core> getCore();
		std::string getPath();
	protected:
		friend struct argge::CacheManager;
		std::string path;
		std::weak_ptr<Core> core;
	};

}

#endif // !ARGGE_RESOURCE_H
