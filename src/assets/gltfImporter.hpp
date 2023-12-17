#ifndef __GLTFIMPORTER_HPP__
#define __GLTFIMPORTER_HPP__

#include <filesystem>

#include "../renderer/mesh.hpp"

namespace engine
{
    namespace ImporterGltf
    {
        Mesh ImportText(const std::filesystem::path& path);
        Mesh ImportBinary(const std::filesystem::path& path);
    }
}

#endif
