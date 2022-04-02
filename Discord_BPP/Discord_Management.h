#ifndef	DISCORD_MANAGEMENT_HPP__
#define DISCORD_MANAGEMENT_HPP__
/*
* ============================================================================================================
* Discord_Management
* 
* 작업자 : EavanKim
* 
* 용도 :
*	프로그램이 실행중인 시스템에서 프로그램에 명령을 내리거나 상태를 확인하기 위한 내용을 관리하는 객체
* 
* 주의사항 :
*	Thread-Safe가 유지되어야 함.
* 
* 생명주기 :
*	1. 생성은 Program 종속적
*	2. 삭제는 명령과 Program 종속적(예외 발생으로 프로그램 종료가 필요한 경우 명령이 없더라도 삭제)
* 
* ============================================================================================================
*/

namespace Discord
{
	class DManagement
	{
	public:


	private:
		explicit DManagement();
		~DManagement();

		static DManagement* m_Instnace;
	};
}

#endif