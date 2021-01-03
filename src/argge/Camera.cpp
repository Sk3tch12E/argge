#include "Camera.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"

namespace argge
{
    void Camera::onInitialize()
    {
        std::shared_ptr<Camera> self = getEntity()->getComponent<Camera>();
        getCore()->cameras.push_back(self);
    }

    rend::mat4 Camera::getView()
    {
        rend::mat4 view = rend::mat4(0);
        /*glm::inverse(rend::mat4(0));*/
        rend::mat4 pos = getTransform()->getModelMat();
        view = rend::inverse(pos);
        return view;
    }

    std::shared_ptr<rend::RenderTexture> Camera::getRenderTexture()
    {
        return renderTexture;
    }

    std::shared_ptr<rend::RenderTexture> Camera::addRenderTexture()
    {
        renderTexture = getCore()->context->createRenderTexture();

        return renderTexture;
    }

}