#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "Exception.h"

namespace argge
{
	void Texture::onLoad()
	{
		data = stbi_load(path.c_str(), &w, &h, NULL, 4);
	}
}