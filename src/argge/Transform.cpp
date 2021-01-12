#include "Transform.h"
#include <rend/rend.h>
#include <iostream>
namespace argge
{
	rend::mat4 Transform::getModelMat()
	{	
		glm::mat4 view(1.0f);view = glm::translate(glm::mat4(1), position);
		view = rend::rotate(view, rend::radians(rotation.x), rend::vec3(1.0f, 0.0f, 0.0f));
		view = rend::rotate(view, rend::radians(rotation.y), rend::vec3(0.0f, 1.0f, 0.0f));
		view = rend::rotate(view, rend::radians(rotation.z), rend::vec3(0.0f, 0.0f, 1.0f));
		
		return view;
	}

	void Transform::setPos(rend::vec3 pos)
	{
		position = pos;
		//model = glm::translate(model, position);
	}

	void Transform::setScale(float s)
	{
		scale = rend::vec3(s);
		//model = glm::scale(model, scale);
	}
	rend::vec3 Transform::getPos()
	{
		return position;
	}

	void Transform::Translate(rend::vec3 trans)
	{
		rend::vec4 fwd = getModelMat() * rend::vec4(trans, 0);
		position += rend::vec3(fwd);
		//model = glm::translate(model, trans);
	}

	void Transform::Rotate(rend::vec3 rotate)
	{
		rotation += rotate;
		//model = rend::rotate(model, rend::radians(rotate.x), rend::vec3(1.0f, 0.0f, 0.0f));
		//model = rend::rotate(model, rend::radians(rotate.y), rend::vec3(0.0f, 1.0f, 0.0f));
		//model = rend::rotate(model, rend::radians(rotate.z), rend::vec3(0.0f, 0.0f, 1.0f));
	}

}