#ifndef LYENHS_VIEWERCOMMAND_H_
#define LYENHS_VIEWERCOMMAND_H_

#include <vector>
#include <string>

namespace lyenhs
{
	class ViewerCommand
	{
	public:
		ViewerCommand();
		~ViewerCommand();

		bool Parse(const std::string& line);
		void Clear();

		void SetCommand(const std::string& cmd) { m_command = cmd; }
		const std::string& GetCommand() const { return m_command; }

		void AddArg(const std::string& arg) { m_args.push_back(arg); }
		void ClearArgs() { m_args.clear(); }

		const std::vector<std::string>& GetArgs() const { return m_args; }

	private:
		std::string		m_command;
		std::vector<std::string>	m_args;
	};


}




#endif//LYENHS_VIEWERCOMMAND_H_

