#pragma once

#include "../NeuralNet_base.h"

#include <math.h>

#define NET_ACTIVATION_LINEAR(x) x
#define NET_ACTIVATION_LINEAR_DERIVETIVE(x) 1

#define NET_ACTIVATION_RELU(x) x<=0? 0:x
#define NET_ACTIVATION_RELU_DERIVETIVE(x) x<=0? 0:1

#define NET_ACTIVATION_FINITELINEAR(x) x<-1? -1: x>1? 1:x
#define NET_ACTIVATION_FINITELINEAR_DERIVETIVE(x) x<-1? 0: x>1? 0:1

#define NET_ACTIVATION_BINARY(x) x<0? -1:1
// No derivetive exists

//https://www.wolframalpha.com/input/?i=exp%28-pow%28x%2C2%29%29*2-1
#define NET_ACTIVATION_GAUSSIAN(x) 2*pow(2.71828182845904523536f,-(x)*(x))-1 
#define NET_ACTIVATION_GAUSSIAN_DERIVETIVE(x) -4*pow(2.71828182845904523536f,-(x)*(x))*x 


#define NET_ACTIVATION_SIGMOID(x) atan((float)x)* 0.628318531f
#define NET_ACTIVATION_SIGMOID_DERIVETIVE(x) 0.628318531f/((x)*(x)+1)

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

			count
		};

		inline float activate_linear(float x) { return NET_ACTIVATION_LINEAR(x); }
		inline float activate_linear_derivetive(float x) { return 1; }
		inline float activate_finiteLinear(float x) { return NET_ACTIVATION_FINITELINEAR(x); }
		inline float activate_finiteLinear_derivetive(float x) { return NET_ACTIVATION_FINITELINEAR_DERIVETIVE(x); }
		inline float activate_relu(float x) { return NET_ACTIVATION_RELU(x); }
		inline float activate_relu_derivetive(float x) { return NET_ACTIVATION_RELU_DERIVETIVE(x); }
		inline float activate_binary(float x) { return NET_ACTIVATION_BINARY(x); }
		inline float activate_gaussian(float x) { return NET_ACTIVATION_GAUSSIAN(x); }
		inline float activate_gaussian_derivetive(float x) { return NET_ACTIVATION_GAUSSIAN_DERIVETIVE(x); }
		inline float activate_sigmoid(float x) { return NET_ACTIVATION_SIGMOID(x); }
		inline float activate_sigmoid_derivetive(float x) { return NET_ACTIVATION_SIGMOID_DERIVETIVE(x); }
		
		extern ActivationFunction NEURAL_NET_3_EXPORT getActivationFunction(Type type);
		extern ActivationFunction NEURAL_NET_3_EXPORT getActivationDerivetiveFunction(Type type);
	}
}
