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
*	봇에서 변수를 저장하는 경우 이 객체를 통해 조회 가능
*	처음 규모가 작을때는 메모리만 사용하고, 내용이 커지고 규모가 커지면 SQL 도입.
*	Radis를 사용하는 방안도 검토 필요.
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
		static void Initialize_Manager();
		static DManagement* GetInstance();
		void Destroy();

		// Main Process Loop
		int run();

	private:
		explicit DManagement();
		~DManagement();

		void split(std::vector<std::wstring>& _result, std::wstring _string, wchar_t _Seperater);
		static void exit(DManageCommand* _param);
		static void start(DManageCommand* _param);
		static void stop(DManageCommand* _param);
		static void showInfo(DManageCommand* _param);

		std::map<std::wstring, void(*)(DManageCommand*)> m_commands = {};
		DBot_Server* m_server = nullptr;

		volatile long long m_state = 0;

		static DManagement* m_Instnace;
	};
}

#endif