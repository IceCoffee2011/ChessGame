#include "ChessServer.h"
#include <iostream>

#ifdef WIN32
#include <winsock2.h>
#endif

int main()
{
#ifdef WIN32
    WSAData data ;
    WSAStartup(MAKEWORD(2,2), &data);
#endif

    g_pChessServer->StartRun ();

    return 0;
}
