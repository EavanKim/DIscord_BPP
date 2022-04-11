#include "pch.h"

//Exception Code
//1  Class
//2     
//3
//4
//5
//6
//7
//8

Discord::DException::DException()
    : m_code(0)
    , m_exceptionDescription(L"")
{
}

Discord::DException::DException(uint64_t _code)
    : m_code(_code)
    , m_exceptionDescription(ParseExceptionCode(_code))
{
}

Discord::DException::~DException()
{
}

DString Discord::DException::ParseExceptionCode(uint64_t _code)
{
    DString result = L"";

    switch (_code)
    {
    case 0x0100000000000000:
        break;
    default:
        result = L"Unknown";
        break;
    }

    return result;
}
