#include "Mesh.h"
#include "Util.h"
#include "mathutil.h"
#include "Context.h"
#include "Buffer.h"
#include "Exception.h"
#include <iostream>
namespace rend
{

    struct Face
    {
      vec3 pa;
      vec3 pb;
      vec3 pc;

      vec2 tca;
      vec2 tcb;
      vec2 tcc;

      vec3 na;
      vec3 nb;
      vec3 nc;

      vec2 lmca;
      vec2 lmcb;
      vec2 lmcc;
    };

    void Mesh::setBuffer(const std::string& name, const std::shared_ptr<Buffer>& buffer)
    {
      for(std::vector<std::shared_ptr<BufferData> >::iterator it =
        buffers.begin(); it != buffers.end(); it++)
      {
        if((*it)->name == name)
        {
          (*it)->buffer = buffer;

          return;
        }
      }

      std::shared_ptr<BufferData> bd = std::make_shared<BufferData>();
      bd->name = name;
      bd->buffer = buffer;
      buffers.push_back(bd);
    }

    void Mesh::setTexture(const std::string& name, const std::shared_ptr<TextureAdapter>& texture)
    {
      for(std::vector<std::shared_ptr<TextureData> >::iterator it =
        textures.begin(); it != textures.end(); it++)
      {
        if((*it)->name == name)
        {
          (*it)->texture = texture;

          return;
        }
      }

      std::shared_ptr<TextureData> td = std::make_shared<TextureData>();
      td->name = name;
      td->texture = texture;
      textures.push_back(td);
    }

    void Mesh::parse(const std::string& data)
    {
      std::string currentLine;

      try
      {
        safeParse(data, currentLine);
      }
      catch(std::exception& e)
      {
        throw Exception("Failed to parse model data [" + currentLine + "]");
      }
    }

    void Mesh::safeParse(const std::string& data, std::string& currentLine)
    {
        std::vector<std::string> lines;
        Util::splitStringLineEnding(data, lines);

        std::vector<vec3> positions;
        std::vector<vec2> tcs;
        std::vector<vec3> normals;
        std::vector<vec2> lmcs;
        std::vector<Face> faces;
        std::vector<vec3> tangents;
        std::vector<vec3> bitangents;

        for (std::vector<std::string>::iterator lit = lines.begin();
            lit != lines.end(); lit++)
        {
            currentLine = *lit;
            if (lit->length() < 1) continue;
            //std::cout << "Line [" << *lit << "]" << std::endl;

            std::vector<std::string> tokens;
            Util::splitStringWhitespace(*lit, tokens);
            if (tokens.size() < 1) continue;

            if (tokens.at(0) == "v")
            {
                vec3 p(atof(tokens.at(1).c_str()),
                    atof(tokens.at(2).c_str()),
                    atof(tokens.at(3).c_str()));

                positions.push_back(p);
            }
            else if (tokens.at(0) == "vt")
            {
                vec2 tc(atof(tokens.at(1).c_str()),
                    atof(tokens.at(2).c_str()));

                tcs.push_back(tc);
            }
            else if (tokens.at(0) == "vn")
            {
                vec3 n(atof(tokens.at(1).c_str()),
                    atof(tokens.at(2).c_str()),
                    atof(tokens.at(3).c_str()));

                normals.push_back(n);
            }
            else if (tokens.at(0) == "f")
            {
                if (tokens.size() < 4) continue;

                Face f;
                std::vector<std::string> sub;
                Util::splitString(tokens.at(1), '/', sub);
                if (sub.size() >= 1) f.pa = positions.at(atoi(sub.at(0).c_str()) - 1);
                if (sub.size() >= 2) f.tca = tcs.at(atoi(sub.at(1).c_str()) - 1);
                if (sub.size() >= 3) f.na = normals.at(atoi(sub.at(2).c_str()) - 1);
                if (sub.size() >= 4) f.lmca = lmcs.at(atoi(sub.at(3).c_str()) - 1);

                Util::splitString(tokens.at(2), '/', sub);
                if (sub.size() >= 1) f.pb = positions.at(atoi(sub.at(0).c_str()) - 1);
                if (sub.size() >= 2) f.tcb = tcs.at(atoi(sub.at(1).c_str()) - 1);
                if (sub.size() >= 3) f.nb = normals.at(atoi(sub.at(2).c_str()) - 1);
                if (sub.size() >= 4) f.lmcb = lmcs.at(atoi(sub.at(3).c_str()) - 1);

                Util::splitString(tokens.at(3), '/', sub);
                if (sub.size() >= 1) f.pc = positions.at(atoi(sub.at(0).c_str()) - 1);
                if (sub.size() >= 2) f.tcc = tcs.at(atoi(sub.at(1).c_str()) - 1);
                if (sub.size() >= 3) f.nc = normals.at(atoi(sub.at(2).c_str()) - 1);
                if (sub.size() >= 4) f.lmcc = lmcs.at(atoi(sub.at(3).c_str()) - 1);

                faces.push_back(f);
                if (tokens.size() < 5) continue;

                Face fq;
                fq.pa = f.pc;
                fq.tca = f.tcc;
                fq.na = f.nc;
                fq.lmca = f.lmcc;

                Util::splitString(tokens.at(4), '/', sub);
                if (sub.size() >= 1) fq.pb = positions.at(atoi(sub.at(0).c_str()) - 1);
                if (sub.size() >= 2) fq.tcb = tcs.at(atoi(sub.at(1).c_str()) - 1);
                if (sub.size() >= 3) fq.nb = normals.at(atoi(sub.at(2).c_str()) - 1);
                if (sub.size() >= 4) fq.lmcb = lmcs.at(atoi(sub.at(3).c_str()) - 1);

                fq.pc = f.pa;
                fq.tcc = f.tca;
                fq.nc = f.na;
                fq.lmcc = f.lmca;

                faces.push_back(fq);
            }
        }
        std::vector<glm::vec3> vertices;
        if (positions.size() > 0)
        {
            std::shared_ptr<Buffer> b = context->createBuffer();

            for (std::vector<Face>::iterator fit = faces.begin();
                fit != faces.end(); fit++)
            {
                b->add(fit->pa);
                b->add(fit->pb);
                b->add(fit->pc);
                vertices.push_back(fit->pa);
                vertices.push_back(fit->pb);
                vertices.push_back(fit->pc);
            }
            setBuffer("a_Position", b);
        }
        
        std::vector<glm::vec2> uvs;
        if (tcs.size() > 0)
        {
            std::shared_ptr<Buffer> b = context->createBuffer();

            for (std::vector<Face>::iterator fit = faces.begin();//REnd is broken hence why this thing is here
                fit != faces.end(); fit++)
            {
                glm::vec2 workPlease;
                workPlease = fit->tca;
                b->add(&workPlease);
                workPlease = fit->tcb;
                b->add(&workPlease);
                workPlease = fit->tcc;
                b->add(&workPlease);
                uvs.push_back(fit->tca);
                uvs.push_back(fit->tcb);
                uvs.push_back(fit->tcc);
            }

            setBuffer("a_TexCoord", b);
        }

        std::vector<glm::vec3> DefinatlyNOTnormals;
        if (normals.size() > 0)
        {
            std::shared_ptr<Buffer> b = context->createBuffer();

            for (std::vector<Face>::iterator fit = faces.begin();
                fit != faces.end(); fit++)
            {
                b->add(fit->na);
                b->add(fit->nb);
                b->add(fit->nc);
                DefinatlyNOTnormals.push_back(fit->na);
                DefinatlyNOTnormals.push_back(fit->nb);
                DefinatlyNOTnormals.push_back(fit->nc);
            }

            setBuffer("a_Normal", b);//normal
        }

        if (lmcs.size() > 0)
        {
            std::shared_ptr<Buffer> b = context->createBuffer();

            for (std::vector<Face>::iterator fit = faces.begin();
                fit != faces.end(); fit++)
            {
                b->add(fit->lmca);
                b->add(fit->lmcb);
                b->add(fit->lmcc);
            }

            setBuffer("a_LightMapCoord", b);
        }

        //for each face calulate the tangent and the bitangent
        //wtf is uvs??
        /*for (int i = 0; i < faces.size; i++)
        {

        }*/
        computeTangentBasis(vertices, uvs, DefinatlyNOTnormals, tangents, bitangents);
        if (tangents.size() > 0)
        {
            std::shared_ptr<Buffer> b = context->createBuffer();

            for (int t = 0; t < tangents.size(); t++)
            {
                //Gram-Schmidt orthogonalize
                tangents[t] = glm::normalize((tangents[t] - DefinatlyNOTnormals[t] * glm::dot(DefinatlyNOTnormals[t], tangents[t])));
                //Right handed TBN space ?
                

                b->add(tangents[t]);
            }
            bool rigthHanded = glm::dot(glm::cross(tangents[0], bitangents[0]), DefinatlyNOTnormals[0]) >= 0;
            //bitangents[] = crossProduct(normal, tangent);
            if (!rigthHanded)
            {
                for (int i = 0; i< bitangents.size(); i++)
                {
                    bitangents[i] = bitangents[i] * -1.0f;
                    std::cout << "FLIP ME\n"; //binormal.multiply(-1);
                }
                
            }
            setBuffer("a_Tangent", b);
        }
        if (bitangents.size() > 0)
        {
            std::shared_ptr<Buffer> b = context->createBuffer();

            for (int t = 0; t < bitangents.size(); t++)
            {
                
                b->add(bitangents[t]);
            }
            setBuffer("a_BTangent", b);
        }

    }

    void Mesh::computeTangentBasis(
        // inputs
        std::vector<glm::vec3>& vertices,
        std::vector<glm::vec2>& uvs,
        std::vector<glm::vec3>& normals,
        // outputs
        std::vector<glm::vec3>& tangents,
        std::vector<glm::vec3>& bitangents
    ) {
        for (size_t i = 0; i < vertices.size(); i = i+3) //steps in 3 for each face
        {
            // Shortcuts for vertices
            glm::vec3& v0 = vertices[i + 0];
            glm::vec3& v1 = vertices[i + 1];
            glm::vec3& v2 = vertices[i + 2];

            // Shortcuts for UVs
            glm::vec2& uv0 = uvs[i + 0];
            glm::vec2& uv1 = uvs[i + 1];
            glm::vec2& uv2 = uvs[i + 2];

            // Edges of the triangle : position delta
            glm::vec3 deltaPos1 = v1 - v0;
            glm::vec3 deltaPos2 = v2 - v0;

            // UV delta
            glm::vec2 deltaUV1 = uv1 - uv0;
            glm::vec2 deltaUV2 = uv2 - uv0;

            //compute tan and bitan
            float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
            glm::vec3 tangent;// = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            glm::vec3 bitangent;// = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
            tangent.x = r * (deltaUV2.y * deltaPos1.x - deltaUV1.y * deltaPos2.x);
            tangent.y = r * (deltaUV2.y * deltaPos1.y - deltaUV1.y * deltaPos2.y);
            tangent.z = r * (deltaUV2.y * deltaPos1.z - deltaUV1.y * deltaPos2.z);

            bitangent.x = r * (-deltaUV2.x * deltaPos1.x + deltaUV1.x * deltaPos2.x);
            bitangent.y = r * (-deltaUV2.x * deltaPos1.y + deltaUV1.x * deltaPos2.y);
            bitangent.z = r * (-deltaUV2.x * deltaPos1.z + deltaUV1.x * deltaPos2.z);

            

            // Set the same tangent for all three vertices of the triangle.
            // They will be merged later, in vboindexer.cpp
            tangents.push_back(tangent);
            tangents.push_back(tangent);
            tangents.push_back(tangent);

            // Same thing for bitangents
            bitangents.push_back(bitangent);
            bitangents.push_back(bitangent);
            bitangents.push_back(bitangent);
        }
    }

}
