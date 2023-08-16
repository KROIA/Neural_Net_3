#pragma once

#include "NeuralNet_base.h"

#include <vector>

namespace NeuralNet
{
	class Neuron;
	class NEURAL_NET_3_EXPORT Net
	{
	public:
		Net(size_t inputCount, size_t outputCount);
		Net(const Net& other);
		virtual ~Net();

		COPY_FUNC_DEC_BASE(Net) = 0;

		size_t getInputCount() const;
		size_t getOutputCount() const;

		void setInput(const std::vector<float> &inputs);
		void setInput(size_t input, float value);

		const std::vector<float>& getInput() const;
		float getInput(size_t input) const;

		const std::vector<float>& getOutput() const;
		float getOutput(size_t output) const;

		void setName(const std::string& name);
		const std::string& getName() const;

		virtual void run() = 0;

		virtual Neuron* getNeuron(size_t id) = 0;

	protected:
		

		std::vector<float> m_inputValues;
		std::vector<float> m_outputValues;

		size_t m_inputCount;
		size_t m_outputCount;

		std::string m_name;

		LOG_DECLARE;
	private:
		

		
	};

}