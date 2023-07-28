#include "base/Activation.h"

namespace NeuralNet
{
	namespace Activation
	{
		ActivationFunction getActivationFunction(Type type)
		{
			switch (type)
			{
				case Type::linear: return &activate_linear;
				case Type::finiteLinear: return &activate_finiteLinear;
				case Type::relu: return &activate_relu;
				case Type::binary: return &activate_binary;
				case Type::gaussian: return &activate_gaussian;
				case Type::sigmoid: return &activate_sigmoid;
				case Type::tanh_: return &activation_tanh;
			}
			return activate_linear;
		}
		ActivationFunction getActivationDerivetiveFunction(Type type)
		{
			switch (type)
			{
			case Type::linear: return &activate_linear_derivetive;
			case Type::finiteLinear: return &activate_finiteLinear_derivetive;
			case Type::relu: return &activate_relu_derivetive;
			case Type::gaussian: return &activate_gaussian_derivetive;
			case Type::sigmoid: return &activate_sigmoid_derivetive;
			case Type::tanh_: return &activation_tanh_derivetive;
			}
			return nullptr;
		}
	}
}