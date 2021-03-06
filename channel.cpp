#include "channel.h"

Channel::Channel(int fd) : m_fd(fd), m_events(0), m_minHeapIndex(-1)
{
	
}

void Channel::SetReadCallback(CallbackType readCallback)
{
	m_readCallback = readCallback;
}

void Channel::SetWriteCallback(CallbackType writeCallback)

{
	m_writeCallback = writeCallback;
}

void Channel::SetErrorCallback(CallbackType errorCallback)
{
	m_errorCallback = errorCallback;
}

void Channel::SetEvents(int events)
{
	m_events = events;
}

int Channel::GetFd()
{
	return m_fd;
}

int Channel::GetEvents()
{
	return m_events;
}

SimpleBuffer & Channel::GetInBuffer()
{
	return m_inBuffer;
}

SimpleBuffer & Channel::GetOutBuffer()
{
	return m_outBuffer;
}

HttpMessage & Channel::GetHttpMessage()
{
	return m_httpmessage;
}

const struct timeval & Channel::GetLastActiveTime()
{
	return m_stLastActiveTime;
}

void Channel::SetLastActiveTime(const struct timeval & stTimeval)
{
	m_stLastActiveTime = stTimeval;
}

int Channel::GetMinHeapIndex()
{
	return m_minHeapIndex;
}

void Channel::SetMinHeapIndex(int minHeapIndex)
{
	m_minHeapIndex = minHeapIndex;
}

void Channel::HandleEvent(EventLoop & eventLoop, std::shared_ptr<Channel> ptChannel, int revents)
{
	if (revents & (EPOLLHUP | EPOLLERR))
	{
		if (m_errorCallback) m_errorCallback(eventLoop, ptChannel);
		ERRLOG("%s %s %d, Handle event %d error", __FILE__, __func__, __LINE__, m_fd);
	}
	else
	{
		if (revents & (EPOLLIN | EPOLLRDHUP))
		{
			if (m_readCallback) m_readCallback(eventLoop, ptChannel);
		}
		if (revents & EPOLLOUT)
		{
			if (m_writeCallback) m_writeCallback(eventLoop, ptChannel);
		}
	}
}