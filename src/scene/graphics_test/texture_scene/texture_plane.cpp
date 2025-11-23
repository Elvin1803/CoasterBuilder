#ifdef DEBUG

#include <pch.h>
#include "texture_plane.h"

#include "utils/logger.h"

namespace scene {

    void TexturePlane::Update(float timestep) {
        m_model.SetMeshRotation("blue", glm::vec3(0, m_model.GetMeshRotation("blue").y - timestep, 0));
        m_model.SetMeshRotation("Suzanne", glm::vec3(0, m_model.GetMeshRotation("Suzanne").y - timestep, 0));
    }

}

#endif // DEBUG
