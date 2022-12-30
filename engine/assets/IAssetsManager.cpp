// Own headers
#include <engine/assets/IAssetsManager.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Sopel {

AssetID IAssetsManager::registerModel(const std::string path, AssetID id) {
    Assimp::Importer m_importer;
    const aiScene *scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    return 0u;
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

