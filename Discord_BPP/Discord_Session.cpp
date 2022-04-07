#include "pch.h"

namespace Discord
{
	DSession::DSession()
	{
	}
	DSession::DSession(SOCKET _sock)
		: DContext(CONTEXT_TYPE::SESSION)
		, m_socket(_sock)
	{

	}

	DSession::~DSession()
	{

	}

	void DSession::listenRequest()
	{
		m_socket.getPeer();
		
	}

	void DSession::doResponse()
	{

	}

	void DSession::setAcceptSocket(SOCKET _sock)
	{
		if (INVALID_SOCKET == _sock)
			return;

		if (INVALID_SOCKET == m_socket.getSocket())
			m_socket.setSocket(_sock);
	}
}
