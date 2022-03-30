#ifndef DISCORD_WIN_SOCKET_HPP__
#define DISCORD_WIN_SOCKET_HPP__

namespace Discord
{
	class Discord_Win_Socket : public Discord::Interface::DSocket
	{
	public:
		explicit Discord_Win_Socket();
		virtual ~Discord_Win_Socket();

		// Socket을(를) 통해 상속됨
		virtual void connect();
		virtual void disconnect();

		static UINT WINAPI wait(void* _lpParam);

		virtual void read();
		virtual void write();

		virtual bool isConnected();

	private:
		WSADATA m_wsaData;
		addrinfo m_connectInfo;
		SOCKET m_socket = INVALID_SOCKET;
	};
}

#endif