#ifdef DEBUG

#include <pch.h>
#include "gyroscope.h"

#include "utils/logger.h"

namespace scene {

    void Gyroscope::Update(float timestep) {
        m_model.SetMeshRotation("outer", glm::vec3(0, m_model.GetMeshRotation("outer").y + timestep * 0.1f, 0));
        m_model.SetMeshRotation("inner", glm::vec3(0, 0, m_model.GetMeshRotation("inner").z + timestep * 0.05f));
    }

}

#endif // DEBUG
