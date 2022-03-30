#ifndef DISCORD_WORK_HPP__
#define DISCORD_WORK_HPP__
#define USE_THREADPOOL 1

namespace Discord
{
#if USE_THREADPOOL
	class DWork
	{
	public:
		explicit DWork() {};
		virtual ~DWork() {};

		void start();
		void stop();

		DWORD getReturn();
		void setParam(LPVOID _lpParam);
		void setFunction(UINT(*m_func)(void* _lpParam));

	private:
		PTP_WORK m_pWorkItem = NULL;
		volatile LONG m_nCurrentTask = 0;
		UINT(*m_func)(void* _lpParam) = nullptr;
		DWORD m_return = 0;
		LPVOID m_Param = nullptr;
	};
#else
	class DWork
	{
	public:
		explicit DWork() {};
		virtual ~DWork() {};

		void start();
		void stop();

		DWORD getReturn();
		void setParam(LPVOID _lpParam);
		void setFunction(UINT(*m_func)(void* _lpParam));

	private:
		HANDLE m_thread = INVALID_HANDLE_VALUE;
		UINT m_threadID = 0;
		UINT(*m_func)(void* _lpParam) = nullptr;
		DWORD m_return = 0;
		LPVOID m_Param = nullptr;
	};
#endif
}

#endif