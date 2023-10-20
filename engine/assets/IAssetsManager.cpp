// Own headers
#include <engine/assets/IAssetsManager.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Image/stb_image.h>

#include <iostream>

namespace Sopel {

std::tuple<AssetID, Model*> IAssetsManager::loadModelAsset(const std::string path) {

    // Check if the file is already loaded and if type match
    for(std::pair<const AssetID, std::pair<std::string, AssetType>>& entry : _assets) {
        if(entry.second.first == path) {
            if(entry.second.second != AssetType::Model) {
                return {INVALID_ASSET_ID, nullptr};
            }
            else {
                Model* model = &_models.at(entry.first);
                return {entry.first, model};
            }
        } 
    }

    // Model is not loaded within engine find free asset;
    AssetID newId = INVALID_ASSET_ID;
    while(++newId != INVALID_ASSET_ID) {
        if(_assets.count(newId) == 0) {
            break;
        }
    }

    // All ids used no more asset can be registered 
    if(newId == INVALID_ASSET_ID ) {
        std::cout << "Failed" << std::endl
                  << "ERROR::IAssetManager" << std::endl
                  << "Asset storage is full, no free asset Id. Remove unused to free asset space" << std::endl;
        return {INVALID_ASSET_ID, nullptr};
    }
    Model* model = nullptr;
    Assimp::Importer m_importer;
    const aiScene *scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(scene == nullptr || scene->mNumMeshes == 0) {
        std::cout << "Failed" << std::endl
                  << "ERROR::IAssetManager" << std::endl
                  << "Scene could not be read properly or Scene does not contain at least one Mesh" << std::endl;
        return {INVALID_ASSET_ID, nullptr};
    }

    _assets.insert({newId, {path, AssetType::Model}});
    _models.insert({newId, {}});
    model = &_models.at(newId);

    aiMesh* meshAi = scene->mMeshes[0];
    Mesh& mesh = model->mesh;
    mesh.vertices.reserve(meshAi->mNumVertices);
    

    for (uint32 id = 0; id < meshAi->mNumVertices; ++id) {
        aiVector3D vertex = meshAi->mVertices[id];
        aiVector3D normals = meshAi->mNormals[id];
        mesh.vertices.insert(mesh.vertices.end(), {vertex.x, vertex.y, vertex.z});
        mesh.vertices.insert(mesh.vertices.end(), {normals.x, normals.y, normals.z});
    }
    
    return {newId, model};
}

std::tuple<AssetID, std::shared_ptr<Image>> IAssetsManager::loadImageAsset(const std::string path) {
    
    // Check if the file is already loaded and if type match
    for(std::pair<const AssetID, std::pair<std::string, AssetType>>& entry : _assets) {
        if(entry.second.first == path) {
            if(entry.second.second != AssetType::Image) {
                return {INVALID_ASSET_ID, nullptr};
            }
            else {
                // Model* model = &_models.at(entry.first);
                // return {entry.first, model};
            }
        } 
    }

    // Model is not loaded within engine find free asset;
    AssetID newId = INVALID_ASSET_ID;
    while(++newId != INVALID_ASSET_ID) {
        if(_assets.count(newId) == 0) {
            break;
        }
    }

    // All ids used no more asset can be registered 
    if(newId == INVALID_ASSET_ID ) {
        std::cout << "Failed" << std::endl
                  << "ERROR::IAssetManager" << std::endl
                  << "Asset storage is full, no free asset Id. Remove unused to free asset space" << std::endl;
        return {INVALID_ASSET_ID, nullptr};
    }
    
    stbi_set_flip_vertically_on_load(true);  
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.data(), &width, &height, &nrChannels, 0);
    if(data == nullptr) {
        return {INVALID_ASSET_ID, nullptr};
    }

    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;

    std::shared_ptr<Image> image = std::make_shared<Image>(newId, width, height, path, nrChannels);
    image->data.reserve((width * height * nrChannels));

    // std::cout << "Data: " << std::endl;
    for (auto i=0; i < (width * height * nrChannels); i++) {
        image->data.emplace_back(data[i]);
    }
    // std::cout << std::endl;

    // std::cout << "Test: " << (uint16_t)image->data[0] << ", ";
    // std::memcmp(data, image->data.data(), (width * height * nrChannels));

    

    _assets.insert({newId, {path, AssetType::Image}});
    // _images.insert({newId, data});
    return {newId, image};
}


};
// namespace SopelGE {
// const Model IAssetsManager::getModel(const AssetId id)
// {
//     if(m_models.count(id) != 0) {
//         return m_models.at(id);
//     }

//     // Id is not assing to any model. Return empty object
//     return Model();
// }

// const Texture& IAssetsManager::getTexture(const AssetId id)
// {
//     if(m_textures.count(id) != 0) {
//         return m_textures.at(id);
//     }
//     return Texture();
// }

// };

