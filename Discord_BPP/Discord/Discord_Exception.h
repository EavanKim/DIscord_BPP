#ifndef	DISCORD_EXCEPTION_HPP__
#define DISCORD_EXCEPTION_HPP__

namespace Discord
{
	class DException : public std::exception
	{
	public:
		explicit DException();
		explicit DException(uint64_t _code);
		virtual ~DException();

		DString ParseExceptionCode(uint64_t _code);

	private:
		uint64_t m_code;
		DString m_exceptionDescription = L"";
	};
}

#endif