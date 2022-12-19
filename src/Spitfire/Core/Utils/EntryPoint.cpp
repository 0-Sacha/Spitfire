#include "Spitfirepch.h"
#include "EntryPoint.h"

#ifdef SPITFIRE_PLATFORM_WINDOWS

int main(int argc, char** argv) {
	auto app = Spitfire::CreateApplication();
	app->Run();
	delete app;
}

#endif
