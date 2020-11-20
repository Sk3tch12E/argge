#include "Transform.h"
#include <rend/rend.h>

namespace argge
{
	rend::mat4 Transform::getModelMat()
	{
		//rend::mat4 model = rend::mat4(1.0f);
		rend::mat4 model = rend::mat4(1.0f);
		position = glm::vec3(0.0f, 0.0f, -10.0f);
		model = rend::translate(model, position);
		rotation.y += 0.1;
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f,0.0f,0.0f ));
		model = rend::rotate(model, rend::radians(rotation.y), rend::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = rend::scale(model, scale);
		return model;
	}

}