#pragma once

#include "NeuralNet_base.h"
#include "Neuron.h"


#include <vector>


namespace NeuralNet
{
	class NEURAL_NET_3_EXPORT InputNeuron : public Neuron
	{
	public:
		InputNeuron(size_t id = 0);
		InputNeuron(const InputNeuron& other) = delete;
		 
		~InputNeuron();

		void setInput(float value);
		float getInput() const;

		void run() override;
	protected:


	};
}