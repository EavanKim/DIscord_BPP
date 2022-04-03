#ifndef	DISCORD_INCLUDE_HPP__
#define DISCORD_INCLUDE_HPP__

#include <iostream>
#include <vector>
#include <map>
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
//Singleton은 자체적인 context로 취급
//왜냐하면 Program이 실행되는 Process 종속적인 객체이기 때문
//Context를 상속하는 객체는 별도로 실행하는 Thread에 종속적인 대상만 관리
#include "Discord_Management.h"
#include "Thread/Discord_Work.h"
#include "Thread/Discord_Task.h"
#include "Server/Discord_Socket.h"
#include "Discord_Session.h"
#include "Discord_INI.h"
#include "Server/Discord_Bot_Server.h"

#endif