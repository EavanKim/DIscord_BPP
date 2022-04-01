#ifndef	DISCORD_INCLUDE_HPP__
#define DISCORD_INCLUDE_HPP__

#include <vector>
#include <unordered_map>
#include <stdint.h>


#include <windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "Discord_Defines.h"
#include "Discord_Exception.h"
#include "Discord_Context.h"
#include "Discord_Work.h"
#include "Discord_Task.h"
#include "Discord_Socket.h"
#include "Discord_Bot_Server.h"

#endif