#include "base/Neuron.h"
#include "utilities/RandomEngine.h"


namespace NeuralNet
{
	Neuron::Neuron()
		: m_outputValue(0)
		, m_netinputValue(0)
		, m_inputCount(0)
		, m_activationType(Activation::Type::linear)
		, m_activationFunction(Activation::getActivationFunction(m_activationType))
	{

	}
	Neuron::Neuron(const Neuron& other)
		: m_inputValues(other.m_inputValues)
		, m_weights(other.m_weights)
		, m_outputValue(other.m_outputValue)
		, m_netinputValue(other.m_netinputValue)
		, m_inputCount(other.m_inputCount)
		, m_activationType(other.m_activationType)
		, m_activationFunction(other.m_activationFunction)
	{

	}
	Neuron::~Neuron()
	{

	}

	void Neuron::setInputCount(size_t count)
	{
		size_t currentCount = m_inputValues.size();
		if (count == currentCount)
			return;
		m_inputValues.resize(count);
		m_weights.resize(count);
		if (count > currentCount)
		{
			size_t countBytes = (count - currentCount) * sizeof(float);
			memset(m_inputValues.data() + currentCount, 0, countBytes);
			for (size_t i = currentCount; i < count; ++i)
				m_weights[i] = Utilities::RandomEngine::getFloat(-1, 1);
		}
		m_inputCount = count;
	}
	size_t Neuron::getInputCount() const
	{
		return m_inputCount;
	}

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
	const std::vector<float>& Neuron::getInputValue() const
	{
		return m_inputValues;
	}
	float Neuron::getInputValue(size_t input) const
	{
		if (input >= m_inputCount)
			return 0;
		return m_inputValues[input];
	}

	void Neuron::setWeight(const std::vector<float>& weights)
	{
		if (weights.size() == m_inputCount)
		{
			m_weights = weights;
			return;
		}
		size_t min = std::min(weights.size(), m_inputCount);
		m_weights.insert(m_weights.begin(), weights.begin(), weights.begin() + min);
	}
	void Neuron::setWeight(size_t input, float weight)
	{
		if (input >= m_inputCount)
			return;
		m_weights[input] = weight;
	}
	const std::vector<float>& Neuron::getWeight() const
	{
		return m_weights;
	}
	float Neuron::getWeight(size_t input) const
	{
		if (input >= m_inputCount)
			return 0;
		return m_weights[input];
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
		for (size_t i = 0; i < m_inputValues.size(); ++i)
		{
			m_netinputValue += m_inputValues[i] * m_weights[i];
		}
		m_outputValue = (*m_activationFunction)(m_netinputValue);
	}
}