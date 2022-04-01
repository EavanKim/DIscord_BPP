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

		InterlockedExchange64(&m_listenEnable, 1);
	}

	DBot_Server::~DBot_Server()
	{
		InterlockedExchange64(&m_listenEnable, 0);
		m_listen.close();
		WSACleanup();
	}

	UINT DBot_Server::Listen(void* _context)
	{
		DContext* typeCheck = static_cast<DContext*>(_context);

		if (CONTEXT_TYPE::SERVER == typeCheck->getType())
		{
			DBot_Server* Server = static_cast<DBot_Server*>(typeCheck);

			DSocket Session;
			HANDLE hThread = INVALID_HANDLE_VALUE;
			int addrlen = 0;
			while (Server->m_listenEnable)
			{
				Server->m_listen.accespt(Session);

				hThread = (HANDLE)_beginthreadex(NULL, 0, DBot_Server::Process, (void*)&Session, NULL, NULL);
				if (INVALID_HANDLE_VALUE == hThread)
					Session.close();
				else
					CloseHandle(hThread);
			}
		}

		_endthreadex(0);
		return 0;
	}

	UINT DBot_Server::Process(void* _context)
	{

		_endthreadex(0);
		return 0;
	}
}