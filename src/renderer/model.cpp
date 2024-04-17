#include "pch.hpp"
#include "renderer/model.hpp"

namespace engine
{
    Model::Model(std::vector<Mesh>&& meshes)
        : meshes(std::move(meshes))
    {
    }
}
