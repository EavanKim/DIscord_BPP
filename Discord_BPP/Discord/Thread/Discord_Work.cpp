#include "pch.h"

namespace Discord
{
	DWork::DWork()
	{
		if (NULL == m_pWorkItem)
		{
			m_pWorkItem = CreateThreadpoolWork(m_func, m_Param, NULL);
		}
	}

	DWork::~DWork()
	{
		if (NULL != m_pWorkItem)
		{
			CloseThreadpoolWork(m_pWorkItem);
		}
	}

	void DWork::start()
	{
		SubmitThreadpoolWork(m_pWorkItem);
	}

	void DWork::setParam(LPVOID _lpParam)
	{
		m_Param = _lpParam;
	}

	void DWork::setFunction(VOID(NTAPI* _func)(_Inout_ PTP_CALLBACK_INSTANCE _instance, _Inout_opt_ PVOID _context, _Inout_ PTP_WORK _work))
	{
		m_func = _func;
	}
}
