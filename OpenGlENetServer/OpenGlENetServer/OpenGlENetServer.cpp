#include <iostream>
#include <enet/enet.h>
#include <conio.h>
#include "ENet.h"

int Getch_NoBlock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

int main()
{
    ENet* networkLayer = new ENet();
	if (!networkLayer->Initialize())
		return EXIT_FAILURE; 
	bool bContinue = true;
	std::cout << "Hello Enet!\n\n";
	std::cout << "press 1 for Client\n";
	std::cout << "press 2 for Server\n";

	char choice;
	std::cin >> choice;

	switch (choice)
	{
	case '1':
		networkLayer->SetupClient();
		networkLayer->ConnectClient();
		break;
	case '2':
		networkLayer->SetupServer();
		break;
	default:
		std::cout << "unknown choice !\n";
		break;
	}
	do
	{
		networkLayer->Update();
		int lastKey = Getch_NoBlock();
		if (lastKey < 0)
			continue;
		lastKey = toupper(lastKey);
		switch (lastKey)
		{
		case VK_ESCAPE:
			bContinue = false;
			break;
		case 'S':
			if (networkLayer->IsClient())
			{
				std::string myMsg = "UnMessageDeTest";
				std::cout << "Sending " << myMsg << " to the server.\n";

				networkLayer->SendPacket(false, myMsg.c_str());
			}
			else
			{
				std::string myMsg = "UnMessageDeTestBroadcast";
				std::cout << "Sending " << myMsg << " to all the clients.\n";

				networkLayer->BroadcastPacket(false, myMsg.c_str());
			}
			break;

		case 'Q':
			if (networkLayer->IsClientConnected())
			{
				networkLayer->DisconnectClient();
				std::cout << "Press R to reconnect the Client to the server\n";
			}
			break;

		case 'R':
			if (networkLayer->IsClient())
			{
				networkLayer->ConnectClient();
				std::cout << "Press Q to disconnect Client\n";
			}
			break;
		/*}
		default:
			break;*/
		}
	} while (bContinue);
	delete networkLayer;

	return 0;
}