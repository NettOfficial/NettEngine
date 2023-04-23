#include <NettEngine.h>

class ExampleLayer : public NettEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (NettEngine::Input::IsKeyPressed(NE_KEY_TAB))
		{
			NE_TRACE("Tab key is pressed (poll)!");
		}
			
	}

	void OnEvent(NettEngine::Event& event) override
	{
		if (event.GetEventType() == NettEngine::EventType::KeyPressed)
		{
			NettEngine::KeyPressedEvent& e = (NettEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == NE_KEY_TAB)
			{
				NE_TRACE("Tab key is pressed (event)!");
			}
			NE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public NettEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new NettEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

NettEngine::Application* NettEngine::CreateApplication()
{
	return new Sandbox();
}