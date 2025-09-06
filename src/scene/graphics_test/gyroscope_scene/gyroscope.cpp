#include <pch.h>
#include "gyroscope.h"

#include "utils/logger.h"

namespace scene {

    void Gyroscope::Update(float timestep) {
        m_model.SetMeshRotation("outer", glm::vec3(0, m_model.GetMeshRotation("outer").y + 0.01f, 0));
        m_model.SetMeshRotation("inner", glm::vec3(0, 0, m_model.GetMeshRotation("inner").z + 0.005f));

        //LOG_DEBUG("Gyroscope outer rotation: {}", glm::to_string(m_model.GetMeshRotation("outer")));
    }

}
