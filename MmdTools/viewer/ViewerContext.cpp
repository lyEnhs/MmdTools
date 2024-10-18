#include "ViewerContext.h"
#include "Path.h"

namespace lyenhs
{
	ViewerContext::ViewerContext()
		:m_msaaCount(0)
	{
		m_workDir = PathUtil::GetCWD();
	}

	ViewerContext::~ViewerContext()
	{

	}

}
