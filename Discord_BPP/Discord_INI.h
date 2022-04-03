#ifndef	DISCORD_INI_HPP__
#define DISCORD_INI_HPP__

namespace Discord
{
	enum class INI_TYPE
	{

	};

	enum class INI_INFO_TYPE
	{
		UNKNOWN
		, INT
		, UINT
		, FLOAT
		, DOUBLE
		, STRING
		, WSTRING
	};

	//union은 생성자 소멸자 컨트롤이 제대로 될 수 없으므로 안에 문자열 객체를 사용할 수 없음.
	union INI_INFO_DATA
	{
	public:
		void* ptr; //string type은 void*로 다루기.
		int i;
		uint32_t ui;
		float f;
		double d;
	};

	class INI_INFO
	{
		bool m_isInitialized = false;
		INI_INFO_TYPE m_type = INI_INFO_TYPE::UNKNOWN;
		INI_INFO_DATA m_data = {};
	};

	class DINI : public DContext
	{
	public:
		explicit DINI(std::wstring _path);
		virtual ~DINI();

		void Load();
		void Save();

	private:
		std::wstring m_filePath;
		std::map<INI_TYPE, INI_INFO> m_data;
	};
}

#endif