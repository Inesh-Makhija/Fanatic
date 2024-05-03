#include "fncpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Fanatic {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     FNC_CORE_ASSERT(false, "RendererAPI::None id currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(path);
		}

		FNC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return Ref<Texture2D>();
	}

}