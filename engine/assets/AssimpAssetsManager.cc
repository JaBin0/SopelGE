// // System headers
// #include <iostream>
// // Own headers
// #include <engine/assets/AssimpAssetsManager.h>
// #include <engine/assets/Mesh.h>
// #include <engine/assets/SpModel.h>
// // External 
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>
// #define STB_IMAGE_IMPLEMENTATION
// #include <Image/stb_image.h>

// namespace SopelGE {

// // Defines
// #define VERTEXPERFACE 3

// AssimpAssetsManager::AssimpAssetsManager() 
//     : IAssetsManager()
//     , m_importer()
// {
//     stbi_set_flip_vertically_on_load(true);

// }

// AssimpAssetsManager::~AssimpAssetsManager() 
// {

// }

// AssetId AssimpAssetsManager::registerModel(const std::string path, ErrorCodes::value& errCode)
// {   
//     std::cout << "Loading model <" << path.data() << "> ... ";
//     errCode = ErrorCodes::_NO_ERROR;
//     // Check if model registered alraedy and find new free id if not.
//     AssetId id = 0;
//     bool newIdFound = false;

//     for(auto asset : m_assetsMap) {
//         if(0 == path.compare(asset.second)) {
//                 // Both path are the same, return assign ID 
//                 std::cout << "ALREADY LOADED" << std::endl;
//                 return asset.first;
//         }
//         if(!newIdFound) {

//             if(asset.first != id) {
//                 newIdFound = true;
//             }
//             else {
//                 ++id;
//             }
//         }
//     }

//     m_assetsMap.insert({id, path});

//     const aiScene *scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace); 
//     if(nullptr == scene) {
//         std::cout << "FAILED" << std::endl << "Reading file failed. Possibly such file does not exist.";
//         errCode = ErrorCodes::READING_ASSET_FILE_FAILED;
//         return INVALID_ASSETID;
//     }

//     if(!scene->HasMeshes()) {
//         std::cout << "FAILED" << std::endl << "Readed file does not contain any mesh.";
//         errCode = ErrorCodes::READING_ASSET_FILE_FAILED;
//         return INVALID_ASSETID;
//     }

//     aiMesh* originMesh = scene->mMeshes[0];
//     Mesh mesh;
//     mesh.vertices.reserve(originMesh->mNumFaces * VERTEXPERFACE);
//     mesh.normals.reserve(originMesh->mNumFaces * VERTEXPERFACE);
//     mesh.textureCoords.reserve(originMesh->mNumFaces * VERTEXPERFACE);
//     mesh.tangents.reserve(originMesh->mNumFaces * VERTEXPERFACE);
//     mesh.verticesNumber = originMesh->mNumFaces * VERTEXPERFACE;
    
//     mesh.vertexSize = 11;
//     for(uint16_t faceId = 0; faceId < originMesh->mNumFaces; ++faceId) 
//     {
//         aiFace face = originMesh->mFaces[faceId];
//         for(uint16_t faceVertex = 0; faceVertex <  face.mNumIndices; ++faceVertex) {
//             uint16_t vertexId = face.mIndices[faceVertex];
//             aiVector3D vertexCoord = originMesh->mVertices[vertexId];
//             mesh.vertices.push_back({vertexCoord.x, vertexCoord.y, vertexCoord.z});
//             aiVector3D vertexNormal = originMesh->mNormals[vertexId];
//             mesh.normals.push_back({vertexNormal.x, vertexNormal.y, vertexNormal.z});
//             aiVector3D vertexTextCoord = originMesh->mTextureCoords[0][vertexId];
//             mesh.textureCoords.push_back({vertexTextCoord.x, vertexTextCoord.y});
//             aiVector3D tangent = originMesh->mTangents[vertexId];
//             mesh.tangents.push_back({tangent.x, tangent.y, tangent.z});
//         }
//     }
 
//     Model model;
//     model.mesh = mesh;
//     m_models.insert({id, model});
//     std::cout << "Success id[" << id << "]" << std::endl;
//     return id;

//     // for(uint16_t vertexId = 0; vertexId < originMesh->mNumVertices; ++vertexId) {
//     //     // mesh.vertices.push_back({cube->mVertices[vertexId].x, cube->mVertices[vertexId].y, cube->mVertices[vertexId].z});
//     //     // mesh.normals.push_back({cube->mNormals[vertexId].x, cube->mNormals[vertexId].y, cube->mNormals[vertexId].z});
//     //     // mesh.textureCoords.push_back({cube->mTextureCoords[0][vertexId].x, cube->mTextureCoords[0][vertexId].y});
//     //     std::cout << "[" << originMesh->mVertices[vertexId].x << ", " << originMesh->mVertices[vertexId].y << ", " << originMesh->mVertices[vertexId].z << "]      " ;
//     //     std::cout << "[" << originMesh->mNormals[vertexId].x << ", " << originMesh->mNormals[vertexId].y << ", " << originMesh->mNormals[vertexId].z << "]      " ;
//     //     std::cout << "[" << originMesh->mTextureCoords[0][vertexId].x << ", " << originMesh->mTextureCoords[0][vertexId].y << ", " << originMesh->mTextureCoords[0][vertexId].z << "]"  << std::endl;
//     // }
// }

// TextureId AssimpAssetsManager::registerTexture(const std::string textruePath, ErrorCodes::value& errCode) 
// {
//     errCode = ErrorCodes::_NO_ERROR;
//     AssetId id = 0;
//     bool newIdFound = false;

//     for(auto asset : m_assetsMap) {
//         if(0 == textruePath.compare(asset.second)) {
//                 // Both path are the same, return assign ID 
//                 std::cout << "ALREADY LOADED" << std::endl;
//                 return asset.first;
//         }
//         if(!newIdFound) 
//         {
//             if(asset.first != id) {
//                 newIdFound = true;
//             }
//             else {
//                 ++id;
//             }
//         }
//     }

//     int width, height, nrChannels;
//     unsigned char *data = stbi_load(textruePath.data(), &width, &height, &nrChannels, 0);
//     if(nullptr == data) {
//         errCode = ErrorCodes::TEXTURE_FILE_NOT_LOADED;
//         return INVALID_ASSETID;
//     }

//     m_assetsMap.insert({id, textruePath});

//     m_textures.insert({id, {0, height, nrChannels, {}}});
//     Texture& texture = m_textures.at(id);

//     uint32 dataSize = nrChannels * width * height;
//     texture.width = width;
//     texture.data.reserve(dataSize);
//     texture.data.insert(texture.data.end(), data, &data[dataSize]);

//     STBI_FREE(data);

//     return id;
// }

// void AssimpAssetsManager::registerScene(const std::string scenePath) 
// {
//     const aiScene *scene = m_importer.ReadFile(scenePath, aiProcess_Triangulate);
//     if(scene) {
//         std::cout << "File found" << std::endl;
//     }
//     else {
//         std::cout << "File not found" << std::endl;
//     }
// }

// };