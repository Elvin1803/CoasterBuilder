#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include "model.h"

namespace graphics::modelLoader {

    std::shared_ptr<graphics::Model> LoadModel(const std::string& filename);

}

#endif /* MODEL_LOADER.H */
