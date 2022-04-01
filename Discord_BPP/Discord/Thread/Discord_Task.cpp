#include "pch.h"

namespace Discord
{
	DTask::DTask()
	{

	}

	DTask::~DTask()
	{
		stop();
	}

	void DTask::start()
	{
		if ((INVALID_HANDLE_VALUE == m_thread) && nullptr != m_func)
		{
			m_thread = (HANDLE)_beginthreadex(NULL, 0, m_func, m_param, NULL, NULL);
		}
	}

	void DTask::stop()
	{
		if (INVALID_HANDLE_VALUE != m_thread)
		{
			CloseHandle(m_thread);
		}
	}

	void DTask::set_Function(UINT(*_func)(void* _context))
	{
		m_func = _func;
	}

	void DTask::set_Param(void* _param)
	{
		m_param = _param;
	}
}
