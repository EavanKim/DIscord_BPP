#include "pch.h"

namespace Discord
{
	DRef_Ptr<DLog> DLog::m_instance = DRef_Ptr<DLog>();//Parameter가 없다면 nullptr 값으로 생성.

	void DLog::Initialize(DString _path, DString _fileName, DString _extention)
	{
		if (nullptr == m_instance.get())
		{
			m_instance = new DLog(_path, _fileName, _extention);
		}
	}

	DRef_Ptr<DLog> DLog::GetInstance()
	{
		return DRef_Ptr<DLog>(m_instance);
	}

	void DLog::Destroy()
	{
		InterlockedExchange(&(*m_instance)->m_state, 0);
		m_instance.tryDestroy();
	}

	void DLog::printf(DString _log)
	{
		while(!TrySubmitThreadpoolCallback(DLog::printf_internal, new DLogContext(_log), 0)) {}
	}

	VOID DLog::printf_internal(PTP_CALLBACK_INSTANCE _instance, PVOID _context)
	{	
		DContext* typeCheck = static_cast<DContext*>(_context);
		if (CONTEXT_TYPE::LOG == typeCheck->getType())
		{
			DLogContext* logContext = static_cast<DLogContext*>(typeCheck);
			DRef_Ptr<DLog> LogPtr = DLog::GetInstance();
			if (nullptr == LogPtr.get())
			{
				return;
			}
			typeCheck = nullptr;
			DBOOL Work = 1;
			while (Work)
			{
				if (1 == InterlockedCompareExchange(&LogPtr.get()->m_barrier, 1, 0))
				{
					LogPtr.get()->m_logs.push_back(logContext->m_logString);
					Work = 0;
				}
				Sleep(10);
			}
			InterlockedExchange(&LogPtr.get()->m_barrier, 0);
			delete logContext;
		}

		return;
	}

	UINT DLog::update(void* _context)
	{
		DContext* typeCheck = static_cast<DContext*>(_context);
		if (CONTEXT_TYPE::LOG == typeCheck->getType())
		{
			DLogContext* logContext = static_cast<DLogContext*>(typeCheck);
			DRef_Ptr<DLog> LogPtr = DLog::GetInstance();
			typeCheck = nullptr;
			DString FullPath = LogPtr.get()->m_savePath + L'\\' + LogPtr.get()->m_saveFileName + L'.' + LogPtr.get()->m_extentions;
			
			std::wofstream output(FullPath, std::ios::out | std::ios::app, 0);
			if (!output.is_open())
				throw new DException(0x0);
			while (LogPtr.get()->m_state)
			{
				int vectorEOF = LogPtr.get()->m_logs.size();
				if ((0 != vectorEOF) && (1 == InterlockedCompareExchange(&LogPtr.get()->m_barrier, 1, 0)))
				{
					for (int seek = 0; vectorEOF > seek; ++seek)
					{
						output << LogPtr.get()->m_logs[seek] << std::endl;
					}
					output.close();
					LogPtr.get()->m_logs.clear();
					InterlockedExchange(&LogPtr.get()->m_barrier, 0);
				}
				Sleep(10);
			}
			delete logContext;
		}

		_endthreadex(0);
		return 0;
	}

	DLog::DLog()
		: m_savePath(L".")
		, m_saveFileName(L"Defalut")
		, m_extentions(L"log")
	{
		if (INVALID_HANDLE_VALUE == m_updateThread)
		{
			InterlockedExchange(&m_state, 1);
			m_updateThread = (HANDLE)_beginthreadex(NULL, 0, DLog::update, new DLogContext(L""), 0, NULL);
		}
		m_logs.clear();
	}

	DLog::DLog(DString _path, DString _fileName, DString _extention)
		: m_savePath(_path)
		, m_saveFileName(_fileName)
		, m_extentions(_extention)
	{
		if (INVALID_HANDLE_VALUE == m_updateThread)
		{
			InterlockedExchange(&m_state, 1);
			m_updateThread = (HANDLE)_beginthreadex(NULL, 0, DLog::update, new DLogContext(L""), 0, NULL);
		}
		m_logs.clear();
	}

	DLog::~DLog()
	{
		InterlockedExchange(&m_state, 0);
		if (INVALID_HANDLE_VALUE != m_updateThread)
		{
			CloseHandle(m_updateThread);
		}
		int vectorEOF = m_logs.size();
		if ((0 != vectorEOF) && (1 == InterlockedCompareExchange(&m_barrier, 1, 0)))
		{
			DString FullPath = m_savePath + L'\\' + m_saveFileName + L'.' + m_extentions;
			std::wofstream output(FullPath, std::ios::out | std::ios::app, 0);
			for (int seek = 0; vectorEOF > seek; ++seek)
			{
				output << m_logs[seek] << std::endl;
			}
			output.close();
			m_logs.clear();
			InterlockedExchange(&m_barrier, 0);
		}
	}
}
