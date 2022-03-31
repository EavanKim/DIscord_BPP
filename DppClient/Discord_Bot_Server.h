#ifndef DISCORD_BOT_SERVER_HPP__
#define DISCORD_BOT_SERVER_HPP__

namespace Discord
{
	class DBot_Server
	{
	public:
		explicit DBot_Server();
		~DBot_Server();

		// �� ��ɿ� ����� �Լ��� ThreadPool���� ����� �� �ְ� �����մϴ�.
		void CreateWorks();

		UINT Process(void* _context);

	private:
		SOCKET m_listenSocket;
	};
}

#endif