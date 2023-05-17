#include "OnlineNetwork.h"
#include "ServerENet.h"
#include "ClientENet.h"

OnlineNetwork* OnlineNetwork::onlineNetwork = new OnlineNetwork();

OnlineNetwork::OnlineNetwork()
{
	networkLayer = nullptr;
}

OnlineNetwork::~OnlineNetwork()
{
	OnNetworkSet.Clear();
	delete networkLayer;
}

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

void OnlineNetwork::LoadClient()
{
	if (networkLayer)return;
	networkLayer = new ClientENet("127.0.0.1", 1234);
	OnNetworkSet.Invoke();
}

void OnlineNetwork::LoadServer()
{
	if (networkLayer)return;
	networkLayer = new ServerENet(1234);
	OnNetworkSet.Invoke();
}
