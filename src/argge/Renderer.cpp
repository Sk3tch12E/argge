#include "Renderer.h"
#include "Core.h"
#include "Transform.h"
#include "Exception.h"
#include "CacheManager.h"
#include "Model.h"

#include <stb/stb_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Entity.h"

namespace argge
{
    void Renderer::onInitialize()
    {

        albedo = getCore()->context->createTexture();
        ao = getCore()->context->createTexture();
        height = getCore()->context->createTexture();
        normal = getCore()->context->createTexture();
        metalness = getCore()->context->createTexture();
        roughness = getCore()->context->createTexture();



        std::cout << "Initializing Shader Program" << std::endl;

        std::string src;
        std::ifstream source("./Resources/ShaderProgramPBR3.txt");
        std::string line;        
        while (!source.eof())
        {
            getline(source, line);
            src += line + '\n'; //getting each line strips the new line char
        }

        shader = getCore()->context->createShader();
        shader->parse(src);
        std::cout << "Shader program loaded" << std::endl;
    }

    void Renderer::onRender()
    {     
        shader->setUniform("u_Projection", rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
        shader->setUniform("u_Model", getEntity()->getComponent<Transform>()->getModelMat());
        shader->setUniform("u_CamPos", getCore()->getCamera()->getTransform()->getPos());
        shader->setUniform("u_View", getCore()->getCamera()->getView());
        //shader->setUniform("camPos", glm::vec3());

        //PBR
        shader->setSampler("tex_albedo", albedo);
        shader->setSampler("tex_ao", ao);
        shader->setSampler("tex_metalness", metalness);
        shader->setSampler("tex_roughness", roughness);
        shader->setSampler("tex_normal", normal);
        shader->setSampler("tex_height", height);
        
        //add lights
        std::vector<rend::vec3> lightPos;
        lightPos.push_back(rend::vec3(-2.f, 0.0f, -3.0f));
        lightPos.push_back(rend::vec3(-1.f, 0.0f, -3.0f));
        lightPos.push_back(rend::vec3(0.0f, 0.0f, 0.0f));
        lightPos.push_back(rend::vec3(1.f, 0.0f, -3.0f));
        lightPos.push_back(rend::vec3(2.f, 0.0f, -3.0f));
        shader->setUniform("nooLights", lightPos.size());
        shader->setUniform("u_lightPos", lightPos[2]);
        shader->setUniform("lightColors", rend::vec3(150));


        shader->setMesh(model->mesh);
        shader->render();
    }

    void Renderer::setTexture(const char* path)
    {
        //texture = getCore()->cacheManager->loadResource<>(path);
        texture = getCore()->context->createTexture();
        int w = 0;
        int h = 0;
        int bpp = 0;
        //"../curuthers/redbricks_albedo.png"
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
    }
    void Renderer::setAlbedo(const char* path)
    {
        //texture = getCore()->cacheManager->loadResource<>(path);
        //albedo = getCore()->context->createTexture();
        int w = 0;
        int h = 0;
        int bpp = 0;
        //"../curuthers/redbricks_albedo.png"
        unsigned char* data = stbi_load(path, &w, &h, NULL, 3);
        if (!data)
        {
            std::string f = "Failed to open image @" + (std::string)path + "\n";
            throw Exception(f);
        }

        albedo->setSize(w, h);
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int r = y * w * 3 + x * 3;

                albedo->setPixel(x, y, rend::vec3(
                    data[r] / 255.0f,
                    data[r + 1] / 255.0f,
                    data[r + 2] / 255.0f));
            }
        }
        stbi_image_free(data);
    }
    void Renderer::setAO(const char* path)
    {
        //texture = getCore()->cacheManager->loadResource<>(path);
        //ao = getCore()->context->createTexture();
        int w = 0;
        int h = 0;
        int bpp = 0;
        //"../curuthers/redbricks_albedo.png"
        unsigned char* data = stbi_load(path, &w, &h, NULL, 3);
        if (!data)
        {
            std::string f = "Failed to open image @" + (std::string)path + "\n";
            throw Exception(f);
        }

        ao->setSize(w, h);
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int r = y * w * 3 + x * 3;

                ao->setPixel(x, y, rend::vec3(
                    data[r] / 255.0f,
                    data[r + 1] / 255.0f,
                    data[r + 2] / 255.0f));
            }
        }
        stbi_image_free(data);
    }
    void Renderer::setHeight(const char* path)
    {
        //texture = getCore()->cacheManager->loadResource<>(path);
        //height = getCore()->context->createTexture();
        int w = 0;
        int h = 0;
        int bpp = 0;
        //"../curuthers/redbricks_albedo.png"
        unsigned char* data = stbi_load(path, &w, &h, NULL, 3);
        if (!data)
        {
            std::string f = "Failed to open image @" + (std::string)path + "\n";
            throw Exception(f);;
        }

        height->setSize(w, h);
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int r = y * w * 3 + x * 3;

                height->setPixel(x, y, rend::vec3(
                    data[r] / 255.0f,
                    data[r + 1] / 255.0f,
                    data[r + 2] / 255.0f));
            }
        }
        stbi_image_free(data);
    }
    void Renderer::setNormal(const char* path)
    {
        //texture = getCore()->cacheManager->loadResource<>(path);
        //normal = getCore()->context->createTexture();
        int w = 0;
        int h = 0;
        int bpp = 0;
        //"../curuthers/redbricks_albedo.png"
        unsigned char* data = stbi_load(path, &w, &h, NULL, 3);
        if (!data)
        {
            std::string f = "Failed to open image @" + (std::string)path + "\n";
            throw Exception(f);
        }

        normal->setSize(w, h);
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int r = y * w * 3 + x * 3;

                normal->setPixel(x, y, rend::vec3(
                    data[r] / 255.0f,
                    data[r + 1] / 255.0f,
                    data[r + 2] / 255.0f));
            }
        }
        stbi_image_free(data);
    }
    void Renderer::setMetalness(const char* path)
    {
        //texture = getCore()->cacheManager->loadResource<>(path);
        //metalness = getCore()->context->createTexture();
        int w = 0;
        int h = 0;
        int bpp = 0;
        //"../curuthers/redbricks_albedo.png"
        unsigned char* data = stbi_load(path, &w, &h, NULL, 3);
        if (!data)
        {
            std::string f = "Failed to open image @" + (std::string)path + "\n";
            throw Exception(f);;
        }

        metalness->setSize(w, h);
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int r = y * w * 3 + x * 3;

                metalness->setPixel(x, y, rend::vec3(
                    data[r] / 255.0f,
                    data[r + 1] / 255.0f,
                    data[r + 2] / 255.0f));
            }
        }
        stbi_image_free(data);
    }
    void Renderer::setRoughnesse(const char* path)
    {
        //texture = getCore()->cacheManager->loadResource<>(path);
        //roughness = getCore()->context->createTexture();
        int w = 0;
        int h = 0;
        int bpp = 0;
        //"../curuthers/redbricks_albedo.png"
        unsigned char* data = stbi_load(path, &w, &h, NULL, 3);
        if (!data)
        {
            std::string f = "Failed to open image @" + (std::string)path + "\n";
            throw Exception(f);
        }

        roughness->setSize(w, h);
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int r = y * w * 3 + x * 3;

                roughness->setPixel(x, y, rend::vec3(
                    data[r] / 255.0f,
                    data[r + 1] / 255.0f,
                    data[r + 2] / 255.0f));
            }
        }
        stbi_image_free(data);
    }    

    void Renderer::setModel(std::shared_ptr<Model> _model)
    {//const char* path

        //std::ifstream file(path);
        //if (!file.is_open())
        //{
        //    std::string f = "Failed to open object @" + (std::string)path + "\n";
        //    throw Exception(f);
        //}
        //std::cout << "model loaded\n";
        //std::string content;
        //std::string line;//line declearded outside of the while to stp it from allocating and reallocating it
        //while (!file.eof())
        //{
        //    getline(file, line);
        //    content += line + '\n'; //getting each line strips the new line char
        //}
        //shape = getCore()->context->createMesh();
        //shape->parse(content);

        model = _model;
    }
}