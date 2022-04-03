#ifndef	DISCORD_INI_HPP__
#define DISCORD_INI_HPP__
/*
* ============================================================================================================
* Discord_INI
*
* �۾��� : EavanKim
*
* �뵵 :
*	GitHub�� �ø��� ������ ������ .gitignore���� ������ *.ini���Ϸ� ������ �ʿ䰡 ����.
*	�ҷ������ ������ ���� �ϱ� ���� ��üȭ �ؼ� �ϰ����ִ� ���ٰ� ���� ����
*
* ���ǻ��� :
*	.gitignore�� ������ ����.
*	��� ini������ git�� �ö󰡼� �ȵ˴ϴ�.
*
* �����ֱ� :
*	1. Program ������
*
* ============================================================================================================
*/

namespace Discord
{
	enum class INI_TYPE
	{
		URL
		, PUBLIC_KEY
		, APPLICATION_ID
		, TOKEN_BOT
		, TOKEN_CREDENTIALS
		, MAX
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
		, MAX
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
	public:
		explicit INI_INFO();
		explicit INI_INFO(int _integer);
		explicit INI_INFO(unsigned int _unsignedinterger);
		explicit INI_INFO(float _singlefloating);
		explicit INI_INFO(double _doublefloating);
		explicit INI_INFO(char* _string);
		explicit INI_INFO(wchar_t* _unicodestring);
		~INI_INFO();

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