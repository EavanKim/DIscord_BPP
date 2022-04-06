#include "pch.h"

namespace Discord
{
	DINI::DINI(std::wstring _path)
		: m_filePath(_path)
	{
	}

	DINI::~DINI()
	{
	}

	void DINI::Load()
	{
		std::wifstream stream(m_filePath);

		if (stream.is_open())
		{
			std::getline(stream, m_url);
			std::getline(stream, m_publicKey);
			std::getline(stream, m_applicationID);
			std::getline(stream, m_tokenBot);
			std::getline(stream, m_tokenCredentials);
			stream.close();
		}
	}

	void DINI::Save()
	{
		std::wofstream stream(m_filePath);

		if (stream.is_open())
		{
			stream << m_url << std::endl;
			stream << m_publicKey << std::endl;
			stream << m_applicationID << std::endl;
			stream << m_tokenBot << std::endl;
			stream << m_tokenCredentials << std::endl;
			stream.close();
		}
	}
}
