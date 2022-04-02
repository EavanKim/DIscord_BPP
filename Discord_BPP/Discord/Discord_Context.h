#pragma once

namespace Discord
{
	enum class CONTEXT_TYPE
	{
		UNKNOWN
		, SERVER
		, SESSION
		, WORK
		, MAX
	};

	class DContext
	{
	public:
		explicit DContext();
		explicit DContext(CONTEXT_TYPE _type);
		virtual ~DContext();

		CONTEXT_TYPE getType();

	private:
		CONTEXT_TYPE m_type;
	};
}

