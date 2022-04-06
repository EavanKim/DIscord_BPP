#ifndef	DISCORD_SOCKET_HPP__
#define DISCORD_SOCKET_HPP__
/*
* ============================================================================================================
* Discord_Socket
* 
* �۾��� : EavanKim
*
* �뵵 :
*	Server������ �ؾ��ϹǷ� �ʿ������� ����ϴ� ������ ���۰� ���� �� ���°����� ���� ��ü
*
* ���ǻ��� :
*	Discord_Context ���������� Thread-Safe���� �����鼭, Thread-Safe�� ���ǿ����� ���ư�����.
*	beginthreadex�� ������ Thread �ܺο��� �����Ǿ����� ������ Thread������ ���Ǵ� ���ǿ� ���� ����� ��Ȳ.
*
* �����ֱ� :
*	1. ������ Program ������
*	2. ������ ��ɰ� Program ������(���� �߻����� ���α׷� ���ᰡ �ʿ��� ��� ����� ������ ����)
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