#pragma once
#include <engine/common/BasicTypes.h>
#include <engine/core/components/Component.h>

#include <glm/matrix.hpp>


// All data necessary for visual aspect like model, material etc.
_COMPONENT(CRender) {
     /*! \brief */
    AssetID model = INVALID_ASSET_ID;

     /*! \brief */
    GPID gpid = INVALID_GP_ID;

    uint16 x;
    uint16 y;
};

// Position of object in the world, but not it visual aspect (ex. area which trigger event)
_COMPONENT(CWorldTransform) {
    glm::mat4 transform;
    uint16 x;
    uint16 y;
};

// Camera information
_COMPONENT(CCamera) {
    uint16 x;
    uint16 y;
};
