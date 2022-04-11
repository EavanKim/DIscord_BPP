#ifndef DISCORD_DEFINES_HPP__
#define DISOCRD_DEFINES_HPP__

typedef volatile long DBOOL;
//DPtr 때문에 32비트는 DPtr동작에 문제가 없도록 32비트 변수로 변경합니다.
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
//snprintf를 사용할 때 버퍼를 지정하지 않고 사용했을 경우 format 결과물 최대길이가 출력되는데
//이를 이용해 가변 버퍼 사이즈를 정해서 가변 인자로 인한 가변사이즈를 커버.
//%s를 사용하는 경우 매우 많이 길어지는 문자열에 효과적.
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