#pragma once

#include "NeuralNet_base.h"
#include "Activation.h"


#include <vector>


namespace NeuralNet
{
	class NEURAL_NET_3_EXPORT Neuron
	{
	public:
		Neuron();
		Neuron(const Neuron& other);
		virtual ~Neuron();

		void setInputCount(size_t count);
		size_t getInputCount() const;

		void setInputValue(const std::vector<float>& values);
		void setInputValue(size_t input, float value);
		const std::vector<float>& getInputValue() const;
		float getInputValue(size_t input) const;

		void setWeight(const std::vector<float>& weights);
		void setWeight(size_t input, float weight);
		const std::vector<float>& getWeight() const;
		float getWeight(size_t input) const;

		void setActivationType(Activation::Type type);
		Activation::Type getActivationType() const;

		float getOutputValue() const;
		float getNetinputValue() const;

		virtual void run();

	protected:
		std::vector<float> m_inputValues;
		std::vector<float> m_weights;
		float m_outputValue;
		float m_netinputValue;
		size_t m_inputCount;
		Activation::Type m_activationType;
		Activation::ActivationFunction m_activationFunction;
	private:

	};
}