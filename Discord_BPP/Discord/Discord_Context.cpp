#include "pch.h"
#include "Discord_Context.h"

namespace Discord
{
	DContext::DContext()
		: m_type(CONTEXT_TYPE::UNKNOWN)
	{
	}

	DContext::DContext(CONTEXT_TYPE _type)
		: m_type(_type)
	{
	}

	DContext::~DContext()
	{
	}
	CONTEXT_TYPE DContext::getType()
	{
		return m_type;
	}
}
