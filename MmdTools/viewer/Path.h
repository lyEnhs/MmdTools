#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <vector>

namespace lyenhs
{
	class PathUtil
	{
	public:
		PathUtil() = delete;
		PathUtil(const PathUtil&) = delete;
		PathUtil& operator = (const PathUtil&) = delete;
		
		static std::string GetCWD();
		static std::string GetExePath();
		static std::string Combine(const std::vector<std::string>& parts);
		static std::string Combine(const std::string& a, const std::string& b);
		static std::string GetDirectoryName(const std::string& path);
		static std::string GetFileName(const std::string& path);
		static std::string GetFileNameWithoutExe(const std::string& path);
		static std::string GetExe(const std::string& path);
		static std::string GetDelimiter();
		static std::string Normalize(const std::string& path);
	};
}


#endif//PATH_H_