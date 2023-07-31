#pragma once
#include "../NeuralNet_global.h"
#include "../utilities/NeuralNet_profiling.h"
#include "Logger.h"

#define COPY_FUNC_DEC_BASE(className) \
	virtual className *copy() const
#define COPY_FUNC_DEC(className) \
	className *copy() const override

#define COPY_FUNC_IMPL(className) \
	className *className::copy() const \
	{ \
		return new className(*this);\
	}


#define NEURAL_NET_LOGGING


#ifdef NEURAL_NET_LOGGING
#define LOG_INSTANCE           m_logger
#define LOG_DECLARE		       mutable Log::ConsoleLogger LOG_INSTANCE;

#define LOG(params,...)		   m_logger.log(params,__VA_ARGS__);
#define LOG_FUNC(params,...)   m_logger.log(std::string(__PRETTY_FUNCTION__)+": "+params,__VA_ARGS__);
#define LOG_TAB_IN			   m_logger.tabIn();
#define LOG_TAB_OUT			   m_logger.tabOut();
#define LOG_SET_TABS(amount)   m_logger.setTabCount(amount);
#define LOG_TABS               m_logger.getTabCount()

#else
#define LOG(params,...)		
#define LOG_FUNC(params,...)
#define LOG_TAB_IN			
#define LOG_TAB_OUT			
#define LOG_SET_TABS(amount)
#define LOG_TABS            

#endif