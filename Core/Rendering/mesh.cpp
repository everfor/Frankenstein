#include "mesh.h"

Mesh::Mesh() :
		size(0)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo[INDEX_VB]);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
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
	glGenBuffers(NUM_BUFFERS, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(POSITION_VB);
	glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for textures
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(textures[0]), &textures[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(TEXCOORD_VB);
	glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(NORMAL_VB);
	glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_index * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	size = num_index;
}

void Mesh::addVertices(std::vector<Vertex>& vertices, int num_vert, std::vector<unsigned short>& indices, int num_index)
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
	glGenBuffers(NUM_BUFFERS, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(POSITION_VB);
	glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for textures
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(textures[0]), &textures[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(TEXCOORD_VB);
	glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// VBO for normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	// Bind VBO
	glEnableVertexAttribArray(NORMAL_VB);
	glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_index * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	size = num_index;
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, size);
}