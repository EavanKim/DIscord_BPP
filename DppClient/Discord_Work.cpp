#include "pch.h"

namespace Discord
{

#if USE_THREADPOOL
	void DWork::start()
	{
		if (NULL == m_pWorkItem)
		{

		}
	}

	void DWork::stop()
	{

	}

	DWORD DWork::getReturn()
	{
		return m_return;
	}

	void DWork::setParam(LPVOID _lpParam)
	{
		m_Param = _lpParam;
	}

	void DWork::setFunction(UINT(*_func)(void* _lpParam))
	{
		m_func = _func;
	}

#else
	void DWork::start()
	{
		if (INVALID_HANDLE_VALUE == m_thread)
		{
			//Thread 안에서 Parameter Nullcheck 필수.
			//어려울 것 같다면 Thread-Safe한 스마트포인터 처리 필수.
			// 제프리 리처의 Windows C++ 을 보면 CreateThread는 _tiddata 관련 문제가 있으므로 beginthreadex사용을 권장
			//m_thread = CreateThread(NULL, 0, m_func, &m_Param, 0, &m_return);
			m_thread = (HANDLE)_beginthreadex(NULL, 0, m_func, NULL, 0, &m_threadID);
		}
	}

	void DWork::stop()
	{
		if (INVALID_HANDLE_VALUE != m_thread)
		{
			CloseHandle(m_thread);
			m_thread = INVALID_HANDLE_VALUE;
		}
	}

	DWORD DWork::getReturn()
	{
		return m_return;
	}

	void DWork::setParam(LPVOID _lpParam)
	{
		m_Param = _lpParam;
	}

	void DWork::setFunction(UINT(*_func)(void* _lpParam))
	{
		m_func = _func;
	}
#endif
}
