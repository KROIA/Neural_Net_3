#include "base/InputNeuron.h"

namespace NeuralNet
{
	InputNeuron::InputNeuron(size_t id)
		: Neuron(id)
	{
		m_outputConnections = new std::vector<Connection*>();
	}

	InputNeuron::~InputNeuron()
	{

	}

	void InputNeuron::setInput(float value)
	{
		m_outputValue = value;
		m_netinputValue = value;
	}
	float InputNeuron::getInput() const
	{
		return m_outputValue;
	}

	void InputNeuron::run()
	{

	}

}