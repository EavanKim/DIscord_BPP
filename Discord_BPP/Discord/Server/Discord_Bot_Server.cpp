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
				//beginethreadex안에서 사용할 객체 생성
				DBot_Server* Server = static_cast<DBot_Server*>(typeCheck);

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
			//context는 thread종속적인데, 에러가 나서 Thread에 문제가 생겼을 경우 자신의 Thread가 아닌 외부제어가 필요함.
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
				//댕글링이 발생하지 않도록 typeCheck는 사용하지 못하도록 하지만, _context는 예외처리용으로 남깁니다.
				typeCheck = nullptr;

				CurrentSession;

				//처리가 끝나고 Responce를 돌려주었다면 세션 종료
				//_context는 모두 Thread 종속적이어야 하는데 종료시점에 Context가 access exception이 발생하는 경우가 있다면
				//잘못 만든 코드이므로 수행된 명령을 수정해야 함.
				delete CurrentSession;
			}
		}
		catch (...)
		{
			//고민지점.
			//context는 thread종속적인데, 에러가 나서 Thread에 문제가 생겼을 경우 자신의 Thread가 아닌 외부제어가 필요함.
			if (nullptr != _context)
				delete _context;
		}

		_endthreadex(0);
		return 0;
	}
}