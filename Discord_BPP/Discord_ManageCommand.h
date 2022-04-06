#ifndef	DISCORD_MANAGEMENT_COMMAND_HPP__
#define DISCORD_MANAGEMENT_COMMAND_HPP__

namespace Discord
{
	class DManageCommand
	{
	public:
		explicit DManageCommand();
		explicit DManageCommand(std::vector<std::wstring> _params);
		virtual ~DManageCommand();

	private:
		std::vector<std::wstring> m_inputParam;
	};
}

#endif