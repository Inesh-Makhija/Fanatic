#include "fncpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fanatic {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}