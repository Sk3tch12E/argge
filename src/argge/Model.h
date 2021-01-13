#ifndef ARGGE_MODEL_H
#define ARGGE_MODEL_H

#include "Resource.h"
#include "Exception.h"
#include "Core.h"

#include <rend/rend.h>
#include <string>
#include <memory>

namespace argge
{
	//struct Renderer;
	struct Model : public Resource
	{
		///
		///Use this to do something when the model is loaded.
		///
		virtual void onLoad(); 
		///
		///stores the mesh of the model
		///
		std::shared_ptr<rend::Mesh> mesh;
	private:
		friend struct argge::Renderer;
	};

}

#endif