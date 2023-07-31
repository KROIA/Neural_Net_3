#include "nets/NeatNet.h"

namespace NeuralNet
{
	// GENOM

	NeatGenom::NeatGenom(size_t inputCount, size_t outputCount)
		: Genom("NeatGenom")
		, m_inputs(inputCount)
		, m_outputs(outputCount)
	{

	}
	NeatGenom::NeatGenom(const NeatGenom& other)
		: Genom(other)
		, m_inputs(other.m_inputs)
		, m_outputs(other.m_outputs)
	{

	}

	NeatGenom::~NeatGenom()
	{

	}

	COPY_FUNC_IMPL(NeatGenom);

	size_t NeatGenom::getInputs() const
	{
		return m_inputs;
	}
	size_t NeatGenom::getOutputs() const
	{
		return m_outputs;
	}

	void NeatGenom::clear()
	{
		m_connections.clear();
	}

	Json NeatGenom::toJson()
	{
		Json data({ "name",m_name });

		return data;
	}
	bool NeatGenom::fromJson(const Json& data)
	{
		return false;
	}

	bool NeatGenom::addConnection(const Connection& connection)
	{
		Connection* exists = getConnection(connection.getStartID(), connection.getDestinationID());
		if (exists) return false;
		m_connections.push_back(connection);
		return true;
	}
	NeatGenom::Connection* NeatGenom::getConnection(size_t startID, size_t destinationID)
	{
		for (size_t i = 0; i < m_connections.size(); ++i)
		{
			const Connection& con = m_connections[i];
			if (con.getStartID() == startID && con.getDestinationID() == destinationID)
				return &m_connections[i];
		}
		return nullptr;
	}
	const std::vector<NeatGenom::Connection>& NeatGenom::getConnections() const
	{
		return m_connections;
	}


	// CONNECTION

	NeatGenom::Connection::Connection()
		: m_startConnectionID(0)
		, m_destinationConnectionID(0)
		, m_weight(0)
		, m_enabled(false)
		, m_startNeuron(nullptr)
		, m_destinationNeuron(nullptr)
	{

	}
	NeatGenom::Connection::Connection(size_t startID, size_t destinationID,
									  float weight, bool enabled)
		: m_startConnectionID(startID)
		, m_destinationConnectionID(destinationID)
		, m_weight(weight)
		, m_enabled(enabled)
		, m_startNeuron(nullptr)
		, m_destinationNeuron(nullptr)
	{

	}
	NeatGenom::Connection::Connection(Neuron* start, Neuron* destination,
		float weight, bool enabled)
		: m_startConnectionID(0)
		, m_destinationConnectionID(0)
		, m_weight(weight)
		, m_enabled(enabled)
		, m_startNeuron(start)
		, m_destinationNeuron(destination)
	{
		if (m_startNeuron)
			m_startConnectionID = m_startNeuron->getID();
		if (m_destinationNeuron)
			m_destinationConnectionID = m_destinationNeuron->getID();
	}
	NeatGenom::Connection::Connection(const Connection& other)
		: m_startConnectionID(other.m_startConnectionID)
		, m_destinationConnectionID(other.m_destinationConnectionID)
		, m_weight(other.m_weight)
		, m_enabled(other.m_enabled)
		, m_startNeuron(other.m_startNeuron)
		, m_destinationNeuron(other.m_destinationNeuron)
	{

	}

	void NeatGenom::Connection::setStartID(size_t id)
	{
		m_startConnectionID = id;
	}
	size_t NeatGenom::Connection::getStartID() const
	{
		return m_startConnectionID;
	}

	void NeatGenom::Connection::setStartNeuron(Neuron* n)
	{
		m_startNeuron = n;
	}
	Neuron* NeatGenom::Connection::getStartNeuron() const
	{
		return m_startNeuron;
	}

	void NeatGenom::Connection::setDestinationID(size_t id)
	{
		m_destinationConnectionID = id;
	}
	size_t NeatGenom::Connection::getDestinationID() const
	{
		return m_destinationConnectionID;
	}

	void NeatGenom::Connection::setDestinationNeuron(Neuron* n)
	{
		m_destinationNeuron = n;
	}
	Neuron* NeatGenom::Connection::getDestinationNeuron() const
	{
		return m_destinationNeuron;
	}

	void NeatGenom::Connection::setWeight(float w)
	{
		m_weight = w;
	}
	float NeatGenom::Connection::getWeight() const
	{
		return m_weight;
	}

	void NeatGenom::Connection::setEnabled(bool enable)
	{
		m_enabled = enable;
	}
	bool NeatGenom::Connection::isEndabled() const
	{
		return m_enabled;
	}



	// NEAT NET

	NeatNet::NeatNet(size_t inputCount, size_t outputCount)
		: Net(inputCount, outputCount)
		, m_genom(inputCount, outputCount)
	{

	}
	NeatNet::NeatNet(const NeatNet& other)
		: Net(other)
		, m_genom(other.m_genom)
	{

	}

	COPY_FUNC_IMPL(NeatNet);

	bool NeatNet::setGenom(const NeatGenom& genom)
	{
		LOG_FUNC("start");

		if (m_genom.getInputs() != genom.getInputs() ||
			m_genom.getOutputs() != genom.getOutputs())
		{
			LOG("genom has not the same input/output count as this network");
			return false;
		}

		LOG("Clear neurons");
		for (size_t i = 0; i < m_neurons.size(); ++i)
			delete m_neurons[i];
		m_neurons.clear();
		m_genom.clear();

		std::vector<NeatGenom::Connection> connections = m_genom.getConnections();
		for (size_t i = 0; i < connections.size(); ++i)
		{
			addConnection(connections[i].getStartID(), connections[i].getDestinationID());
		}

		LOG_FUNC("end");
		return true;
	}

	bool NeatNet::addConnection(size_t startID, size_t destinationID)
	{
		Neuron* start = nullptr;
		Neuron* end = nullptr;



		return true;
	}

	void NeatNet::run()
	{

	}
}