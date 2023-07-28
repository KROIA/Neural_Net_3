#pragma once

#include "NeuralNet_base.h"

#include <math.h>

namespace NeuralNet
{
	namespace Activation
	{
		typedef float (*ActivationFunction)(float);
		enum Type
		{
			linear,
			finiteLinear,
			relu,
			binary,
			sigmoid,
			gaussian,
			tanh_,

			count
		};

		inline float activate_linear(float x) { return x; }
		inline float activate_linear_derivetive(float x) { return 1; }
		inline float activate_finiteLinear(float x) { return x < -1 ? -1 : x>1 ? 1 : x; }
		inline float activate_finiteLinear_derivetive(float x) { return x < -1 ? 0 : x>1 ? 0 : 1; }
		inline float activate_relu(float x) { return x <= 0 ? 0 : x; }
		inline float activate_relu_derivetive(float x) { return x <= 0 ? 0 : 1; }
		inline float activate_binary(float x) { return x < 0 ? -1 : 1; }

		//https://www.wolframalpha.com/input/?i=exp%28-pow%28x%2C2%29%29*2-1
		inline float activate_gaussian(float x) { return 2 * exp(-(x) * (x)) - 1; }
		inline float activate_gaussian_derivetive(float x) { return -4 * exp(-(x) * (x)) * x; }
		inline float activate_sigmoid(float x) { return 1 / (1 + exp(-x)); }
		inline float activate_sigmoid_derivetive(float x) { 
			float ex = exp(x);
			float sum = ex + 1;
			return ex / (sum * sum);
		}

		inline float activation_tanh(float x) { return tanh(x); }
		inline float activation_tanh_derivetive(float x) { 
			float c = cosh(x);
			return 1 / (c * c);
		}
		
		extern ActivationFunction NEURAL_NET_3_EXPORT getActivationFunction(Type type);
		extern ActivationFunction NEURAL_NET_3_EXPORT getActivationDerivetiveFunction(Type type);
	}
}
