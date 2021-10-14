#pragma once
#include <iostream>
#include <fstream>
#include "Constants.h"
#include "Sink.h"

namespace MAIN_HEDRON_NAMESPACE_NAME
{
	namespace HEDRON_LOGGER_NAMESPACE_NAME
	{
		class FileSink : public Sink
		{
			const char* m_file_path;
			std::ofstream m_file_stream;
		public:
			FileSink(const char* file_path) : Sink(SinkType::FILE_SINK), m_file_path(file_path)
			{}


			const char* get_file_path()
			{
				return m_file_path;
			}

			void set_file_path(const char* file_path)
			{
				m_file_path = file_path;
			}

			SinkState write(const char* msg) override
			{
				m_file_stream.open(m_file_path);
				m_file_stream << msg;
				m_file_stream.close();

				return SinkState::WRITING;
			}
		};
	}
}