#include "pch.hpp"
#include "assets/importer.hpp"

#include "assets/gltfImporter.hpp"

namespace engine
{
    namespace AssetImporter
    {
        Mesh Import(const std::filesystem::path& path)
        {
            return ImporterGltf::ImportText(path);
        }
    }
}
