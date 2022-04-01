#ifndef	DISCORD_SOCKET_HPP__
#define DISCORD_SOCKET_HPP__

namespace Discord
{
	class DSocket : public DContext
	{
	public:
		explicit DSocket();
		explicit DSocket(SOCKET _socket);
		virtual ~DSocket();

		void open();
		void close();

		void accespt(DSocket& _createdSocket);
		void listen();
		void talk();
		bool IsInvalid();

		void setSocket(SOCKET _socket);
		void setInfo(SOCKADDR_IN _connectInfo);

		SOCKET getSocket();
		SOCKADDR_IN getInfo();
		int getAddrlen();
		int getSessionReturn();

	private:
		int m_sessionreturn = 0;
		int m_addrlen = 0;
		SOCKET m_socket = INVALID_SOCKET;
		SOCKADDR_IN m_connectInfo = {};
		std::vector<char> m_data = {};
	};
}

#endif