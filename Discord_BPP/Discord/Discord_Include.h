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
//Singleton�� ��ü���� context�� ���
//�ֳ��ϸ� Program�� ����Ǵ� Process �������� ��ü�̱� ����
//Context�� ����ϴ� ��ü�� ������ �����ϴ� Thread�� �������� ��� ����
#include "Discord_Management.h"
#include "Thread/Discord_Work.h"
#include "Thread/Discord_Task.h"
#include "Server/Discord_Socket.h"
#include "Discord_Session.h"
#include "Discord_INI.h"
#include "Server/Discord_Bot_Server.h"

#endif