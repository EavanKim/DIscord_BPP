#ifndef	DISCORD_MANAGEMENT_HPP__
#define DISCORD_MANAGEMENT_HPP__

namespace Discord
{
	//Session별 Thread에서 Management로 상태값을 알려주거나,
	//Management에서 Session별 Thread로 전파해야 할 수 있으므로
	//Management의 모든 내용은 Thread-Safe해야함.
	//생성 삭제의 경우, Thread 분기 전을 기준으로 생성
	//삭제된 경우 모든 유관 Thread에서 Program이 종료되었다고 인지하고 모든 Thread가 종료되어야 함.
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