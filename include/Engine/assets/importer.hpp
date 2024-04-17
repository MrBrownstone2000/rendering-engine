#ifndef __IMPORTER_HPP__
#define __IMPORTER_HPP__

#include <filesystem>

#include "../renderer/model.hpp"

namespace engine
{
    namespace AssetImporter
    {
        Model Import(const std::filesystem::path& path);
    }
}

#endif
