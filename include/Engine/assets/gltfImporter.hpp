#ifndef __GLTFIMPORTER_HPP__
#define __GLTFIMPORTER_HPP__

#include <filesystem>

#include "../renderer/model.hpp"

namespace engine
{
    namespace ImporterGltf
    {
        Model Import(const std::filesystem::path& path);
    }
}

#endif
