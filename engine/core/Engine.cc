// Own headers
#include <engine/core/Engine.h>

// System haeaders
#include <string>

// External 
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Sopel {
// Static variables
const float Engine::version = 0.001f;

Engine::~Engine() {

}
};

Sopel::Engine::Engine()
{
    std::cout << "Engine constructor" << std::endl;
    std::string path = "F://C++//Game//assets//WalterMelon//defaultCube.fbx";
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); 
    if(nullptr == scene) {
        std::cout << "No such file exist" << std::endl;
        return;
    }
    if(scene->HasMeshes()) {
        auto nMeshes = scene->mNumMeshes;
        std::cout << "Scane has some meshes data: " << nMeshes << std::endl;
        aiMesh* cube = scene->mMeshes[0];
        auto nFaces = cube->mNumFaces;
        std::cout << "Mesh, presumebly cube has " << nFaces << " faces" << std::endl;
        auto nVertices = cube->mNumVertices;
        std::cout << "Vertices: " << nVertices << std::endl;

        for(uint16_t i = 0; i < nVertices; ++i) {
            std::cout << "[" << cube->mVertices[i].x << ", " << cube->mVertices[i].y << ", " << cube->mVertices[i].z << "]" << std::endl;
        }

        for(uint16_t i = 0; i < cube->mNumFaces; ++i) {
            aiFace face = cube->mFaces[i];
            std::cout << "F [" << face.mIndices[0] << ", " << face.mIndices[1] << ", " << face.mIndices[2] << "]" << std::endl;
        }

        
       // std::cout << "Root node data: " << ->mName.data << std::endl;

        aiNode* pCubeNode = scene->mRootNode->mChildren[0];
        aiMetadata* cubeMetaData = pCubeNode->mMetaData;
        for(auto i = 0; i < cubeMetaData->mNumProperties; i++){
            auto key = cubeMetaData->mKeys[i];
            std::cout << "Cube prop key: " <<  key.data << std::endl;
            if(std::strcmp(key.data, "Bartek") == 0) {
                std::cout << "Value: " << static_cast<aiString*>(cubeMetaData->mValues[i].mData)->data << std::endl;
            }
        }
        
        auto metaData = scene->mMetaData[0];

        for(auto i = 0; i < metaData.mNumProperties; i++){
            auto key = metaData.mKeys[i];

            std::cout << "Prop key: " <<  key.data << std::endl;
        }
        // 
        // 
       
    }
}


    