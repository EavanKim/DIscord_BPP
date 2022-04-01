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

	}

	void DSocket::setInfo(SOCKADDR_IN _connectInfo)
	{

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

	void DSocket::accespt(DSocket& _createdSocket)
	{
		if (INVALID_SOCKET != _createdSocket.getSocket())
		{
			_createdSocket.close();
		}
	}

	void DSocket::listen()
	{
	}

	void DSocket::talk()
	{
	}
	bool DSocket::IsInvalid()
	{
		return false;
	}
}