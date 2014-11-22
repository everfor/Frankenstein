#include "mesh.h"
#include "resource_manager.h"

Mesh::Mesh(const std::string& init_fileName) : fileName(init_fileName)
{
	resource = MeshResource::_get_resource(fileName);

	if (fileName != "")
	{
		ResourceManager::LoadMesh(fileName, *this);
	}
}

Mesh::~Mesh()
{
	MeshResource::_remove_resource(fileName);
}

void Mesh::addVertices(Vertex *vertices, int num_vert, unsigned short *indices, int num_index)
{
	// Construct glm::vec3 arrays
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	positions.reserve(num_vert);
	textures.reserve(num_vert);
	normals.reserve(num_vert);

	for (int i = 0; i < num_vert; i++)
	{
		positions.push_back(vertices[i].getPose());
		textures.push_back(vertices[i].getTex());
		normals.push_back(vertices[i].getNormal());
	}

	// Initialize VBO for position
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::POSITION_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(MeshResource::POSITION_VB);
	glVertexAttribPointer(MeshResource::POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for textures
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::TEXCOORD_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(textures[0]), &textures[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(MeshResource::TEXCOORD_VB);
	glVertexAttribPointer(MeshResource::TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for normals
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::NORMAL_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(MeshResource::NORMAL_VB);
	glVertexAttribPointer(MeshResource::NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getVBO(MeshResource::INDEX_VB));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_index * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	resource->setSize(num_index);
}

void Mesh::addVertices(std::vector<Vertex>& vertices, int num_vert, std::vector<unsigned short>& indices, int num_index)
{
	// Construct glm::vec3 arrays
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec2> normalcoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	positions.reserve(num_vert);
	textures.reserve(num_vert);
	normalcoords.reserve(num_vert);
	normals.reserve(num_vert);
	tangents.reserve(num_vert);
	bitangents.reserve(num_vert);

	for (int i = 0; i < num_vert; i++)
	{
		positions.push_back(vertices[i].getPose());
		textures.push_back(vertices[i].getTex());
		normalcoords.push_back(vertices[i].getNormalCoord());
		normals.push_back(vertices[i].getNormal());
		tangents.push_back(vertices[i].getTangent());
		bitangents.push_back(vertices[i].getBiTangent());
	}

	// Initialize VBO for position
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::POSITION_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(MeshResource::POSITION_VB);
	glVertexAttribPointer(MeshResource::POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for textures
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::TEXCOORD_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(textures[0]), &textures[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(MeshResource::TEXCOORD_VB);
	glVertexAttribPointer(MeshResource::TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for normalCoords
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::NORMALCOORD_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(normalcoords[0]), &normalcoords[0], GL_STATIC_DRAW);
	// Bind VBO
	glDisableVertexAttribArray(MeshResource::NORMALCOORD_VB);
	glVertexAttribPointer(MeshResource::NORMALCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for normals
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::NORMAL_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(MeshResource::NORMAL_VB);
	glVertexAttribPointer(MeshResource::NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for tangents
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::TANGENT_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(tangents[0]), &tangents[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(MeshResource::TANGENT_VB);
	glVertexAttribPointer(MeshResource::TANGENT_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for bitangents
	glBindBuffer(GL_ARRAY_BUFFER, resource->getVBO(MeshResource::BITANGENT_VB));
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(bitangents[0]), &bitangents[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(MeshResource::BITANGENT_VB);
	glVertexAttribPointer(MeshResource::BITANGENT_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->getVBO(MeshResource::INDEX_VB));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_index * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	resource->setSize(num_index);
}

void Mesh::draw()
{
	glBindVertexArray(resource->getVAO());
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, resource->getSize(), GL_UNSIGNED_SHORT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, size);
}