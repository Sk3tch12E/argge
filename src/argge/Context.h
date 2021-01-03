#ifndef ARGGE_CONTEXT_H
#define ARGGE_CONTEXT_H

#include <memory>

namespace argge
{
	struct Texture;
	struct Context
	{
		static std::shared_ptr<Context> initialize();
		std::shared_ptr<Texture> createTexture();
	private:
		std::weak_ptr<Context> self;
	};
}

#endif