#pragma once

// Own headers
#include <engine/assets/IAssetsManager.h>
// External
#include <assimp/Importer.hpp>

namespace Sopel {

/** Asset manager based on the assimp library */
class AssimpAssetsManager : public IAssetsManager {
public:
    /** Constructors */
    AssimpAssetsManager();

    /** Destructor */
    virtual ~AssimpAssetsManager();

    AssetId registerModel(const std::string path, ErrorCodes::value& errCode) override;

protected:
    /** Main assimp asset importer */
    Assimp::Importer m_importer;



};};
