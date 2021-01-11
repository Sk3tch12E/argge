#ifndef ARGGE_MODEL_H
#define ARGGE_MODEL_H

#include <rend/rend.h>

#include "Resource.h"
#include "Exception.h"

#include <string>
#include <memory>

namespace argge
{

	struct Renderer;

	struct Model : public Resource
	{
		virtual void onLoad(); 
		std::shared_ptr<rend::Mesh> mesh;
	private:
		friend struct argge::Renderer;
	};

}

#endif