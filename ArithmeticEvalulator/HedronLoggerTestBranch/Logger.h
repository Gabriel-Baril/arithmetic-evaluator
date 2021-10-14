#pragma once
#include "Constants.h"
#include "Sink.h"
#include "FileSink.h"

namespace MAIN_HEDRON_NAMESPACE_NAME
{
	namespace HEDRON_LOGGER_NAMESPACE_NAME
	{
		class Logger
		{
			Sink* m_destination;
		public:

			Sink* const get_destination() const
			{
				switch (m_destination->get_sink_type())
				{
				case SinkType::FILE_SINK:
					return static_cast<FileSink*>(m_destination);
					break;
				case SinkType::STREAM_SINK:
					return static_cast<FileSink*>(m_destination);
					break;
				}
			}
		};
	}
}