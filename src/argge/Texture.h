#ifndef ARGGE_TEXTURE_H
#define ARGGE_TEXTURE_H

#include "Resource.h"

#include <memory>
#include <GL/glew.h> // GLuint

namespace argge
{
	struct Renderer;
	struct Texture : public Resource
	{
		void onLoad();
	private:
		friend struct argge::Renderer;
		unsigned char* data;
		int w;
		int h;
		//GLuint textureId;
	};
}
#endif
