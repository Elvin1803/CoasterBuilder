#ifndef ENTITY_H
#define ENTITY_H

#include "graphics/model/modelInstance.h"

class Renderer;

namespace scene {

    class Entity {
        friend class ::Renderer;

    public:
        Entity(graphics::ModelInstance model)
            : m_model(model) {};
        virtual ~Entity() = default;

        virtual void Update(float timestep) = 0;

        graphics::ModelInstance GetModel() { return m_model; };

        void SetPosition(glm::vec3& newPos) {
            m_position = newPos;
            m_isTranformDirty = true;
        };

        void SetRotation(glm::vec3& newRot) {
            m_rotation = newRot;
            m_isTranformDirty = true;
        };

        void SetScale(glm::vec3& newScale) {
            m_scale = newScale;
            m_isTranformDirty = true;
        };

    protected:
        graphics::ModelInstance m_model;

        glm::vec3 m_position = glm::vec3(0.0f);
        glm::vec3 m_rotation = glm::vec3(0.0f);
        glm::vec3 m_scale = glm::vec3(1.0f);

        bool m_isTranformDirty;
        glm::mat4 m_modelMatrix = glm::mat4(1.0f);
    };

}

#endif // ENTITY_H
