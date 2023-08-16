#pragma once

#include "NeuralNet_base.h"
#include "Activation.h"


#include <vector>


namespace NeuralNet
{
	class Connection;
	class NEURAL_NET_3_EXPORT Neuron
	{
	public:
		Neuron(size_t id = 0);
		Neuron(const Neuron& other) = delete;
		virtual ~Neuron();

		//COPY_FUNC_DEC_BASE(Neuron);

		void setID(size_t id);
		size_t getID() const;

		//void setInputCount(size_t count);
		size_t getInputCount() const;

		//void setInputValue(const std::vector<float>& values);
		//void setInputValue(size_t input, float value);
		std::vector<float> getInputValue() const;
		float getInputValue(size_t input) const;

		void setWeight(const std::vector<float>& weights);
		void setWeight(size_t input, float weight);
		std::vector<float> getWeight() const;
		float getWeight(size_t input) const;

		Connection* addConnectionTo(Neuron* destination);
		bool removeConnectionTo(Neuron* destination);
		static bool removeConnection(Connection* con);
		static bool addConnection(Connection* con);
		bool isConnectedTo(Neuron* destination) const;

		void setActivationType(Activation::Type type);
		Activation::Type getActivationType() const;

		float getOutputValue() const;
		float getNetinputValue() const;

		virtual void run();

	protected:
		

		//std::vector<float> m_inputValues;
		//std::vector<float> m_weights;
		float m_outputValue;
		float m_netinputValue;
		//size_t m_inputCount;
		Activation::Type m_activationType;
		Activation::ActivationFunction m_activationFunction;

		size_t m_id;
		
		std::vector<Connection*>* m_inputConnections;
		std::vector<Connection*>* m_outputConnections;
		// std::vector<Connection*> m_inputConnections;
		// std::vector<Connection*> m_outputConnections;
	private:
		

	};
}