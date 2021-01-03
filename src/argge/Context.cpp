#include "Context.h"
#include "Exception.h"
//#include "ShaderProgram.h"
#include "Texture.h"

#include <GL/glew.h>
namespace argge
{
	std::shared_ptr<Context> Context::initialize()
	{
		std::shared_ptr<Context> rtn = std::make_shared<Context>();

		if (glewInit() != GLEW_OK)
		{
			throw argge::Exception("Failed to initialize glew");
		}

		rtn->self = rtn;

		return rtn;
	}
	
	std::shared_ptr<Texture> Context::createTexture()
	{
		GLuint id;
		glGenTextures(1, &id);

		if (!id)
		{
			throw argge::Exception("Failed to set texture Id");
		}

		std::shared_ptr<Texture> rtn = std::make_shared<Texture>();
		rtn->context = self.lock();
		rtn->textureId = id;

		return rtn;
	}

}