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

	/*bool NeatGenom::addConnection(const Connection& connection)
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
		: m_startID(0)
		, m_destinationID(0)
		, m_weight(0)
		, m_enabled(false)
		, m_startNeuron(nullptr)
		, m_destinationNeuron(nullptr)
	{

	}
	NeatGenom::Connection::Connection(size_t startID, size_t destinationID,
									  float weight, bool enabled)
		: m_startID(startID)
		, m_destinationID(destinationID)
		, m_weight(weight)
		, m_enabled(enabled)
		, m_startNeuron(nullptr)
		, m_destinationNeuron(nullptr)
	{

	}
	NeatGenom::Connection::Connection(Neuron* start, Neuron* destination,
		float weight, bool enabled)
		: m_startID(0)
		, m_destinationID(0)
		, m_weight(weight)
		, m_enabled(enabled)
		, m_startNeuron(start)
		, m_destinationNeuron(destination)
	{
		if (m_startNeuron)
			m_startID = m_startNeuron->getID();
		if (m_destinationNeuron)
			m_destinationID = m_destinationNeuron->getID();
	}
	NeatGenom::Connection::Connection(const Connection& other)
		: m_startID(other.m_startID)
		, m_destinationID(other.m_destinationID)
		, m_weight(other.m_weight)
		, m_enabled(other.m_enabled)
		, m_startNeuron(other.m_startNeuron)
		, m_destinationNeuron(other.m_destinationNeuron)
	{

	}

	void NeatGenom::Connection::setStartID(size_t id)
	{
		m_startID = id;
	}
	size_t NeatGenom::Connection::getStartID() const
	{
		return m_startID;
	}

	void NeatGenom::Connection::setStartNeuron(Neuron* n)
	{
		m_startNeuron = n;
		if (m_startNeuron)
			m_startID = m_startNeuron->getID();
	}
	Neuron* NeatGenom::Connection::getStartNeuron() const
	{
		return m_startNeuron;
	}

	void NeatGenom::Connection::setDestinationID(size_t id)
	{
		m_destinationID = id;
	}
	size_t NeatGenom::Connection::getDestinationID() const
	{
		return m_destinationID;
	}

	void NeatGenom::Connection::setDestinationNeuron(Neuron* n)
	{
		m_destinationNeuron = n;
		if (m_destinationNeuron)
			m_destinationID = m_destinationNeuron->getID();
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
	}*/

	NeatGenom::NeatConnection::NeatConnection(size_t startID, size_t destinationID,
		float weight, bool enabled)
		: m_isEnabled(enabled)
		, m_startID(startID)
		, m_destinationID(destinationID)
		, m_connection(nullptr)
		, m_weight(weight)
	{

	}
	
	NeatGenom::NeatConnection::~NeatConnection()
	{

	}


	void NeatGenom::NeatConnection::setStartID(size_t id)
	{
		m_startID = id;
	}
	size_t NeatGenom::NeatConnection::getStartID() const
	{
		return m_startID;
	}

	void NeatGenom::NeatConnection::setDestinationID(size_t id)
	{
		m_destinationID = id;
	}
	size_t NeatGenom::NeatConnection::getDestinationID() const
	{
		return m_destinationID;
	}


	void NeatGenom::NeatConnection::setWeight(float w)
	{
		m_weight = w;
	}
	float NeatGenom::NeatConnection::getWeight() const
	{
		return m_weight;
	}

	void NeatGenom::NeatConnection::setEnabled(bool en)
	{
		if (m_isEnabled == en)
			return;
		m_isEnabled = en;
		if (!m_connection)
			return;
		if (m_isEnabled)
			Neuron::addConnection(m_connection);
		else
			Neuron::removeConnection(m_connection);
	}
	bool NeatGenom::NeatConnection::isEnabled() const
	{
		return m_isEnabled;
	}

	
	void NeatGenom::NeatConnection::setConnection(Connection* con)
	{
		m_connection = con;
		if(m_connection)
			m_connection->onDelete.connect_member(this, &NeatGenom::NeatConnection::onConnectionDeleted);
	}
	Connection* NeatGenom::NeatConnection::getConnection() const
	{
		return m_connection;
	}
	void NeatGenom::NeatConnection::onConnectionDeleted(Connection* con)
	{
		if(m_connection == con)
			m_connection = nullptr;
	}
	bool NeatGenom::addConnection(NeatConnection* connection)
	{
		m_connections.push_back(connection);
		return true;
	}
	const std::vector<NeatGenom::NeatConnection*>& NeatGenom::getConnections() const
	{
		return m_connections;
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

		bool success = true;
		const std::vector<NeatGenom::NeatConnection*> &connections = genom.getConnections();
		for (size_t i = 0; i < connections.size(); ++i)
		{
			NeatGenom::NeatConnection* con = addConnection(connections[i]->getStartID(), 
														   connections[i]->getDestinationID(),
														   connections[i]->getWeight(), 
														   connections[i]->isEnabled());
			if (!con)
				success = false;
		}

		LOG_FUNC("end");
		return success;
	}

	NeatGenom::NeatConnection* NeatNet::addConnection(size_t startID, size_t destinationID, float weight, bool enable)
	{
		Neuron* start = getNeuron(startID);
		Neuron* end = getNeuron(destinationID);

		if (!start || !end)
			goto error;

		NeatGenom::NeatConnection *con = new NeatGenom::NeatConnection(startID, destinationID, weight, enable);
		Connection* connection = Connection::create(start, end);
		con->setConnection(connection);

		if(enable)
		if (!Neuron::addConnection(connection))
		{
			delete con;
			delete connection;
			goto error;
		}

		if (!m_genom.addConnection(con))
		{
			delete con;
			delete connection;
			goto error;
		}
		m_genom.addConnection(con);
		return con;

		error:
		LOG("Can't create connection from neuron: " + std::to_string(startID) +
			" to " + std::to_string(destinationID) +
			" with weight: " + std::to_string(weight));
		return nullptr;
	}

	void NeatNet::run()
	{

	}
	Neuron* NeatNet::getNeuron(size_t id)
	{
		for (auto& n : m_neurons)
			if (n->getID() == id)
				return n;
		return nullptr;
	}
}