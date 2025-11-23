#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "graphics/3d/model.h"

namespace scene {

    class ModelManager {
    public:
        std::shared_ptr<graphics::Model> GetModel(std::string name);

    private:
        std::unordered_map<std::string, std::shared_ptr<graphics::Model>> m_models;
    };

}

#endif /* MODEL_MANAGER.H */
