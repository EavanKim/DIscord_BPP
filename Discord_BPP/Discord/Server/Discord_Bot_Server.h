#ifndef DISCORD_BOT_SERVER_HPP__
#define DISCORD_BOT_SERVER_HPP__

namespace Discord
{
	class DBot_Server : public DContext
	{
	public:
		explicit DBot_Server(SOCKADDR_IN& _endPoint);
		~DBot_Server();

		static UINT Listen(void* _context);
		static VOID Process(_Inout_ PTP_CALLBACK_INSTANCE _instance, _Inout_opt_ PVOID _context);

	private:
		DINT_T m_listenEnable = 0;
		HANDLE m_thread;
		DSocket m_listen;
		WSADATA m_wsaData;
	};
}

#endif