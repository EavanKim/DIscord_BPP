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

	class DINI : public DContext
	{
	public:
		explicit DINI(DString _path);
		virtual ~DINI();

		void Load();
		void Save();

	private:
		DString m_filePath = L"";
		DString m_url = L"";
		DString m_publicKey = L"";
		DString m_applicationID = L"";
		DString m_tokenBot = L"";
		DString m_tokenCredentials = L"";
	};
}

#endif