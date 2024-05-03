#include "fncpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Fanatic {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		FNC_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FNC_CORE_ASSERT(status, "Failed to initialize Glad!");

		//FNC_CORE_INFO("OpenGl Info:");
		//FNC_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		//FNC_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		//FNC_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));     VIDEO : Our First Triangle! error

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}