#include "pch.hpp"
#include "texture.hpp"

#include <GL/glew.h>
#include <OpenImageIO/imageio.h>

namespace engine
{
    Texture::Texture(const std::filesystem::path& path)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        uint32_t width, height, channels;
        auto pixels = loadImage(path, width, height, channels);

        GLuint internalFormat = 0;
        GLuint inputFormat = 0;
        switch (channels)
        {
            case 3:
                internalFormat = GL_RGB8;
                inputFormat = GL_RGB;
                break;
            case 4:
                internalFormat = GL_RGBA8;
                inputFormat = GL_RGBA;
                break;
            default:
                engineLog.error("Wrong format").watch(channels);
        }
        glTextureStorage2D(m_id, 1, internalFormat, width, height);
        glTextureSubImage2D(m_id, 0, 0, 0, width, height, inputFormat, GL_UNSIGNED_BYTE, pixels.data());
    }

    std::vector<uint8_t> Texture::loadImage(const std::filesystem::path& path, 
                                    uint32_t& width, uint32_t& height, uint32_t& channels)
    {
        using namespace OIIO;

        auto input = ImageInput::open(path);
        if (!input)
        {
            engineLog.error("Image couldn't open: " + path.string());
            return {};
        }

        const ImageSpec& spec = input->spec();
        width = spec.width;
        height = spec.height;
        channels = spec.nchannels;
        std::vector<uint8_t> pixels(width * height * channels);

        int scanlinesize = width * channels * sizeof(uint8_t);
        uint8_t* lastRow = (uint8_t*) pixels.data() + (height - 1) * scanlinesize;

        input->read_image(0, 0, 0, channels, TypeDesc::UINT8, lastRow,
                          AutoStride, -scanlinesize, AutoStride);
        input->close();

        return pixels;
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_id);
    }

    Texture::Texture(Texture&& rhs)
    {
        m_id = rhs.m_id;
        rhs.m_id = 0;
    }

    Texture& Texture::operator=(Texture&& rhs)
    {
        m_id = rhs.m_id;
        rhs.m_id = 0;
        return *this;
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
