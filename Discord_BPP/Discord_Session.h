#ifndef	DISCORD_SESSION_HPP__
#define DISCORD_SESSION_HPP__
/*
* ============================================================================================================
* Discord_Session
*
* �۾��� : EavanKim
*
* �뵵 :
*	Thread���� Socket�� �Բ� ������ ���� �����͸� �����صα� ���� ��ü.
*
* ���ǻ��� :
*	�������� �ϳ��� Thread�� �־�� ��.
*
* �����ֱ� :
*	1. ������ Program ������
*	2. ������ ��ɰ� Program ������(���� �߻����� ���α׷� ���ᰡ �ʿ��� ��� ����� ������ ����)
*
* ============================================================================================================
*/

namespace Discord
{
	class DSession : public DContext
	{
	public:
		explicit DSession();
		explicit DSession(SOCKET _sock);
		virtual ~DSession();

		void listenRequest();
		void doResponse();

		void setAcceptSocket(SOCKET _sock);

	private:
		DSocket m_socket;
	};
}

#endif