#include "Model.h"

#include <iostream>
#include <fstream>

namespace argge
{

    void Model::onLoad()
    {
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
