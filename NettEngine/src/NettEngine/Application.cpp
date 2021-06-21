#include "nepch.h"
#include "Application.h"

#include "NettEngine/Events/ApplicationEvent.h"
#include "NettEngine/Log.h"

#include <GLFW/glfw3.h>

namespace NettEngine {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run() {

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}