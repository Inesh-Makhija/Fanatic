#include "fncpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fanatic {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     FNC_CORE_ASSERT(false, "RendererAPI::None id currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return new OpenGLVertexArray();
		}

		FNC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}