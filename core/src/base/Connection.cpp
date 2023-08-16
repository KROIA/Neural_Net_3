#include "base/Connection.h"
#include "base/Neuron.h"

namespace NeuralNet
{
	Connection::Connection(Neuron* start, Neuron* destination)
		: m_start(start)
		, m_destination(destination)
		, m_weight(1)
	{

	}
	Connection* Connection::create(Neuron* start, Neuron* destination)
	{
		if (!start || !destination)
			return nullptr;
		return new Connection(start, destination);
	}

	Connection::~Connection()
	{
		if (m_start)
			Neuron::removeConnection(this);
		onDelete.emit(this);
	}


	Neuron* Connection::getStartNeuron() const
	{
		return m_start;
	}

	Neuron* Connection::getDestinationNeuron() const
	{
		return m_destination;
	}

	void Connection::setWeight(float w)
	{
		m_weight = w;
	}
	float Connection::getWeight() const
	{
		return m_weight;
	}
	float Connection::getWeightedSignal() const
	{
		return m_weight * m_start->getOutputValue();
	}
	float Connection::getSignal() const
	{
		return m_start->getOutputValue();
	}

	void Connection::disconnect()
	{
		Neuron::removeConnection(this);
		cleanup();
	}

	void Connection::cleanup()
	{
		m_start = nullptr;
		m_destination = nullptr;
	}

}