#ifndef _TEXTURE2D_HPP_
#define _TEXTURE2D_HPP_
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace RendererEngine
{
	class Texture2D
	{
	public:
		struct SubTexture
		{
			glm::vec2 m_leftBottomUV;
			glm::vec2 m_rightTopUV;
			std::string m_name;
			
			SubTexture(const std::string& name, const glm::vec2& leftBottomUV,
					const glm::vec2& rightTopUV) : m_name(name),
					m_leftBottomUV(leftBottomUV), m_rightTopUV(rightTopUV) {}
			SubTexture() : m_leftBottomUV(0.0f), m_rightTopUV(1.0f) {}
		};
		Texture2D(const std::string& name);
		~Texture2D();
		Texture2D(Texture2D&&);
		void LoadTextureAtlas(const std::vector<std::string> subTextureName,
				const unsigned int subTextureWidth, const unsigned int subTextureHeight);
		void Bind(const unsigned int slot = 0);
		void Unbind();
		void AddSubTexture(const std::string& name, const glm::vec2& leftBottomUV,
				const glm::vec2& rightTopUV);
		const SubTexture& GetSubTexture(const std::string& name) const;
	private:
		unsigned int m_texture;
		std::string m_name;
		unsigned char* m_buffer;
		int m_width, m_height, m_bpp;
		std::vector<SubTexture> m_subTexture;
	};
}

#endif
