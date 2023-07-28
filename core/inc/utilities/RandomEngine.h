#pragma once

#include "base/NeuralNet_base.h"

namespace NeuralNet
{
	namespace Utilities
	{
		class NEURAL_NET_3_EXPORT RandomEngine
		{
				RandomEngine();
			public:
			

				static float getFloat(float min = 0, float max = 1);
				static int getInt(int min = 0, int max = 1);
				static int getNext();

				static void setSeed(unsigned int seed);
				static unsigned int getSeed();
			private:
				static RandomEngine s_instance;
				unsigned int m_seed;
		};
	}
}