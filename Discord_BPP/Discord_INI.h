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

	//union�� ������ �Ҹ��� ��Ʈ���� ����� �� �� �����Ƿ� �ȿ� ���ڿ� ��ü�� ����� �� ����.
	union INI_INFO_DATA
	{
	public:
		void* ptr; //string type�� void*�� �ٷ��.
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