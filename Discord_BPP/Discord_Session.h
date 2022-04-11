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
		void Process();
		void doResponse();

		void setupData(char* _ptr, int _length);
		void setupData(std::vector<char>& _data);

		void appendData(char* _ptr, int _length);
		void appendData(std::vector<char>& _data);

		void setAcceptSocket(SOCKET _sock);

	private:
		std::vector<char> m_responseData;
		DSocket m_socket;
	};
}

#endif