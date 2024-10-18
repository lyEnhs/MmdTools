#ifndef VIEWER_LOGGER_H_
#define VIEWER_LOGGER_H_

#include <deque>
#include <Base/Log.h>

namespace lyenhs
{
	class ImGUILogSink : public spdlog::sinks::sink
	{
	public:
		explicit ImGUILogSink(size_t maxBufferSize = 100)
			:m_maxBufferSize(maxBufferSize)
			,m_added(false)
		{
		}

		void log(const spdlog::details::log_msg& msg) override
		{
			while (m_buffer.size() >= m_maxBufferSize)
			{
				if (m_buffer.empty())
				{
					break;
				}
				m_buffer.pop_front();
			}

			m_buffer.emplace_back(LogMessage{ msg.level, msg.formatted.str()});
			m_added = true;
		}

		void flush() override
		{
		}

		struct LogMessage
		{
			spdlog::level::level_enum  m_level;
			std::string				   m_message;
		};

		const std::deque<LogMessage>& GetBuffer() const { return m_buffer; }

		bool IsAdded() const { return m_added; }
		void ClearAddedFlag() { m_added = false; }

	private:
		size_t					m_maxBufferSize;
		std::deque<LogMessage>	m_buffer;
		bool					m_added;
	};
}

#endif//VIEWER_LOGGER_H_