#ifndef	DISCORD_MANAGEMENT_COMMAND_HPP__
#define DISCORD_MANAGEMENT_COMMAND_HPP__

namespace Discord
{
	class DManageCommand
	{
	public:
		explicit DManageCommand();
		explicit DManageCommand(std::vector<DString> _params);
		virtual ~DManageCommand();

	private:
		std::vector<DString> m_inputParam;
	};
}

#endif