#include "pch.h"
#include <fstream>

namespace Discord
{
	INI_INFO::INI_INFO()
		: m_isInitialized(false)
		, m_type(INI_INFO_TYPE::UNKNOWN)
	{

	}

	INI_INFO::INI_INFO(int _integer)
		: m_isInitialized(true)
		, m_type(INI_INFO_TYPE::INT)
	{
		ZeroMemory(&m_data, sizeof(INI_INFO_DATA));
		m_data.i = _integer;
	}

	INI_INFO::INI_INFO(unsigned int _unsignedinterger)
		: m_isInitialized(true)
		, m_type(INI_INFO_TYPE::UINT)
	{
		ZeroMemory(&m_data, sizeof(INI_INFO_DATA));
		m_data.ui = _unsignedinterger;
	}

	INI_INFO::INI_INFO(float _singlefloating)
		: m_isInitialized(true)
		, m_type(INI_INFO_TYPE::FLOAT)
	{
		ZeroMemory(&m_data, sizeof(INI_INFO_DATA));
		m_data.f = _singlefloating;
	}

	INI_INFO::INI_INFO(double _doublefloating)
		: m_isInitialized(true)
		, m_type(INI_INFO_TYPE::DOUBLE)
	{
		ZeroMemory(&m_data, sizeof(INI_INFO_DATA));
		m_data.d = _doublefloating;
	}

	INI_INFO::INI_INFO(char* _string)
		: m_isInitialized(true)
		, m_type(INI_INFO_TYPE::STRING)
	{
		ZeroMemory(&m_data, sizeof(INI_INFO_DATA));
		m_data.ptr = _string;
	}

	INI_INFO::INI_INFO(wchar_t* _unicodestring)
		: m_isInitialized(true)
		, m_type(INI_INFO_TYPE::WSTRING)
	{
		ZeroMemory(&m_data, sizeof(INI_INFO_DATA));
		m_data.ptr = (void*)_unicodestring;
	}

	INI_INFO::~INI_INFO()
	{
		if (m_isInitialized)
		{
			if ((INI_INFO_TYPE::STRING == m_type) || (INI_INFO_TYPE::WSTRING == m_type))
			{
				delete m_data.ptr;
				m_data.ptr = nullptr;
			}
		}
	}

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
			std::map<INI_TYPE, INI_INFO>::iterator dataIter = m_data.begin();
			std::map<INI_TYPE, INI_INFO>::iterator dataEnd = m_data.end();
			for (; dataIter != dataEnd; ++dataIter)
			{
				size_t dataCount = 0;
				size_t dataSize = 0;

				if (dataIter->second.m_isInitialized)
				{
					switch (dataIter->second.m_type)
					{
					case INI_INFO_TYPE::INT:
						stream << dataIter->second.m_data.i;
						break;
					case INI_INFO_TYPE::UINT:
						stream << dataIter->second.m_data.i;
						break;
					case INI_INFO_TYPE::FLOAT:
						stream << dataIter->second.m_data.i;
						break;
					case INI_INFO_TYPE::DOUBLE:
						stream << dataIter->second.m_data.i;
						break;
					case INI_INFO_TYPE::STRING:
						stream << std::string((char*)dataIter->second.m_data.ptr).c_str();
						break;
					case INI_INFO_TYPE::WSTRING:
						stream << std::wstring((wchar_t*)dataIter->second.m_data.ptr).c_str();
						break;
					default:
						continue;
					}
					stream << std::endl;
				}
				else
				{
					stream << std::endl;
				}
			}

			stream.close();
			fclose(targetFile);
		}
	}
}
