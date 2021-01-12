#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include <fstream>

namespace argge
{
	void Texture::onLoad()
	{
        texture = getCore()->context->createTexture();
        int bpp = 0;
        unsigned char* data = stbi_load(path, &w, &h, NULL, 3);
        if (!data)
        {
            std::string f = "Failed to open image @" + (std::string)path + "\n";
            throw Exception(f);
        }

        texture->setSize(w, h);
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int r = y * w * 3 + x * 3;

                texture->setPixel(x, y, rend::vec3(
                    data[r] / 255.0f,
                    data[r + 1] / 255.0f,
                    data[r + 2] / 255.0f));
            }
        }
        stbi_image_free(data);


		//data = stbi_load(path.c_str(), &w, &h, NULL, 4);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &textureId);
	}
}