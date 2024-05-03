#include "fncpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Fanatic {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Fanatic::ShaderDataType::Float:     return GL_FLOAT;
			case Fanatic::ShaderDataType::Float2:    return GL_FLOAT;
			case Fanatic::ShaderDataType::Float3:    return GL_FLOAT;
			case Fanatic::ShaderDataType::Float4:    return GL_FLOAT;
			case Fanatic::ShaderDataType::Mat3:      return GL_FLOAT;
			case Fanatic::ShaderDataType::Mat4:      return GL_FLOAT;
			case Fanatic::ShaderDataType::Int:       return GL_INT;
			case Fanatic::ShaderDataType::Int2:      return GL_INT;
			case Fanatic::ShaderDataType::Int3:      return GL_INT;
			case Fanatic::ShaderDataType::Int4:      return GL_INT;
			case Fanatic::ShaderDataType::Bool:      return GL_BOOL;
		}

		FNC_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer)
	{
		FNC_CORE_ASSERT(vertexbuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexbuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexbuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffer.push_back(vertexbuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexbuffer)
	{
		glBindVertexArray(m_RendererID);
		indexbuffer->Bind();

		m_IndexBuffer = indexbuffer;
	}

}