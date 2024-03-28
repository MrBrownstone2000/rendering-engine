#ifndef __IMPORTER_HPP__
#define __IMPORTER_HPP__

#include <filesystem>

#include "../renderer/mesh.hpp"

namespace engine
{
    namespace AssetImporter
    {
        Mesh Import(const std::filesystem::path& path);
    }
}

#endif
