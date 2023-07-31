#include "base/Genom.h"

namespace NeuralNet
{
	Genom::Genom(const std::string& name)
		: m_name(name)
	{

	}
	Genom::Genom(const Genom& other)
		: m_name(other.m_name)
	{

	}

	Genom::~Genom() {

	}

	const std::string& Genom::getName() const
	{
		return m_name;
	}

}