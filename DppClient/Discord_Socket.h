#ifndef DISCORD_SOCKET_HPP__
#define DISCORD_SOCKET_HPP__

namespace Discord
{
	namespace Interface
	{
		class DSocket : public DWork
		{
		public:
			explicit DSocket() {};
			virtual ~DSocket() {};

			virtual void connect() = 0;
			virtual void disconnect() = 0;

			virtual void read() = 0;
			virtual void write() = 0;

			virtual bool isConnected() = 0;

		private:
			bool m_isConnected = false;
		};
	}
}

#endif