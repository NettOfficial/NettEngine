#include <NettEngine.h>

class Sandbox : public NettEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

NettEngine::Application* NettEngine::CreateApplication()
{
	return new Sandbox();
}