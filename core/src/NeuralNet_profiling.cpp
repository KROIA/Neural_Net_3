#include "NeuralNet_profiling.h"

namespace NeuralNet
{
	namespace Profiling
	{
		void start()
		{
#ifdef NEURAL_NET_3_PROFILING
			EASY_PROFILER_ENABLE;
#endif
		}
		uint32_t saveProfilerFile(const std::string& fileName)
		{
#ifdef NEURAL_NET_3_PROFILING
			return profiler::dumpBlocksToFile(fileName.c_str());
#else
			return 0;
#endif
		}
	}
}