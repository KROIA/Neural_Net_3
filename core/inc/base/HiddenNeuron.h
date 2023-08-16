#pragma once

#include "NeuralNet_base.h"
#include "Neuron.h"


#include <vector>


namespace NeuralNet
{
	class NEURAL_NET_3_EXPORT HiddenNeuron : public Neuron
	{
	public:
		HiddenNeuron(size_t id = 0);
		HiddenNeuron(const HiddenNeuron& other) = delete;
		~HiddenNeuron();
	protected:

	};
}