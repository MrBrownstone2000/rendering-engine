#include "pch.hpp"
#include "importer.hpp"

#include "gltfImporter.hpp"

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
