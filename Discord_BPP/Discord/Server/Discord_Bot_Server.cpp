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

		//Thread ����
		InterlockedExchange64(&m_listenEnable, 1);
	}

	DBot_Server::~DBot_Server()
	{
		//Thread ����
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
				//beginethreadex�ȿ��� ����� ��ü ����
				DBot_Server* Server = static_cast<DBot_Server*>(typeCheck);

				int addrlen = 0;
				while (Server->m_listenEnable)
				{
					Session = new DSession(Server->m_listen.accespt());

					//Session�� ���� �����Ǵ� Thread�� Owner��.
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
			//�������.
			//context�� thread�������ε�, ������ ���� Thread�� ������ ������ ��� �ڽ��� Thread�� �ƴ� �ܺ���� �ʿ���.
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
				//Process�� stdcall�� Listen���� Session�� ���۵ǰ� ����
				DSession* CurrentSession = static_cast<DSession*>(typeCheck);
				//��۸��� �߻����� �ʵ��� typeCheck�� ������� ���ϵ��� ������, _context�� ����ó�������� ����ϴ�.
				typeCheck = nullptr;

				CurrentSession;

				//ó���� ������ Responce�� �����־��ٸ� ���� ����
				//_context�� ��� Thread �������̾�� �ϴµ� ��������� Context�� access exception�� �߻��ϴ� ��찡 �ִٸ�
				//�߸� ���� �ڵ��̹Ƿ� ����� ����� �����ؾ� ��.
				delete CurrentSession;
			}
		}
		catch (...)
		{
			//�������.
			//context�� thread�������ε�, ������ ���� Thread�� ������ ������ ��� �ڽ��� Thread�� �ƴ� �ܺ���� �ʿ���.
			if (nullptr != _context)
				delete _context;
		}

		_endthreadex(0);
		return 0;
	}
}