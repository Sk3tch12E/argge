#include "Renderer.h"
#include "Core.h"
#include "Transform.h"
#include "Exception.h"

#include <iostream>
#include <fstream>
#include "Entity.h"

namespace argge
{

    void Renderer::onInitialize()
    {
        std::cout << "Initializing" << std::endl;

        const char* src =
            "\n#ifdef VERTEX\n                       " \
            "attribute vec3 a_Position;              " \
            "attribute vec3 a_Normal;                " \
            "attribute vec2 a_TexCoord;              " \
            "uniform mat4 u_Projection;              " \
            "uniform mat4 u_Model;                   " \
            "varying vec2 v_TexCoord;                " \
            "                                        " \
            "void main()                             " \
            "{                                       " \
            "  gl_Position = u_Projection * u_Model * vec4(a_Position, 1); " \
            "  v_TexCoord = a_TexCoord;              " \
            "  if(a_Normal.x > 999) gl_Position.x = 1;"\
            "}                                       " \
            "                                        " \
            "\n#endif\n                              " \
            "\n#ifdef FRAGMENT\n                     " \
            "varying vec2 v_TexCoord;                " \
            "                                        " \
            "void main()                             " \
            "{                                       " \
            "                                        " \
            "  gl_FragColor = vec4(v_TexCoord, 0, 1);" \
            "}                                       " \
            "                                        " \
            "\n#endif\n                              ";

        shader = getCore()->context->createShader();
        shader->parse(src);

        std::ifstream file("../src/demo/curuthers/curuthers.obj");        
        if (!file.is_open())
        {
            throw Exception("Failed to open file");
        }
        std::cout << "model loaded\n";
        std::string content;
        std::string line;//line declearded outside of the while to stp it from allocating and reallocating it
        while (!file.eof())
        {            
            getline(file, line);
            content += line + '\n'; //getting each line strips the new line char
        }

        shape = getCore()->context->createMesh();
        shape->parse(content);
    }

    void Renderer::onRender()
    {
        //shader->setAttribute("a_Position", shape);
        shader->setMesh(shape);
        shader->setUniform("u_Projection", rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
        shader->setUniform("u_Model", getEntity()->getComponent<Transform>()->getModelMat());
        //shader->setUniform("u_View", ...)
        /*rend::vec3 position = glm::vec3(0, 0, -10.0f);
        rend::translate(u_Model, position);*/
        shader->render();
    }

    void Renderer::setTexture(const char* path)
    {
    }

    void Renderer::setMesh(const char* path)
    {
    }

}