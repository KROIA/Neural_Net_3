#include "NeuralNet.h"

int main(void)
{
	Log::ConsoleLogger logger;
	logger.log("Test1");
	//NeuralNet::Net net(2,1);

	NeuralNet::NeatNet net(0,0);
	net.copy();

	getchar();
	return 0;
}