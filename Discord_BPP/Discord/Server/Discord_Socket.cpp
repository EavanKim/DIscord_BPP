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

	SOCKET DSocket::accespt()
	{
		return accept(m_socket, (SOCKADDR*)&m_connectInfo, &m_addrlen);
	}

	bool DSocket::IsInvalid()
	{
		return INVALID_SOCKET == m_socket;
	}

	void DSocket::getPeer()
	{
		getpeername(m_socket, (SOCKADDR*)&m_connectInfo, &m_addrlen);
	}

	void DSocket::packet_recv()
	{
		char buf[513];
		ZeroMemory(&buf, 513);
		while (1)
		{
			int retval = recv(m_socket, buf, 512, 0);
			if (SOCKET_ERROR == retval)
			{
				return;
			}
			else if (0 == retval)
			{
				break;
			}
			else
			{
				for(int Count = 0; retval > Count; ++Count)
					m_data.push_back(buf[Count]);
			}
		}
	}

	void DSocket::packet_send(std::vector<char>& _senddata)
	{
		int maxCount = _senddata.size();
		for (int seek = 0; maxCount > seek; seek += 512)
		{
			int retval = send(m_socket, (const char*)_senddata.data()[seek], (maxCount - seek) > 512 ? 512 : (maxCount - seek), 0);
			if (SOCKET_ERROR == retval)
			{
				return;
			}
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
}
