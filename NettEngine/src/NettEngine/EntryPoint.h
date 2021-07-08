#pragma once
#include "nepch.h"

#ifdef NE_PLATFORM_WINDOWS

extern NettEngine::Application* NettEngine::CreateApplication();

int main(int argc, char** argv)
{
	NettEngine::Log::Init();
	auto app = NettEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif