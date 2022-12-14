#pragma once
#include <engine/core/components/Component.h>

// All data necesry for visual aspect like model, material etc.
_COMPONENT(CRender) {
    uint16 x;
    uint16 y;
};

// Position of object in the world, but not it visual aspect (ex. area which trigger event)
_COMPONENT(CWorldTransform) {
    uint16 x;
    uint16 y;
};

// Camera information
_COMPONENT(CCamera) {
    uint16 x;
    uint16 y;
};
