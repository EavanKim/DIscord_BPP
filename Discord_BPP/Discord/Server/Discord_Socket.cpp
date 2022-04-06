#include "pch.h"

namespace Discord
{
	DSocket::DSocket()
	{

	}

	DSocket::DSocket(SOCKET _socket)
		: m_socket(_socket)
		, m_addrlen(sizeof(SOCKADDR_IN))
	{

	}

	DSocket::~DSocket()
	{
		close();
	}

	void DSocket::open()
	{
		if (INVALID_SOCKET == m_socket)
		{
			m_socket = socket(AF_INET, SOCK_STREAM, 0);
			if (INVALID_SOCKET == m_socket)
			{
				throw new DException(0x0000);
			}
		}
	}

	void DSocket::listen()
	{
		bind(m_socket, (SOCKADDR*)&m_connectInfo, sizeof(m_connectInfo));
	}

	void DSocket::close()
	{
		if (INVALID_SOCKET != m_socket)
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
		}
	}

	void DSocket::setSocket(SOCKET _socket)
	{
		m_socket = _socket;
	}

	void DSocket::setInfo(SOCKADDR_IN _connectInfo)
	{
		m_connectInfo = _connectInfo;
	}

	SOCKET DSocket::getSocket()
	{
		return m_socket;
	}

	SOCKADDR_IN DSocket::getInfo()
	{
		return m_connectInfo;
	}

	int DSocket::getAddrlen()
	{
		return m_addrlen;
	}

	int DSocket::getSessionReturn()
	{
		return m_sessionreturn;
	}

	SOCKET DSocket::accespt()
	{
		return INVALID_SOCKET;
	}

	bool DSocket::IsInvalid()
	{
		return false;
	}
}
