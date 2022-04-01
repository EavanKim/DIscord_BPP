#ifndef	DISCORD_INCLUDE_HPP__
#define DISCORD_INCLUDE_HPP__

#include <vector>
#include <unordered_map>
#include <stdint.h>

#include <WinSock2.h>
#include <Windows.h>
#include <process.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")

#include "Discord_Defines.h"
#include "Discord_Exception.h"
#include "Discord_Context.h"
#include "Thread/Discord_Work.h"
#include "Thread/Discord_Task.h"
#include "Server/Discord_Socket.h"
#include "Server/Discord_Bot_Server.h"

#endif