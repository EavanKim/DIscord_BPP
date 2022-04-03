#include "pch.h"

namespace Discord
{
	DSession::DSession()
	{
	}
	DSession::DSession(SOCKET _sock)
		: m_socket(_sock)
	{

	}

	DSession::~DSession()
	{

	}

	void DSession::listenRequest()
	{
		m_socket.listen();
	}

	void DSession::doResponse()
	{
		m_socket.talk();
	}

	void DSession::setAcceptSocket(SOCKET _sock)
	{
		if (INVALID_SOCKET == _sock)
			return;

		if (INVALID_SOCKET == m_socket.getSocket())
			m_socket.setSocket(_sock);
	}
}
