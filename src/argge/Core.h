#include <memory>
#include <vector>

namespace argge
{
    struct Entity;

    struct Core
    {
        static std::shared_ptr<Core> initialize();

        std::shared_ptr<Entity> addEntity();

        void start();

    private:
        std::vector<std::shared_ptr<Entity>> entities;

    };

}