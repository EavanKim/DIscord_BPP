#ifndef	DISCORD_CONTEXT_HPP__
#define DISCORD_CONTEXT_HPP__
/*
* ============================================================================================================
* Discord_Context
* 
* 작업자 : EavanKim
*
* 용도 :
*	beginthreadex를 통해 생성되는 Thread에 넘겨주는 Heap 메모리 덩어리
*	생성된 Thread에 종속적인 대상.
*
* 주의사항 :
*	Thread 종속적이지 않은 대상을 넣지 않을 것.
*	하나 이상의 Thread에 종속적이라면 Singleton을 사용하고 Thread-Safe함을 보장할 것.
*	함수형을 사용해 값복사를 늘리는 것은 연산만 더 사용하고 더 많은 메모리를 사용하게 되고
*	메모리가 매 올바른 순간에 지워지고 있는지 관리를 어렵게 함
*	머신을 비싸게 사용해서 해결하는 것은 소규모로 사용하게되는 '개인 프로젝트'의 덕목도 아니며,
*	프로그램을 하는 사람이 아니라 수학자가 프로그램 관리를 할 이유가 없기때문에 수학자로서 하는 일이라 생각
*
* 생명주기 :
*	1. Context 생성은 Program 종속적
*	2. 삭제는 Thread와 Program 종속적(예외 발생으로 프로그램 종료가 필요한 경우 명령이 없더라도 삭제)
*
* ============================================================================================================
*/

namespace Discord
{
	enum class CONTEXT_TYPE
	{
		UNKNOWN
		, SERVER
		, SESSION
		, WORK
		, MAX
	};

	class DContext
	{
	public:
		explicit DContext();
		explicit DContext(CONTEXT_TYPE _type);
		virtual ~DContext();

		CONTEXT_TYPE getType();

	private:
		CONTEXT_TYPE m_type;
	};
}

#endif