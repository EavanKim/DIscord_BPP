#ifndef DISCORD_WORK_HPP__
#define DISCORD_WORK_HPP__

namespace Discord
{
	class DWork
	{
	public:
		explicit DWork();
		virtual ~DWork();

		void start();

		void setParam(LPVOID _lpParam);
		void setFunction(VOID(NTAPI* _func)(_Inout_ PTP_CALLBACK_INSTANCE _instance, _Inout_opt_ PVOID _context, _Inout_ PTP_WORK _work));

	private:
		PTP_WORK m_pWorkItem = NULL;
		volatile LONG m_nCurrentTask = 0;
		VOID(NTAPI* m_func)(_Inout_ PTP_CALLBACK_INSTANCE _instance, _Inout_opt_ PVOID _context, _Inout_ PTP_WORK _work) = nullptr;
		LPVOID m_Param = nullptr;
	};
}

#endif