#include "pch.h"

namespace Discord
{
	DRefClass::DRefClass()
	{
	}

	DRefClass::~DRefClass()
	{
		if (0 != m_referenceCount)
			throw new DException(0xFFFFCCCCFFFFCCCC);
	}

	void DRefClass::Reference_Count_Increase()
	{
		InterlockedExchange64(&m_referenceCount, m_referenceCount + 1);
		OutputDebugStringW(DPrintf(L"ReferenceCheck Increase : %d \n", m_referenceCount).c_str());
	}

	void DRefClass::Reference_Count_Decrease()
	{
		InterlockedExchange64(&m_referenceCount, m_referenceCount - 1);
		OutputDebugStringW(DPrintf(L"ReferenceCheck Decrease : %d \n", m_referenceCount).c_str());
	}

	DINT_T DRefClass::Get_Reference_Count()
	{
		return m_referenceCount;
	}
}
