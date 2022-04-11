#ifndef DISCORD_DEFINES_HPP__
#define DISOCRD_DEFINES_HPP__

typedef volatile long DBOOL;
//DPtr ������ 32��Ʈ�� DPtr���ۿ� ������ ������ 32��Ʈ ������ �����մϴ�.
#ifndef _WIN64
typedef volatile __int32 DINT_PTR_T;
#else
typedef volatile __int64 DINT_PTR_T;
#endif
typedef volatile long long DINT_T;
typedef int64_t DINT;
typedef uint64_t DUINT;
typedef double DPOINT;
#if !USE_CUSTOM_STRING
typedef std::wstring DString;
typedef wchar_t DCHAR;

//https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
//snprintf�� ����� �� ���۸� �������� �ʰ� ������� ��� format ����� �ִ���̰� ��µǴµ�
//�̸� �̿��� ���� ���� ����� ���ؼ� ���� ���ڷ� ���� ��������� Ŀ��.
//%s�� ����ϴ� ��� �ſ� ���� ������� ���ڿ��� ȿ����.
template<typename ... Args>
static DString DPrintf(const std::wstring& _format, Args ... _args)
{
    
    int size_s = std::swprintf(nullptr, 0, _format.c_str(), _args ...) + 1;
    if (size_s <= 0)
    {
        throw std::runtime_error("Error during formatting.");
    }
    size_t size = static_cast<size_t>(size_s);
    std::unique_ptr<DCHAR[]> buf(new DCHAR[size]);
    std::swprintf(buf.get(), size, _format.c_str(), _args ...);
    return DString(buf.get(), buf.get() + size - 1);
}

#endif

#endif