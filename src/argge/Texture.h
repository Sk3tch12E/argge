#ifndef ARGGE_TEXTURE_H
#define ARGGE_TEXTURE_H

#include "Resource.h"
#include "Core.h"
#include "Exception.h"

#include <memory>
#include <rend/rend.h>
#include <string>


namespace argge
{
	//struct Renderer;
	struct Texture : public Resource
	{
		void onLoad();
		~Texture();
		std::shared_ptr<rend::Texture> texture;
		GLuint getTextureId() { return textureId; }
	private:
		friend struct argge::Renderer;
		friend struct Context;
		std::shared_ptr<Context> context;
		unsigned char* data = NULL;
		int w = 0;
		int h = 0;
		GLuint textureId = 0;
	};
}
#endif
