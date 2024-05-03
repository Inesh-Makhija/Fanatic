#include "fncpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Fanatic {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     FNC_CORE_ASSERT(false, "RendererAPI::None id currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		FNC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}