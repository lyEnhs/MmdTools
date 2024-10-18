#include "Path.h"

#include <algorithm>
#include <Windows.h>
#include <Base/UnicodeUtil.h>


namespace lyenhs
{
	const char PathDelimiter = '\\';
	const char* PathDelimiters = "\\/";


	std::string PathUtil::GetCWD()
	{
		DWORD sz = GetCurrentDirectoryW(0, nullptr);
		std::vector<wchar_t> buffer(sz);
		GetCurrentDirectory(sz, &buffer[0]);
		std::string workDir = saba::ToUtf8String(&buffer[0]);
		return workDir;
	}

	std::string PathUtil::GetExePath()
	{
		wchar_t filePath[MAX_PATH] = { 0 };
		if (GetModuleFileNameW(nullptr, filePath, MAX_PATH))
		{
			return saba::ToUtf8String(filePath);
		}
		return "";
	}

	std::string PathUtil::Combine(const std::vector<std::string>& parts)
	{
		std::string result;
		for (const auto part : parts)
		{
			if (!part.empty())
			{
				auto pos = part.find_last_not_of(PathDelimiters);
				if (pos != std::string::npos)
				{
					if (!result.empty())
					{
						result.append(&PathDelimiter, 1);
					}
					result.append(part.c_str(), pos + 1);
				}
			}
		}
		return result;
	}
	 
	std::string PathUtil::Combine(const std::string& a, const std::string& b)
	{
		return Combine({ a, b });
	}

	std::string PathUtil::GetDirectoryName(const std::string& path)
	{
		auto pos = path.find_last_of(PathDelimiters);
		if (pos == std::string::npos)
		{
			return "";
		}
		return path.substr(0, pos);
	}

	std::string PathUtil::GetFileName(const std::string& path)
	{
		auto pos = path.find_last_of(PathDelimiters);
		if (pos == std::string::npos)
		{
			return path;
		}
		return path.substr(pos + 1, path.size()-pos);
	 }

	std::string PathUtil::GetFileNameWithoutExe(const std::string& path)
	{
		const std::string filename = GetFileName(path);
		auto pos = filename.find_last_of('.');
		if (pos == std::string::npos)
		{
			return filename;
		}
		return filename.substr(0, pos);
	}

	std::string PathUtil::GetExe(const std::string& path)
	{
		auto pos = path.find_last_of('.');
		if (pos == std::string::npos)
		{
			return "";
		}

		std::string exe = path.substr(pos+1, path.size() - pos);
		for (auto& ch : exe)
		{
			ch = (char)tolower(ch);
		}
		return exe;
	}

	std::string PathUtil::GetDelimiter()
	{
		return "\\";
	}

	std::string PathUtil::Normalize(const std::string& path)
	{
		std::string result = path;

		std::replace(result.begin(), result.end(), '/', '\\');

		return result;
	 }

}
