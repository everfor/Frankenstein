#include "obj_model.h"
#include "mesh.h"
#include "utils.h"
#include "exceptions.h"
#include "vertex.h"

#include <fstream>
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/vector3.h>

ObjModel::ObjModel(const std::string& fileName) :
		hasTextureCoord(true), hasNormalCoord(true)
{
	// Redo obj laoding using assimp
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (scene)
	{
		// Use the first mesh for now
		aiVector3D zero(0.0f, 0.0f, 0.f);
		const aiMesh* mesh = scene->mMeshes[0];

		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			const aiVector3D *pos = &(mesh->mVertices[i]);
			const aiVector3D *normal = mesh->HasNormals() ? &(mesh->mNormals[i]) : &zero;
			const aiVector3D *tex = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zero;
			const aiVector3D *tangent = mesh->HasTangentsAndBitangents() ? &(mesh->mTangents[i]) : &zero;
			const aiVector3D *bitangent = mesh->HasTangentsAndBitangents() ? &(mesh->mBitangents[i]) : &zero;

			vertices.push_back(Vertex(glm::vec3(pos->x, pos->y, pos->z),
										glm::vec2(tex->x, tex->y),
										glm::vec3(normal->x, normal->y, normal->z),
										glm::vec3(tangent->x, tangent->y, tangent->z),
										glm::vec3(bitangent->x, bitangent->y, bitangent->z)));
		}

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace *face = &(mesh->mFaces[i]);
			assert(face->mNumIndices == 3);

			indices.push_back(face->mIndices[0]);
			indices.push_back(face->mIndices[1]);
			indices.push_back(face->mIndices[2]);
		}
	}
}

ObjModel::~ObjModel()
{
}

void ObjModel::loadToMesh(Mesh *mesh)
{
	mesh->addVertices(vertices, vertices.size(), indices, indices.size());
}