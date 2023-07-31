#include "base/Net.h"


namespace NeuralNet
{
	Net::Net(size_t inputCount, size_t outputCount)
		: m_inputCount(inputCount)
		, m_outputCount(outputCount)
	{
		m_inputValues.resize(m_inputCount);
		m_outputValues.resize(m_outputCount);
		for (size_t i = 0; i < m_inputCount; ++i)
		{
			m_inputValues[i] = 0;
		}
		for (size_t i = 0; i < m_outputCount; ++i)
		{
			m_outputValues[i] = 0;
		}
	}
	Net::Net(const Net& other)
		: m_inputValues(other.m_inputValues)
		, m_outputValues(other.m_outputValues)
		, m_inputCount(other.m_inputCount)
		, m_outputCount(other.m_outputCount)
	{

	}

	Net::~Net()
	{

	}


	size_t Net::getInputCount() const
	{
		return m_inputCount;
	}
	size_t Net::getOutputCount() const
	{
		return m_outputCount;
	}

	void Net::setInput(const std::vector<float> &inputs)
	{
		if (inputs.size() == m_inputCount)
		{
			m_inputValues = inputs;
			return;
		}
		size_t min = std::min(inputs.size(), m_inputCount);
		m_inputValues.insert(m_inputValues.begin(), inputs.begin(), inputs.begin() + min);
	}
	void Net::setInput(size_t input, float value)
	{
		if (input >= m_inputCount)
			return;
		m_inputValues[input] = value;
	}

	const std::vector<float>& Net::getInput() const
	{
		return m_inputValues;
	}
	float Net::getInput(size_t input) const
	{
		if (input >= m_inputCount)
			return 0;
		return m_inputValues[input];
	}

	const std::vector<float>& Net::getOutput() const
	{
		return m_outputValues;
	}
	float Net::getOutput(size_t output) const
	{
		if (output >= m_inputCount)
			return 0;
		return m_outputValues[output];
	}

	void Net::setName(const std::string& name)
	{
		m_name = name;
		LOG_INSTANCE.setName(m_name);
	}
	const std::string& Net::getName() const
	{
		return m_name;
	}
}