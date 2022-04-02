#ifndef	DISCORD_SESSION_HPP__
#define DISCORD_SESSION_HPP__

namespace Discord
{
	class DSession : public DContext
	{
	public:
		explicit DSession();
		explicit DSession(SOCKET _sock);
		virtual ~DSession();

		void setAcceptSocket(SOCKET _sock);

	private:
		DSocket m_socket;
	};
}

#endif