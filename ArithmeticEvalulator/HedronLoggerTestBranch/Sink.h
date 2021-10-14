#pragma once
#include "Constants.h"

namespace MAIN_HEDRON_NAMESPACE_NAME
{
	namespace HEDRON_LOGGER_NAMESPACE_NAME
	{
		enum class SinkType
		{
			FILE_SINK,
			STREAM_SINK
		};

		enum class SinkState
		{
			WRITING,
			WAITING,
			ERROR
		};

		enum class SinkOpeningState
		{
			SUCCESS,
			FAIL
		};

		class Sink
		{
		protected:
			SinkType m_sink_type;
		public:
			Sink(SinkType sink_type) : m_sink_type(sink_type) {}
			virtual SinkState write(const char* msg) = 0;

			virtual void log() = 0;
			virtual void warning() = 0;
			virtual void error() = 0;
			virtual void debug() = 0;
			virtual void benchmark() = 0;
			virtual void news() = 0;
			virtual void test() = 0;
			virtual void info() = 0;
			virtual void print() = 0; // generic -> log | warning | error | debug | benchmark | news | test | info
			
			virtual void log_if() = 0;
			virtual void warning_if() = 0;
			virtual void error_if() = 0;
			virtual void debug_if() = 0;
			virtual void benchmark_if() = 0;
			virtual void news_if() = 0;
			virtual void test_if() = 0;
			virtual void info_if() = 0;
			virtual void print_if() = 0; // generic -> log_if | warning_if | error_if | debug_if | benchmark_if | news_if | test_if | info_if
			virtual void assert_if() = 0;

			virtual SinkOpeningState get_sink_state()
			{
				return SinkOpeningState::SUCCESS;
			}
			virtual SinkType get_sink_type() { return m_sink_type; }
		};
	}
}