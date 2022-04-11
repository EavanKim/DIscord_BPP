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