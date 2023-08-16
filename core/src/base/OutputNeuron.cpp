#include "base/OutputNeuron.h"

namespace NeuralNet
{
	OutputNeuron::OutputNeuron(size_t id)
		: Neuron(id)
	{
		m_outputConnections = new std::vector<Connection*>();
	}

	OutputNeuron::~OutputNeuron()
	{

	}


}