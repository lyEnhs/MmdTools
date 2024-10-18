#ifndef VIEWER_CONTEXT_H_ 
#define VIEWER_CONTEXT_H_

#include <string>

namespace lyenhs
{
	class ViewerContext
	{
	public:
		ViewerContext();
		~ViewerContext();

		const std::string& GetWorkDir() const {
			return m_workDir;
		}

		int GetMSAACount() const { return m_msaaCount; }
		void EnableMSAA(bool enable) { m_msaaEnable = enable; }
		void SetMSAACount(int count) { m_msaaCount = count; }
	private:
		std::string		m_workDir;

		bool	m_msaaEnable;
		int		m_msaaCount;
	};

}

#endif//VIEWER_CONTEXT_H_