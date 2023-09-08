#pragma once
#include "Engine/YorkieEngine.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Texture/Texture.h"
#include "Graphics/Mesh/Mesh.h"
#include "Components/BaseComponent.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>

struct YorkieAPI MeshComponent : public BaseComponent
{
public:
    MeshComponent(const char* path);
    void Draw();
    std::vector<Mesh>& GetMeshes() { return meshes; };
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory);
};