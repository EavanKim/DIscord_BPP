#include "pch.h"

namespace Discord
{
	DBot_Server::DBot_Server(SOCKADDR_IN& _endPoint)
		: DContext(CONTEXT_TYPE::SERVER)
		, m_thread(INVALID_HANDLE_VALUE)
	{
		if (0 != WSAStartup(MAKEWORD(2, 2), &m_wsaData))
		{
			throw DException(0x0101000000000001);
		}

		m_listen.open();

		//Thread 제어
		InterlockedExchange64(&m_listenEnable, 1);
	}

	DBot_Server::~DBot_Server()
	{
		//Thread 제어
		InterlockedExchange64(&m_listenEnable, 0);
		m_listen.close();
	
		WSACleanup();
	}

	UINT DBot_Server::Listen(void* _context)
	{
		DSession* Session = nullptr;
		HANDLE hThread = INVALID_HANDLE_VALUE;
		try
		{
			DContext* typeCheck = static_cast<DContext*>(_context);

			if (CONTEXT_TYPE::SERVER == typeCheck->getType())
			{
				DBot_Server* Server = static_cast<DBot_Server*>(typeCheck);

				//Thread 저장소에 복사되어 사용할 것이라 기대
				int addrlen = 0;
				while (Server->m_listenEnable)
				{
					Session = new DSession(Server->m_listen.accespt());

					//Session은 새로 생성되는 Thread가 Owner임.
					hThread = (HANDLE)_beginthreadex(NULL, 0, DBot_Server::Process, (void*)Session, NULL, NULL);
					if (INVALID_HANDLE_VALUE == hThread)
					{
						if (nullptr != Session)
							delete Session;
					}
					else
						CloseHandle(hThread);
				}
			}
		}
		catch(...)
		{
			//고민지점.
			//Session을 주도적으로 해체하는 타이밍을 listen socket기준으로 할 지, Task기준으로 할 지 통일 필요
			if (nullptr != Session)
				delete Session;

			if (INVALID_HANDLE_VALUE != hThread)
				CloseHandle(hThread);
		}

		_endthreadex(0);
		return 0;
	}

	UINT DBot_Server::Process(void* _context)
	{
		try
		{
			DContext* typeCheck = static_cast<DContext*>(_context);

			if (CONTEXT_TYPE::SESSION == typeCheck->getType())
			{
				//Process를 stdcall한 Listen에서 Session이 시작되고 있음
				DSession* CurrentSession = static_cast<DSession*>(typeCheck);



				//처리가 끝나고 Responce를 돌려주었다면 세션 종료
				delete CurrentSession;
			}
		}
		catch (...)
		{
			//고민지점.
			//Session을 주도적으로 해체하는 타이밍을 listen socket기준으로 할 지, Task기준으로 할 지 통일 필요
			if (nullptr != _context)
				delete _context;
		}

		_endthreadex(0);
		return 0;
	}
}