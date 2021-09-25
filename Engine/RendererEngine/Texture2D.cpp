#include <GL/glew.h>
#include "Texture2D.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace RendererEngine
{
	Texture2D::Texture2D(const std::string& name) : m_name(name), m_texture(0), m_height(0), m_width(0), m_bpp(0)
	{
        stbi_set_flip_vertically_on_load(true);
        m_buffer = stbi_load(std::string("../../resources/textures/" + name).c_str(),
			&m_width, &m_height, &m_bpp, 0);
        if (!m_buffer)
            throw std::runtime_error("can't load texture " + name);

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

       	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
       	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
       	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
       	glGenerateMipmap(GL_TEXTURE_2D);

       	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
       	glBindTexture(GL_TEXTURE_2D, 0);

       	if (m_buffer)
           	stbi_image_free(m_buffer);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_texture);
	}

	Texture2D::Texture2D(Texture2D&& texture)
	{
		m_texture = texture.m_texture;
		m_name = texture.m_name;
		texture.m_texture = 0;
		m_bpp = texture.m_bpp;
		m_width = texture.m_width;
		m_height = texture.m_height;
	}

	void Texture2D::LoadTextureAtlas(const std::vector<std::string> subTextureName,
			const unsigned int subTextureWidth, const unsigned int subTextureHeight)
	{
       	glm::vec2 currentTextureOffset = { 0, m_height };
       	for (std::string currentSubTextureName : subTextureName)
       	{
       		glm::vec2 leftBottomUV = { currentTextureOffset.x / m_width,
	    		(currentTextureOffset.y - subTextureHeight) / m_height };
       		glm::vec2 rightTopUV = { (currentTextureOffset.x + subTextureWidth) /
	    		m_width, currentTextureOffset.y / m_height };
       		AddSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);
       		currentTextureOffset.x += subTextureWidth;
       		if (currentTextureOffset.x >= m_width)
       		{
           		currentTextureOffset.y -= subTextureHeight;
           		currentTextureOffset.x = 0;
      		}
       	}
    }

	void Texture2D::Bind(const unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::AddSubTexture(const std::string& name, const glm::vec2& leftBottomUV,
        	const glm::vec2& rightTopUV)
    {
       	m_subTexture.push_back(SubTexture(name, leftBottomUV, rightTopUV));
    }

    const Texture2D::SubTexture& Texture2D::GetSubTexture(const std::string& name) const
    {
    	for (int i = 0; i < m_subTexture.size(); i++)
       		if (m_subTexture.at(i).m_name == name)
            	return m_subTexture.at(i);
    	
		const static SubTexture defaultSubTexture;
       	return defaultSubTexture;
    }
}
