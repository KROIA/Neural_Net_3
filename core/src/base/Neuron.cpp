#include "base/Neuron.h"
#include "utilities/RandomEngine.h"
#include "base/Connection.h"


namespace NeuralNet
{
	Neuron::Neuron(size_t id)
		: m_outputValue(0)
		, m_netinputValue(0)
		//, m_inputCount(0)
		, m_activationType(Activation::Type::linear)
		, m_activationFunction(Activation::getActivationFunction(m_activationType))
		, m_id(id)
		, m_inputConnections(nullptr)
		, m_outputConnections(nullptr)
	{

	}
	/*Neuron::Neuron(const Neuron& other)
		:// m_inputValues(other.m_inputValues)
		//, m_weights(other.m_weights)
		 m_outputValue(other.m_outputValue)
		, m_netinputValue(other.m_netinputValue)
		//, m_inputCount(other.m_inputCount)
		, m_activationType(other.m_activationType)
		, m_activationFunction(other.m_activationFunction)
		, m_id(other.m_id)
	{

	}*/
	Neuron::~Neuron()
	{
		if (m_inputConnections)
		{
			for (size_t i = 0; i < m_inputConnections->size(); ++i)
			{
				delete (*m_inputConnections)[i];
			}
			delete m_inputConnections;
			m_inputConnections = nullptr;
		}
		if (m_outputConnections)
		{
			for (size_t i = 0; i < m_outputConnections->size(); ++i)
			{
				delete (*m_outputConnections)[i];
			}
			delete m_outputConnections;
			m_outputConnections = nullptr;
		}		
	}

	//COPY_FUNC_IMPL(Neuron);

	void Neuron::setID(size_t id)
	{
		m_id = id;
	}
	size_t Neuron::getID() const
	{
		return m_id;
	}

	/*void Neuron::setInputCount(size_t count)
	{
		size_t currentCount = m_inputValues.size();
		if (count == currentCount)
			return;
		m_inputValues.resize(count);
		//m_weights.resize(count);
		if (count > currentCount)
		{
			size_t countBytes = (count - currentCount) * sizeof(float);
			memset(m_inputValues.data() + currentCount, 0, countBytes);
			for (size_t i = currentCount; i < count; ++i)
				m_weights[i] = Utilities::RandomEngine::getFloat(-1, 1);
		}
		m_inputCount = count;
	}*/
	size_t Neuron::getInputCount() const
	{
		if (m_inputConnections)
			return m_inputConnections->size();
		return 0;
	}
	/*
	void Neuron::setInputValue(const std::vector<float>& values)
	{
		if (values.size() == m_inputCount)
		{
			m_inputValues = values;
			return; 
		}
		size_t min = std::min(values.size(), m_inputCount);
		m_inputValues.insert(m_inputValues.begin(), values.begin(), values.begin() + min);
	}
	void Neuron::setInputValue(size_t input, float value)
	{
		if (input >= m_inputCount)
			return;
		m_inputValues[input] = value;
	}
	*/
	std::vector<float> Neuron::getInputValue() const
	{
		if (m_inputConnections)
		{
			std::vector<float> values(m_inputConnections->size(), 0);
			for (size_t i = 0; i < m_inputConnections->size(); ++i)
				values[i] = (*m_inputConnections)[i]->getSignal();
			return values;
		}
		return std::vector<float>();
	}
	float Neuron::getInputValue(size_t input) const
	{
		if (m_inputConnections)
		{
			if (m_inputConnections->size() > input)
			{
				return (*m_inputConnections)[input]->getSignal();
			}
		}
		return 0;
	}

	void Neuron::setWeight(const std::vector<float>& weights)
	{
		if (m_inputConnections)
		{
			size_t min = std::min(weights.size(), m_inputConnections->size());
			for (size_t i = 0; i < min; ++i)
				(*m_inputConnections)[i]->setWeight(weights[i]);
		}
	}
	void Neuron::setWeight(size_t input, float weight)
	{
		if (m_inputConnections)
		{
			if (m_inputConnections->size() > input)
			{
				(*m_inputConnections)[input]->setWeight(weight);
			}
		}
	}
	std::vector<float> Neuron::getWeight() const
	{
		if (m_inputConnections)
		{
			std::vector<float> w(m_inputConnections->size(), 0);
			for (size_t i = 0; i < m_inputConnections->size(); ++i)
				w[i] = (*m_inputConnections)[i]->getWeight();
			return w;
		}
		return std::vector<float>();
	}
	float Neuron::getWeight(size_t input) const
	{
		if (m_inputConnections)
		{
			if (m_inputConnections->size() > input)
			{
				return (*m_inputConnections)[input]->getWeight();
			}
		}
	}

	Connection* Neuron::addConnectionTo(Neuron* destination)
	{
		if (!destination)
			return nullptr;
		if (isConnectedTo(destination))
			return nullptr;
		Connection* con = Connection::create(this, destination);
		if (!con)
			return false;
		if (!addConnection(con))
		{
			con->cleanup();
			delete con;
			con = nullptr;
		}
		return con;
	}
	bool Neuron::removeConnectionTo(Neuron* destination)
	{
		if (!destination)
			return false;
		Connection* toDelete = nullptr;
		if (!m_inputConnections)
			return false;
		for (size_t i = 0; i < m_inputConnections->size(); ++i)
		{
			if ((*m_inputConnections)[i]->getStartNeuron() == this)
			{
				toDelete = (*m_inputConnections)[i];
				break;
			}
		}
		delete toDelete;
		return false;
	}
	bool Neuron::removeConnection(Connection* con)
	{
		Neuron* start = con->getStartNeuron();
		Neuron* destination = con->getDestinationNeuron();
		if (!start || !destination)
			return false;

		std::vector<Connection*>* inputs = destination->m_inputConnections;
		std::vector<Connection*>* outputs = start->m_outputConnections;

		if (!inputs || !outputs)
			return false;

		for (size_t i = 0; i < inputs->size(); ++i)
		{
			if ((*inputs)[i] == con)
			{
				inputs->erase(inputs->begin() + i);
				break;
			}
		}
		

		for (size_t i = 0; i < outputs->size(); ++i)
		{
			if ((*outputs)[i] == con)
			{
				outputs->erase(outputs->begin() + i);
				break;
			}
		}
		
		return true;
	}
	bool Neuron::addConnection(Connection* con)
	{
		if (!con)
			return false;
		Neuron* start = con->getStartNeuron();
		Neuron* dest = con->getDestinationNeuron();
		if (start->isConnectedTo(dest))
			return false;
		if (!dest->m_inputConnections || !start->m_outputConnections)
			return false;

		dest->m_inputConnections->push_back(con);
		start->m_outputConnections->push_back(con);
		return true;
	}
	bool Neuron::isConnectedTo(Neuron* destination) const
	{
		if (!destination)
			return false;
		std::vector<Connection*>* connections = destination->m_outputConnections;
		if (!connections)
			return false;
		for (auto& con : *connections)
		{
			if (con->getStartNeuron() == this)
				return true;
		}
		return false;
	}

	void Neuron::setActivationType(Activation::Type type)
	{
		m_activationType = type;
		m_activationFunction = Activation::getActivationFunction(m_activationType);
	}
	Activation::Type Neuron::getActivationType() const
	{
		return m_activationType;
	}

	float Neuron::getOutputValue() const
	{
		return m_outputValue;
	}
	float Neuron::getNetinputValue() const
	{
		return m_netinputValue;
	}

	void Neuron::run()
	{
		m_netinputValue = 0;
		if (m_inputConnections)
		{
			for (auto& con : *m_inputConnections)
			{
				m_netinputValue += con->getWeightedSignal();
			}
		}
		m_outputValue = (*m_activationFunction)(m_netinputValue);
	}
}