#include "pch.h"
#include <fstream>

namespace Discord
{
	DINI::DINI(std::wstring _path)
	{
	}

	DINI::~DINI()
	{
	}

	void DINI::Load()
	{

	}

	void DINI::Save()
	{
		FILE* targetFile = nullptr;
		errno_t error = _wfopen_s(&targetFile, m_filePath.c_str(), L"wb+");
		if (0 == error)
		{
			std::wofstream stream(targetFile);

			stream.close();
			fclose(targetFile);
		}
	}
}
