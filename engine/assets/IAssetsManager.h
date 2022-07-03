#pragma once
// System headers
#include <map>
#include <string>
#include <unordered_map>
// Own headers
#include <engine/core/types.h>
#include <engine/assets/SpModel.h>
#include <engine/assets/SpMaterial.h>
#include <engine/errors/ErrorCodes.h>


namespace Sopel {

class IAssetsManager {
public:
    /** Destructor */
    virtual ~IAssetsManager() = default;

    /** This method will register new model in the asset system. Model is defined by the path to the physical file.
     *  If asset is registered already, then assigned id will be returned, otherwise new id will be given.
     *  If error occurred during registration, invalid ID will be return and the appropriate error code will be
     *  returned in the second parameter.
     */
    virtual AssetId registerModel(const std::string path, ErrorCodes::value& errCode) = 0;

    /** This method will register new texture in the asset system. Texture is defined by the path to the physical file.
     *  If Texture is registered already, then assigned id will be returned, otherwise new id will be given.
     *  If error occurred during registration, invalid ID will be return and the appropriate error code will be
     *  returned in the second parameter.
     */
    virtual AssetId registerTexture(const std::string textruePath, ErrorCodes::value& errCode) = 0;

    

    /** Return model assgin to the given id. If no model is assign to id empty object will be returned */
    const Model getModel(const AssetId id);

    /** Return model assgin to the given id. If no model is assign to id empty object will be returned */
    const Sopel::Texture& getTexture(const AssetId id);
 
protected:
    /** Map combining id given by the asset manager with the physical file path which identify particular resource.
     *  Records are stored in sorted increasing manner 
     */
    std::map<AssetId, std::string> m_assetsMap;

    /** Models map which combine asset id with particular model */
    std::unordered_map<AssetId, Model> m_models;

    /** Texture map which combine asset id with particular texture */
    std::unordered_map<AssetId, Sopel::Texture> m_textures;
};};