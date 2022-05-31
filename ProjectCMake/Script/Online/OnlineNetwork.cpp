#include "OnlineNetwork.h"
#include "Input.h"
#include "ServerENet.h"
#include "ClientENet.h"

OnlineNetwork* OnlineNetwork::onlineNetwork = new OnlineNetwork();

void OnlineNetwork::SendPacket(NetType _netType, int flags, std::string _dataStr)
{
	if(networkLayer)
		networkLayer->SendBroadcastPacket(false, _netType, flags, _dataStr.c_str());
}

void OnlineNetwork::Update()
{
	if (!networkLayer) return;
	networkLayer->Update();
}

OnlineNetwork::OnlineNetwork()
{
	networkLayer = nullptr;
}

void OnlineNetwork::LoadClient()
{
	networkLayer = new ClientENet("127.0.0.1", 1234);
	OnNetworkSet.Invoke();
}

void OnlineNetwork::LoadServer()
{
	networkLayer = new ServerENet(1234);
	OnNetworkSet.Invoke();
}
