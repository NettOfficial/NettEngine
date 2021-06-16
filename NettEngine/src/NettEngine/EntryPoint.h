#pragma once

#ifdef NE_PLATFORM_WINDOWS

extern NettEngine::Application* NettEngine::CreateApplication();

int main(int argc, char** argv)
{
	NettEngine::Log::Init();
	NE_CORE_WARN("lol");
	NE_CORE_INFO("BUBN");

	auto app = NettEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif