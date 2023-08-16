#pragma once

#include "NeuralNet_base.h"
#include "utilities/Signal.h"


namespace NeuralNet
{
	class Neuron;
	class NEURAL_NET_3_EXPORT Connection
	{
		//friend Neuron;
	
		Connection(Neuron* start, Neuron* destination);
		Connection(const Connection& other) = delete;
	public:
		static Connection* create(Neuron* start, Neuron* destination);
		virtual ~Connection();
		

		Neuron* getStartNeuron() const;
		Neuron* getDestinationNeuron() const;

		void setWeight(float w);
		float getWeight() const;
		float getWeightedSignal() const;
		float getSignal() const;


		void disconnect();
		void cleanup();

		Signal<Connection*> onDelete;
	protected:
		
		

		Neuron* m_start;
		Neuron* m_destination;

		float m_weight;

		
	};
}