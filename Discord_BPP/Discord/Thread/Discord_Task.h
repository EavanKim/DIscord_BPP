#ifndef DISCORD_TASK_HPP__
#define DISCORD_TASK_HPP__

namespace Discord
{
	class DTask
	{
	public:
		explicit DTask();
		virtual ~DTask();

		void start();
		void stop();

		void set_Function(UINT(*_func)(void* _context));
		void set_Param(void* _param);

	private:
		void* m_param = nullptr;
		UINT(*m_func)(void* _context) = nullptr;
		HANDLE m_thread = INVALID_HANDLE_VALUE;
	};
}

#endif