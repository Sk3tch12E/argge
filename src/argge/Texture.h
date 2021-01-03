#ifndef ARGGE_TEXTURE_H
#define ARGGE_TEXTURE_H

#include "Resource.h"

#include <memory>
#include <rend/rend.h>

namespace argge
{
	//struct Renderer;
	struct Texture : public Resource
	{
		Texture();
		void onLoad();
		~Texture();

		GLuint getTextureId() { return textureId; }
	private:
		//friend struct argge::Renderer;
		friend struct Context;
		std::shared_ptr<Context> context;
		unsigned char* data;
		int w;
		int h;
		GLuint textureId;
	};
}
#endif
