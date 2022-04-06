#ifndef	DISCORD_SOCKET_HPP__
#define DISCORD_SOCKET_HPP__
/*
* ============================================================================================================
* Discord_Socket
* 
* 작업자 : EavanKim
*
* 용도 :
*	Server동작을 해야하므로 필연적으로 사용하는 소켓의 시작과 종료 및 상태관리를 위한 객체
*
* 주의사항 :
*	Discord_Context 종속적으로 Thread-Safe하지 않으면서, Thread-Safe한 조건에서만 돌아가야함.
*	beginthreadex로 생성된 Thread 외부에서 생성되었지만 생성된 Thread에서만 사용되는 조건에 의한 모순적 상황.
*
* 생명주기 :
*	1. 생성은 Program 종속적
*	2. 삭제는 명령과 Program 종속적(예외 발생으로 프로그램 종료가 필요한 경우 명령이 없더라도 삭제)
*
* ============================================================================================================
*/

namespace Discord
{
	class DSocket : public DContext
	{
	public:
		explicit DSocket();
		explicit DSocket(SOCKET _socket);
		virtual ~DSocket();

		void open();
		void listen();
		void close();

		SOCKET accespt();
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