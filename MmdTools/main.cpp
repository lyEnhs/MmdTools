
#ifdef _WIN32
#include <Windows.h>
#include <shellapi.h>
#endif

#include <vector>
#include <string.h>
#include <Base/Log.h>
#include <Base/UnicodeUtil.h>

#include "viewer/ly_viewer.h"

int MMDViewerMain(const std::vector<std::string>& args)
{
	SABA_INFO("Let'go!!!");

	lyenhs::LyViewer viewer;

	if (!viewer.Initialize())
	{
		return -1;
	}

	int ret = viewer.Run();
	
	viewer.Uninitslize();

	SABA_INFO("Eixt!!!");
	return ret;
}

int main(int argc, char** argv)
{
	std::vector<std::string> args(argc);
#ifdef _WIN32
	{
		WCHAR* cmdline = GetCommandLineW();
		int wArgc;
		WCHAR** wArgs = CommandLineToArgvW(cmdline, &wArgc);
		for (int i=0; i< wArgc;++i)
		{
			args[i] = saba::ToUtf8String(wArgs[i]);
		}

	}
#else
	for (int i=0; i<argc; ++i)
	{
		args[i] = argv[i];
	}
#endif

	auto ret = MMDViewerMain(args);

	saba::SingletonFinalizer::Finalize();
	return ret;
}