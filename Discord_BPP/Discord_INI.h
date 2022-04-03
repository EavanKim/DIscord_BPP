#ifndef	DISCORD_INI_HPP__
#define DISCORD_INI_HPP__
/*
* ============================================================================================================
* Discord_INI
*
* 작업자 : EavanKim
*
* 용도 :
*	GitHub에 올리기 위험한 정보를 .gitignore에서 제외한 *.ini파일로 관리할 필요가 있음.
*	불러오기와 저장을 쉽게 하기 위해 객체화 해서 일관성있는 접근과 저장 수행
*
* 주의사항 :
*	.gitignore의 수정에 주의.
*	모든 ini파일은 git에 올라가선 안됩니다.
*
* 생명주기 :
*	1. Program 종속적
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