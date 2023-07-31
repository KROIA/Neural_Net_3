#pragma once

#include "NeuralNet_base.h"
#include "../utilities/Json.h"

#include <string>
#include <vector>


namespace NeuralNet
{
	class NEURAL_NET_3_EXPORT Genom
	{
	public:
		Genom(const std::string& name);
		Genom(const Genom& other);

		virtual ~Genom();

		COPY_FUNC_DEC_BASE(Genom) = 0;

		virtual Json toJson() = 0;
		virtual bool fromJson(const Json& data) = 0;

		const std::string &getName() const;

	protected:
		std::string m_name;
	};
}