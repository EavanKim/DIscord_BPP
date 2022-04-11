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
		m_socket.close();
	}

	void DSession::listenRequest()
	{
		m_socket.getPeer();
		m_socket.packet_recv();
	}

	void DSession::Process()
	{
	}

	void DSession::doResponse()
	{
		m_socket.packet_send(m_responseData);
	}

	void DSession::setupData(char* _ptr, int _length)
	{
		m_responseData.clear();
		for (int seek = 0; _length > seek; ++seek)
			m_responseData.push_back(_ptr[seek]);
	}

	void DSession::setupData(std::vector<char>& _data)
	{
		m_responseData.clear();
		int DataEOF = _data.size();
		for (int seek = 0; DataEOF > seek; ++seek)
			m_responseData.push_back(_data[seek]);
	}

	void DSession::appendData(char* _ptr, int _length)
	{
		for (int seek = 0; _length > seek; ++seek)
			m_responseData.push_back(_ptr[seek]);
	}

	void DSession::appendData(std::vector<char>& _data)
	{
		int DataEOF = _data.size();
		for (int seek = 0; DataEOF > seek; ++seek)
			m_responseData.push_back(_data[seek]);
	}

	void DSession::setAcceptSocket(SOCKET _sock)
	{
		if (INVALID_SOCKET == _sock)
			return;

		if (INVALID_SOCKET == m_socket.getSocket())
			m_socket.setSocket(_sock);
	}
}
