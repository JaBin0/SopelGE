// System headers
#include <iostream>
// Own headers
#include <engine/assets/AssimpAssetsManager.h>
#include <engine/assets/Mesh.h>
#include <engine/assets/Model.h>
// External 
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Sopel {

// Defines
#define VERTEXPERFACE 3

AssimpAssetsManager::AssimpAssetsManager() 
    : IAssetsManager()
    , m_importer()
{
    

}

AssimpAssetsManager::~AssimpAssetsManager() 
{

}

AssetId AssimpAssetsManager::registerModel(const std::string path, ErrorCodes::value& errCode)
{   
    std::cout << "Loading model <" << path.data() << "> ... ";
    errCode = ErrorCodes::_NO_ERROR;
    // Check if model registered alraedy and find new free id if not.
    AssetId id = INVALID_ASSETID;
    AssetId index = 0;

    for(auto record : m_assetsMap) {
        if(INVALID_ASSETID == id && record.first != index) {
            id = index;
        }
        index++;

        if(0 == path.compare(record.second)) {
            // Both path are the same, return assign ID 
            id = record.first;
            std::cout << "ALREADY LOADED" << std::endl;
            return id;
        }
    }

    const aiScene *scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); 
    if(nullptr == scene) {
        std::cout << "FAILED" << std::endl << "Reading file failed. Possibly such file does not exist.";
        errCode = ErrorCodes::READING_ASSET_FILE_FAILED;
        return INVALID_ASSETID;
    }

    if(!scene->HasMeshes()) {
        std::cout << "FAILED" << std::endl << "Readed file does not contain any mesh.";
        errCode = ErrorCodes::READING_ASSET_FILE_FAILED;
        return INVALID_ASSETID;
    }

    aiMesh* originMesh = scene->mMeshes[0];
    Mesh mesh;
    mesh.vertices.reserve(originMesh->mNumFaces * VERTEXPERFACE);
    mesh.normals.reserve(originMesh->mNumFaces * VERTEXPERFACE);
    mesh.textureCoords.reserve(originMesh->mNumFaces * VERTEXPERFACE);

    for(uint16_t faceId = 0; faceId < originMesh->mNumFaces; ++faceId) 
    {
        aiFace face = originMesh->mFaces[faceId];
        for(uint16_t faceVertex = 0; faceVertex <  face.mNumIndices; ++faceVertex) {
            uint16_t vertexId = face.mIndices[faceVertex];
            aiVector3D vertexCoord = originMesh->mVertices[vertexId];
            mesh.vertices.push_back({vertexCoord.x, vertexCoord.y, vertexCoord.z});
            aiVector3D vertexNormal = originMesh->mNormals[vertexId];
            mesh.normals.push_back({vertexNormal.x, vertexNormal.y, vertexNormal.z});
            aiVector3D vertexTextCoord = originMesh->mTextureCoords[0][vertexId];
            mesh.textureCoords.push_back({vertexTextCoord.x, vertexTextCoord.y});
        }
    }

    Model model;
    model.mesh = mesh;
    m_models.insert({id, model});
    std::cout << "Success" << std::endl;
    return id;

    // for(uint16_t vertexId = 0; vertexId < originMesh->mNumVertices; ++vertexId) {
    //     // mesh.vertices.push_back({cube->mVertices[vertexId].x, cube->mVertices[vertexId].y, cube->mVertices[vertexId].z});
    //     // mesh.normals.push_back({cube->mNormals[vertexId].x, cube->mNormals[vertexId].y, cube->mNormals[vertexId].z});
    //     // mesh.textureCoords.push_back({cube->mTextureCoords[0][vertexId].x, cube->mTextureCoords[0][vertexId].y});
    //     std::cout << "[" << originMesh->mVertices[vertexId].x << ", " << originMesh->mVertices[vertexId].y << ", " << originMesh->mVertices[vertexId].z << "]      " ;
    //     std::cout << "[" << originMesh->mNormals[vertexId].x << ", " << originMesh->mNormals[vertexId].y << ", " << originMesh->mNormals[vertexId].z << "]      " ;
    //     std::cout << "[" << originMesh->mTextureCoords[0][vertexId].x << ", " << originMesh->mTextureCoords[0][vertexId].y << ", " << originMesh->mTextureCoords[0][vertexId].z << "]"  << std::endl;
    // }
}



};