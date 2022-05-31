// Own headers
#include <engine/assets/IAssetsManager.h>

namespace Sopel {
const Model IAssetsManager::getModel(const AssetId id)
{
    if(m_models.count(id) != 0) {
        return m_models.at(id);
    }

    // Id is not assing to any model. Return empty object
    return Model();
}

};

