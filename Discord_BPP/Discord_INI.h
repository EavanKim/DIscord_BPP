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

	class DINI : public DContext
	{
	public:
		explicit DINI(std::wstring _path);
		virtual ~DINI();

		void Load();
		void Save();

	private:
		std::wstring m_filePath = L"";
		std::wstring m_url = L"";
		std::wstring m_publicKey = L"";
		std::wstring m_applicationID = L"";
		std::wstring m_tokenBot = L"";
		std::wstring m_tokenCredentials = L"";
	};
}

#endif