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


	private:
		explicit DManagement();
		~DManagement();

		static DManagement* m_Instnace;
	};
}

#endif