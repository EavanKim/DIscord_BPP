#ifndef	DISCORD_MANAGEMENT_HPP__
#define DISCORD_MANAGEMENT_HPP__
/*
* ============================================================================================================
* Discord_Management
* 
* �۾��� : EavanKim
* 
* �뵵 :
*	���α׷��� �������� �ý��ۿ��� ���α׷��� ����� �����ų� ���¸� Ȯ���ϱ� ���� ������ �����ϴ� ��ü
*	������ ������ �����ϴ� ��� �� ��ü�� ���� ��ȸ ����
*	ó�� �Ը� �������� �޸𸮸� ����ϰ�, ������ Ŀ���� �Ը� Ŀ���� SQL ����.
*	Radis�� ����ϴ� ��ȵ� ���� �ʿ�.
* 
* ���ǻ��� :
*	Thread-Safe�� �����Ǿ�� ��.
* 
* �����ֱ� :
*	1. ������ Program ������
*	2. ������ ��ɰ� Program ������(���� �߻����� ���α׷� ���ᰡ �ʿ��� ��� ����� ������ ����)
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