#ifndef	DISCORD_SESSION_HPP__
#define DISCORD_SESSION_HPP__
/*
* ============================================================================================================
* Discord_Session
*
* 작업자 : EavanKim
*
* 용도 :
*	Thread에서 Socket과 함께 동작을 위한 데이터를 저장해두기 위한 객체.
*
* 주의사항 :
*	소유권이 하나의 Thread에 있어야 함.
*
* 생명주기 :
*	1. 생성은 Program 종속적
*	2. 삭제는 명령과 Program 종속적(예외 발생으로 프로그램 종료가 필요한 경우 명령이 없더라도 삭제)
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