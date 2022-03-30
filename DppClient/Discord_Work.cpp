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
			//Thread �ȿ��� Parameter Nullcheck �ʼ�.
			//����� �� ���ٸ� Thread-Safe�� ����Ʈ������ ó�� �ʼ�.
			// ������ ��ó�� Windows C++ �� ���� CreateThread�� _tiddata ���� ������ �����Ƿ� beginthreadex����� ����
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
