#ifndef DISCORD_BOT_SERVER_HPP__
#define DISCORD_BOT_SERVER_HPP__

namespace Discord
{
	class DBot_Server
	{
	public:
		explicit DBot_Server();
		~DBot_Server();

		// 봇 명령에 사용할 함수를 ThreadPool에서 사용할 수 있게 생성합니다.
		void CreateWorks();

		UINT Process(void* _context);

	private:
		SOCKET m_listenSocket;
	};
}

#endif