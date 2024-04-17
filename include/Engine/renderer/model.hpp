#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <vector>

#include "mesh.hpp"

namespace engine
{
    class Model
    {
    public:
        Model() = default;
        Model(std::vector<Mesh>&& meshes);

        std::vector<Mesh> meshes;
    };
}

#endif
