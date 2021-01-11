#include "Model.h"
#include "Core.h"

#include <rend/rend.h>

#include <iostream>
#include <fstream>

namespace argge
{

    void Model::onLoad()
    {
        //std::cout << "Loading model: " << getPath() << std::endl;
        //mesh = getCore()->context->createMesh();
        //std::ifstream file(getPath());

        //if (!file.is_open())
        //{
        //    throw Exception("Failed to open object @" + (std::string)path + "\n");
        //}
        //std::cout << "model loaded\n";
        //std::string content;
        ////line declearded outside of the while to stp it from allocating and reallocating it
        //std::string line;

        //while (!file.eof())
        //{
        //    getline(file, line);
        //    content += line + "\n";
        //}
        //mesh->parse(content);

        std::ifstream file(path);
        if (!file.is_open())
        {
            std::string f = "Failed to open object @" + (std::string)path + "\n";
            throw Exception(f);
        }
        std::cout << "model loaded\n";
        std::string content;
        std::string line;//line declearded outside of the while to stp it from allocating and reallocating it
        while (!file.eof())
        {
            getline(file, line);
            content += line + '\n'; //getting each line strips the new line char
        }
        mesh = getCore()->context->createMesh();
        mesh->parse(content);
    }

}
