#include <map>
#include <vector>
#include <GL/glew.h>
#include <Importer.hpp>      // C++ importer interface
#include <scene.h>           // Output data structure
#include <postprocess.h>     // Post processing flags
#include <assert.h>

#include "myMath.h"
#include "myTexture.h"
#include "myDefUtil.h"

#ifndef _myMesh
#define _myMesh 1

class myMesh
{
public:
	myMesh();

	~myMesh();

	bool loadMesh(const std::string& filename);

	void Render();

private:
	bool initFromScene(const aiScene* pScene, const std::string& path);
	void initMesh(unsigned int index, const aiMesh* paiMesh);
	bool initMaterials(const aiScene* pScene, const std::string& path);
	void clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	struct meshEntry {
		meshEntry();

		~meshEntry();

		void Init(const std::vector<Vertex>& Vertices,
			const std::vector<unsigned int>& Indices);

		GLuint mVB;
		GLuint mIB;
		unsigned int mNumIndices;
		unsigned int mMaterialIndex;
	};

	std::vector<meshEntry> mEntries;
	std::vector<myTexture*> mTextures;
};

#endif // !_myMesh
