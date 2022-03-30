#ifndef DISCORD_DEFINES_HPP__
#define DISOCRD_DEFINES_HPP__

#include <windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "Discord_Work.h"
#include "Discord_Socket.h"
#include "Discord_Win_Socket.h"

#endif