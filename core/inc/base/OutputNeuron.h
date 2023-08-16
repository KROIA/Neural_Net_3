#pragma once

#include "NeuralNet_base.h"
#include "Neuron.h"


#include <vector>


namespace NeuralNet
{
	class NEURAL_NET_3_EXPORT OutputNeuron : public Neuron
	{
	public:
		OutputNeuron(size_t id = 0);
		OutputNeuron(const OutputNeuron& other) = delete;
		~OutputNeuron();
	protected:

	};
}