#ifndef	DISCORD_MANAGEMENT_HPP__
#define DISCORD_MANAGEMENT_HPP__

namespace Discord
{
	//Session�� Thread���� Management�� ���°��� �˷��ְų�,
	//Management���� Session�� Thread�� �����ؾ� �� �� �����Ƿ�
	//Management�� ��� ������ Thread-Safe�ؾ���.
	//���� ������ ���, Thread �б� ���� �������� ����
	//������ ��� ��� ���� Thread���� Program�� ����Ǿ��ٰ� �����ϰ� ��� Thread�� ����Ǿ�� ��.
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