#include "fncpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Fanatic {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     FNC_CORE_ASSERT(false, "RendererAPI::None id currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
		}

		FNC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     FNC_CORE_ASSERT(false, "RendererAPI::None id currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return new OpenGLIndexBuffer(indices, size);
		}

		FNC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}