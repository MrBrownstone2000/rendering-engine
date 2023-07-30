#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <filesystem>
#include <vector>
#include "../util/types.hpp"

namespace engine
{
    struct TextureParams
    {
        // Params for filtering, mipmaps, wrap
    };

    class Texture
    {
        public:
            Texture() : m_id(0) {}
            Texture(const std::filesystem::path& path);
            ~Texture();

            Texture(const Texture& rhs) = delete;
            Texture(Texture&& rhs);
            Texture& operator=(const Texture& rhs) = delete;
            Texture& operator=(Texture&& rhs);

            void bind() const;
            void unbind() const;

            uint32_t getId() const { return m_id; }

        private:
            std::vector<uint8_t> loadImage(const std::filesystem::path& path, 
                                            uint32_t& width, uint32_t& height, 
                                            uint32_t& channels);

        private:
            uint32_t m_id;
    };
}

#endif
