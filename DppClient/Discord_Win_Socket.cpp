#include "pch.h"

namespace Discord
{
    Discord_Win_Socket::Discord_Win_Socket()
    {
        setParam(this);
        setFunction(Discord_Win_Socket::wait);
    }

    Discord_Win_Socket::~Discord_Win_Socket()
    {
        stop();
    }

    void Discord_Win_Socket::connect()
    {
        start();
    }

    void Discord_Win_Socket::disconnect()
    {
        stop();
    }

    UINT Discord_Win_Socket::wait(void* _lpParam)
    {
        if (nullptr != _lpParam)
        {
            Discord_Win_Socket* SocketPtr = static_cast<Discord_Win_Socket*>(_lpParam);

            SocketPtr->read();
            SocketPtr->write();
        }
    }

    void Discord_Win_Socket::read()
    {
    }

    void Discord_Win_Socket::write()
    {
    }

    bool Discord_Win_Socket::isConnected()
    {
        return false;
    }
}
