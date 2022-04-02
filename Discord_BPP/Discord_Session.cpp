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
	void DSession::setAcceptSocket(SOCKET _sock)
	{
	}
}
