#include "myMesh.h"

myMesh::meshEntry::meshEntry()
{
	mVB = INVALID_OGL_VALUE;
	mIB = INVALID_OGL_VALUE;
	mNumIndices = 0;
	mMaterialIndex = INVALID_MATERIAL;
};

myMesh::meshEntry::~meshEntry()
{
	if (mVB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &mVB);
	}

	if (mIB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &mIB);
	}
}

void myMesh::meshEntry::Init(const std::vector<Vertex>& Vertices,
	const std::vector<unsigned int>& Indices)
{
	mNumIndices = Indices.size();

	glGenBuffers(1, &mVB);
	glBindBuffer(GL_ARRAY_BUFFER, mVB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mIB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* mNumIndices, &Indices[0], GL_STATIC_DRAW);
}

myMesh::myMesh()
{
}


myMesh::~myMesh()
{
	clear();
}


void myMesh::clear()
{
	for (unsigned int i = 0; i < mTextures.size(); i++) {
		SAFE_DELETE(mTextures[i]);
	}
}


bool myMesh::loadMesh(const std::string& path)
{
	// Release the previously loaded mesh (if it exists)
	clear();

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene) {
		Ret = initFromScene(pScene, path);
	}
	else {
		printf("> Errore analisi '%s': '%s'.\n", path.c_str(), Importer.GetErrorString());
	}

	return Ret;
}

bool myMesh::initFromScene(const aiScene* pScene, const std::string& path)
{
	mEntries.resize(pScene->mNumMeshes);
	mTextures.resize(pScene->mNumMaterials);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < mEntries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		initMesh(i, paiMesh);
	}

	return initMaterials(pScene, path);
}

void myMesh::initMesh(unsigned int Index, const aiMesh* paiMesh)
{
	mEntries[Index].mMaterialIndex = paiMesh->mMaterialIndex;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(Vector3f(pPos->x, pPos->y, pPos->z),
			Vector2f(pTexCoord->x, pTexCoord->y),
			Vector3f(pNormal->x, pNormal->y, pNormal->z));

		Vertices.push_back(v);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	mEntries[Index].Init(Vertices, Indices);
}

bool myMesh::initMaterials(const aiScene* pScene, const std::string& path)
{
	// Extract the directory part from the file name
	std::string::size_type SlashIndex = path.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos) {
		Dir = ".";
	}
	else if (SlashIndex == 0) {
		Dir = "/";
	}
	else {
		Dir = path.substr(0, SlashIndex);
	}

	bool Ret = true;

	// Initialize the materials
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		mTextures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string FullPath = Dir + "/" + Path.data;
				mTextures[i] = new myTexture(GL_TEXTURE_2D, FullPath.c_str());

				if (!mTextures[i]->loadMesh()) {
					printf("> Errore caricamento texture '%s'.\n", FullPath.c_str());
					delete mTextures[i];
					mTextures[i] = NULL;
					Ret = false;
				}
				else {
					printf("Texture caricate '%s'.\n", FullPath.c_str());
				}
			}
		}

		// Load a white texture in case the model does not include its own texture
		if (!mTextures[i]) {
			mTextures[i] = new myTexture(GL_TEXTURE_2D, "./white.png");

			Ret = mTextures[i]->loadMesh();
		}
	}

	return Ret;
}

void myMesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < mEntries.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mEntries[i].mVB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEntries[i].mIB);

		const unsigned int MaterialIndex = mEntries[i].mMaterialIndex;

		if (MaterialIndex < mTextures.size() && mTextures[MaterialIndex]) {
			mTextures[MaterialIndex]->bind(GL_TEXTURE0);
		}

		glDrawElements(GL_TRIANGLES, mEntries[i].mNumIndices, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
