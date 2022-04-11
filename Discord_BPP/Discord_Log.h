#ifndef	DISCORD_LOG_HPP__
#define DISCORD_LOG_HPP__

namespace Discord
{
	enum class LOG_LEVEL
	{
		LOG_UNKNOWN
		, LOG_DEBUG
		, LOG_RELEASE
	};

	enum class LOG_TYPE
	{
		LOG_UNKNOWN
		, LOG_INFO
		, LOG_WARNING
		, LOG_ERROR
	};

	class DLog;
	class DLogContext : public DContext
	{
	public:
		explicit DLogContext(DString _string)
			: DContext(CONTEXT_TYPE::LOG)
			, m_logString(_string)
		{

		}

		~DLogContext()
		{
		}

		DString m_logString;
	};

	class DLog : public DRefClass
	{
	public:
		static void Initialize(DString _path, DString _fileName, DString _extention = L"log");
		static DRef_Ptr<DLog> GetInstance();
		static void Destroy();

		void printf(DString _log);
		static UINT printf_internal(void* _context);
		static UINT update(void* _context);

	private:
		explicit DLog();
		explicit DLog(DString _path, DString _fileName, DString _extention = L"log");
		virtual ~DLog();

		DBOOL m_barrier = 0;
		DBOOL m_state = 0;
		DString m_savePath = L"";
		DString m_saveFileName = L"";
		DString m_extentions = L"";
		std::vector<DString> m_logs = {};

		HANDLE m_updateThread = INVALID_HANDLE_VALUE;
		static DRef_Ptr<DLog> m_instance;
	};
}

#endif