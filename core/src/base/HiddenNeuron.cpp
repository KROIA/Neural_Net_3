#include "base/HiddenNeuron.h"

namespace NeuralNet
{
	HiddenNeuron::HiddenNeuron(size_t id)
		: Neuron(id)
	{
		m_inputConnections = new std::vector<Connection*>();
		m_outputConnections = new std::vector<Connection*>();
	}
	HiddenNeuron::~HiddenNeuron()
	{
		
	}
}