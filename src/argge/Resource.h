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
        template <typename T>
        std::shared_ptr<T> load(const std::string& path)
        {
            std::shared_ptr<T> rtn;

            for (size_t i = 0; i < resources.size(); i++)
            {
                if (path == resources.at(i)->getPath())
                {
                    rtn = std::dynamic_pointer_cast<T>(resources.at(i));
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

		virtual ~Resource();
		virtual void onLoad();

		std::shared_ptr<Core> getCore();
		std::string getPath();
	protected:
		friend struct argge::CacheManager;
		std::string path;
		std::weak_ptr<Core> core;
	};

}

#endif // !ARGGE_RESOURCE_H
