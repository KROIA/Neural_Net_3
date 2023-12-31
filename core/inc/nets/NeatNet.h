#pragma once

#include "../base/NeuralNet_base.h"

#include "../base/Net.h"
#include "../base/Genom.h"
#include "../base/Neuron.h"
#include "../base/Connection.h"

namespace NeuralNet
{
	class NeatNet;
	class NEURAL_NET_3_EXPORT NeatGenom: public Genom
	{
		friend NeatNet;
	public:
		NeatGenom(size_t inputCount, size_t outputCount);
		NeatGenom(const NeatGenom& other);

		~NeatGenom();

		COPY_FUNC_DEC(NeatGenom);

		size_t getInputs() const;
		size_t getOutputs() const;

		void clear();

		Json toJson() override;
		bool fromJson(const Json& data) override;


		/*class NEURAL_NET_3_EXPORT NeatConnection
		{
		public:
			NeatConnection(size_t startID, size_t destinationID,
				       float weight, bool enabled = true);
			NeatConnection(Neuron *start, Neuron* destination,
				float weight, bool enabled = true);
			NeatConnection(const NeatConnection& other);
		

			void setStartID(size_t id);
			size_t getStartID() const;

			void setStartNeuron(Neuron* n);
			Neuron* getStartNeuron() const;

			void setDestinationID(size_t id);
			size_t getDestinationID() const;

			void setDestinationNeuron(Neuron* n);
			Neuron* getDestinationNeuron() const;

			void setWeight(float w);
			float getWeight() const;

			void setEnabled(bool enable);
			bool isEndabled() const;

		private:
			size_t m_startConnectionID;
			size_t m_destinationConnectionID;
			float m_weight;
			bool m_enabled;

			Neuron* m_startNeuron;
			Neuron* m_destinationNeuron;
		};

		bool addConnection(const NeatConnection&connection);
		NeatConnection* getConnection(size_t startID, size_t destinationID);

		const std::vector<NeatConnection>& getConnections() const;*/

		class NEURAL_NET_3_EXPORT NeatConnection 
		{
		public:
			NeatConnection(size_t startID, size_t destinationID,
				float weight, bool enabled = true);

			~NeatConnection();

			void setStartID(size_t id);
			size_t getStartID() const;

			void setDestinationID(size_t id);
			size_t getDestinationID() const;

			void setWeight(float w);
			float getWeight() const;

			void setEnabled(bool en);
			bool isEnabled() const;

			void setConnection(Connection* con);
			Connection* getConnection() const;
		private:
			void onConnectionDeleted(Connection* con);

			bool m_isEnabled;
			size_t m_startID;
			size_t m_destinationID;
			float m_weight; 

			Connection* m_connection;
		};

		bool addConnection(NeatConnection* connection);
		const std::vector<NeatConnection*>& getConnections() const;

	private:
		size_t m_inputs;
		size_t m_outputs;

		//std::vector<NeatConnection> m_connections;
		std::vector<NeatConnection*> m_connections;
	};

	class NEURAL_NET_3_EXPORT NeatNet: public Net
	{
	public:
		NeatNet(size_t inputCount, size_t outputCount);
		NeatNet(const NeatGenom &genom);
		NeatNet(const NeatNet& other);

		COPY_FUNC_DEC(NeatNet);

		bool setGenom(const NeatGenom& genom);

		NeatGenom::NeatConnection* addConnection(size_t startID, size_t destinationID, float weight, bool enable);

		void run() override;

		Neuron* getNeuron(size_t id) override;

	private:
		NeatGenom m_genom;

		std::vector<Neuron*> m_neurons;

	};
}