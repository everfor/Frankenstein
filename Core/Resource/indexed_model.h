#pragma once

class Mesh;

class IndexedModel
{
	public:
		IndexedModel() {};
		virtual ~IndexedModel() {};
		virtual void loadToMesh(Mesh *mesh) {};
};

