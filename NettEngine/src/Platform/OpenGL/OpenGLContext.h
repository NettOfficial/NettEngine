#pragma once

#include "NettEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace NettEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle = nullptr;
	};
}