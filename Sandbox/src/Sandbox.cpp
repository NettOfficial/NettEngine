#include <NettEngine.h>

class ExampleLayer : public NettEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		NE_INFO("ExampleLayer::Update");
	}

	void OnEvent(NettEngine::Event& event) override
	{
		NE_TRACE("{0}", event);
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