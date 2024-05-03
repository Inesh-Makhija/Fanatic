#pragma once

#ifdef FNC_PLATFORM_WINDOWS

extern Fanatic::Application* Fanatic::CreateApplication();

int main(int argc, char** argv)
{
	Fanatic::Log::Init();
	FNC_CORE_WARN("Initailized Log!");
	int a = 5;
	FNC_INFO("Hello! Var={0}", a);

	auto app = Fanatic::CreateApplication();
	app->Run();
	delete app;
}

#endif // FNC_PLATFORM_WINDOWS