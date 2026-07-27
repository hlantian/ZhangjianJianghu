// Copyright (C) 1999-2000 Open Source Telecom Corporation.
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software 
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// 
// As a special exception to the GNU General Public License, permission is 
// granted for additional uses of the text contained in its release 
// of Common C++.
// 
// The exception is that, if you link the Common C++ library with other
// files to produce an executable, this does not by itself cause the
// resulting executable to be covered by the GNU General Public License.
// Your use of that executable is in no way restricted on account of
// linking the Common C++ library code into it.
// 
// This exception does not however invalidate any other reasons why
// the executable file might be covered by the GNU General Public License.
// 
// This exception applies only to the code released under the 
// name Common C++.  If you copy code from other releases into a copy of
// Common C++, as the General Public License permits, the exception does
// not apply to the code that you add in this way.  To avoid misleading
// anyone as to the status of such modified files, you must delete
// this exception notice from them.
// 
// If you write modifications of your own for Common C++, it is your choice
// whether to permit this exception to apply to your modifications.
// If you do not wish that, delete this exception notice.  

#include "config.h"
#include "thread.h"
#include "socket.h"

Socket::Socket(int domain, int type, int protocol)
{
	setSocket();
	so = socket(domain, type, protocol);
	if(so == INVALID_SOCKET)
	{
		Error(SOCKET_CREATE_FAILED);
		return;
	}
	state = SOCKET_AVAILABLE;
};

Socket::Socket(SOCKET fd)
{
	setSocket();
	if(fd < 0)
	{
		Error(SOCKET_CREATE_FAILED);
		return;
	}
	so = fd;
	state = SOCKET_AVAILABLE;
};

Socket::Socket(const Socket &orig)
{
	setSocket();
	so = orig.so;
	if(so == INVALID_SOCKET)
		Error(SOCKET_COPY_FAILED);
	state = orig.state;
};

void Socket::setSocket(void) 
{
	flags.thrown = false;
	flags.broadcast = false;
	flags.route = true;
	flags.keepalive = false;
	so = -1;
	state = SOCKET_INITIAL;
}

sockerror_t Socket::connectError(void)
{
	switch(WSAGetLastError())	
	{
	case WSAENETDOWN:
		return Error(SOCKET_RESOURCE_FAILURE);
	case WSAEINPROGRESS:
		return Error(SOCKET_CONNECT_BUSY);
	case WSAEADDRNOTAVAIL:
		return Error(SOCKET_CONNECT_INVALID);
	case WSAECONNREFUSED:
		return Error(SOCKET_CONNECT_REFUSED);
	case WSAENETUNREACH:
		return Error(SOCKET_CONNECT_NOROUTE);
	default:
		return Error(SOCKET_CONNECT_FAILED);
	} 
}


void Socket::endSocket(void)
{
	state =  SOCKET_INITIAL;
	if(so != INVALID_SOCKET)
	{
		shutdown(so, 2);
		closesocket(so);
		so = -1;
	}
}

sockerror_t  Socket::setBroadcast(bool enable)
{
	if(setsockopt(so, SOL_SOCKET, SO_BROADCAST, (char *)&enable, (socklen_t)sizeof(enable)))
		Error(SOCKET_BROADCAST_DENIED);
	flags.broadcast = enable;
	return SOCKET_SUCCESS;
}

sockerror_t Socket::setRouting(bool enable)
{
	bool disable = !enable;
	if(setsockopt(so, SOL_SOCKET, SO_DONTROUTE, (char *)&disable, (socklen_t)sizeof(disable)))
		return Error(SOCKET_ROUTING_DENIED);
	flags.route = enable;
	return SOCKET_SUCCESS;
}

sockerror_t Socket::setKeepAlive(bool enable)
{
	if(setsockopt(so, SOL_SOCKET, SO_KEEPALIVE, (char *)&enable, (socklen_t)sizeof(enable)))
		return Error(SOCKET_KEEPALIVE_DENIED);
	flags.keepalive = enable;
	return SOCKET_SUCCESS;
}

				
sockerror_t Socket::Error(sockerror_t err, char *errs)
{
	errid = err;
	errstr = errs;
	if(!flags.thrown)
	{
		flags.thrown = true;
		throw((Socket *)this);
		flags.thrown = false;
	}
	return err;
}


bool Socket::isPending(sockpend_t pend, unsigned long timeout)
{
	int status;
	struct timeval tv;
	struct timeval *tvp = &tv;
	fd_set grp;

	if(timeout == ~0)
		tvp = NULL;
	else
	{
		tv.tv_usec = (timeout % 1000) * 1000;
		tv.tv_sec = timeout / 1000;
	}
	FD_ZERO(&grp);
	FD_SET(so, &grp);
	switch(pend)	{
	case SOCKET_PENDING_INPUT:
		status = select(so + 1, &grp, NULL, NULL, tvp);
		break;
	case SOCKET_PENDING_OUTPUT:
		status = select(so + 1, NULL, &grp, NULL, tvp);
		break;
	case SOCKET_PENDING_ERROR:
		status = select(so + 1, NULL, NULL, &grp, tvp);
		break;
	}
	if(status < 1)
		return false;
	if(FD_ISSET(so, &grp))
		return true;
	return false;
}

Socket &Socket::operator=(const Socket &from)
{
	if(so == from.so)
		return *this;

	if(state != SOCKET_INITIAL)
		endSocket();

	so = from.so;
	if(so == INVALID_SOCKET)
		state = SOCKET_INITIAL;
	else
		state = from.state;

	return *this;
}

InetHostAddress Socket::getSender(short *port)
{
	struct sockaddr_in from;
	char buf;
	int len = sizeof(from);

	int rc = ::recvfrom(so, &buf, 1, MSG_PEEK, (struct sockaddr *)&from, &len);
	if(rc == 1)
	{
		if(port)
			*port = ntohs(from.sin_port);
	}
	else
	{
		if(port)
			*port = 0;
		memset(&from.sin_addr, 0, sizeof(from.sin_addr));
	}
	if(rc < 0)
		Error(SOCKET_INPUT_ERROR);

	return InetHostAddress(from.sin_addr);
}

InetHostAddress Socket::getLocal(short *port)
{
	struct sockaddr_in addr;
	int len = sizeof(addr);

	if(getsockname(so, (struct sockaddr *)&addr, &len))
	{
		Error(SOCKET_RESOURCE_FAILURE);
		if(port)
			*port = 0;
		memset(&addr.sin_addr, 0, sizeof(addr.sin_addr));
	}
	else
	{
		if(port)
			*port = ntohs(addr.sin_port);
	}
	return InetHostAddress(addr.sin_addr);
}

InetHostAddress Socket::getPeer(short *port)
{
	struct sockaddr_in addr;
	int len = sizeof(addr);

	if(getpeername(so, (struct sockaddr *)&addr, &len))
	{
		Error(SOCKET_RESOURCE_FAILURE);
		if(port)
			*port = 0;
		memset(&addr.sin_addr, 0, sizeof(addr.sin_addr));
	}
	else
	{
		if(port)
			*port = ntohs(addr.sin_port);
	}
	return InetHostAddress(addr.sin_addr);
}

UDPSocket::UDPSocket(void) : Socket(PF_INET, SOCK_DGRAM, 0){
	memset(&peer, 0, sizeof(peer));
	peer.sin_family = AF_INET;
};

UDPSocket::UDPSocket(InetAddress &ia, short port) : 
Socket(PF_INET, SOCK_DGRAM, 0)
{
	peer.sin_family = AF_INET;
	peer.sin_addr = getaddress(ia);
	peer.sin_port = htons(port);
	if(bind(so, (sockaddr *)&peer, sizeof(peer)))
	{
		endSocket();
		Error(SOCKET_BINDING_FAILED);
		return;
	}
	state = SOCKET_BOUND;
};

void UDPSocket::setPeer(InetHostAddress &ia, short port)
{
	peer.sin_family = AF_INET;
	peer.sin_addr = getaddress(ia);
	peer.sin_port = htons(port);
}

InetHostAddress UDPSocket::getPeer(short *port)
{
	char buf;
	socklen_t len = sizeof(peer);
	int rtn = ::recvfrom(so, &buf, 1, MSG_PEEK, (struct sockaddr *)&peer, &len);
	
	if(rtn < 1)
	{
		if(port)
			*port = 0;

		memset(&peer, 0, sizeof(peer));
	}
	else
	{
		if(port)
			*port = ntohs(peer.sin_port);
	}
	return InetHostAddress(peer.sin_addr);
}

UDPBroadcast::UDPBroadcast(InetAddress &ia, short port) : 
UDPSocket(ia, port)
{
	if(so != INVALID_SOCKET)
		setBroadcast(true);
};

void UDPBroadcast::setPeer(BroadcastAddress &ia, short port)
{
	peer.sin_family = AF_INET;
	peer.sin_addr = getaddress(ia);
	peer.sin_port = htons(port);
}

TCPSocket::TCPSocket(InetAddress &ia, short port, int backlog) : 
Socket(PF_INET, SOCK_STREAM, 0)
{
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_addr = getaddress(ia);
	addr.sin_port = htons(port);

	if(bind(so, (struct sockaddr *)&addr, sizeof(addr)))	{
		endSocket();
		Error(SOCKET_BINDING_FAILED);
		return;
	}

	if(listen(so, backlog))	{
		endSocket();
		Error(SOCKET_BINDING_FAILED);
		return;
	}
	state = SOCKET_BOUND;
};

void TCPSocket::Reject(void)
{
	int rej = accept(so, NULL, NULL);
	shutdown(rej, 2);
	closesocket(rej);
}

TCPStream::TCPStream() :
Socket(AF_INET, SOCK_STREAM, 0), streambuf(), iostream((streambuf *)this)
{
	gbuf = pbuf = NULL;
	bufsize = 0;
}

TCPStream::TCPStream(TCPSocket &server, int size) :
Socket(accept(server.so, NULL, NULL)), streambuf(), iostream((streambuf *)this)
{
	gbuf = pbuf = NULL;
	bufsize = 0;

	short port;
	InetHostAddress host = getPeer(&port);
	if(!server.OnAccept(host, port))	{
		endSocket();
		Error(SOCKET_CONNECT_REJECTED);
		return;
	}
	Allocate(size);
	Socket::state = SOCKET_CONNECTED;
};

TCPStream::TCPStream(InetHostAddress &host, short port, int size) :
Socket(AF_INET, SOCK_STREAM, 0), streambuf(), iostream((streambuf *)this)
{
	int len;
	gbuf = pbuf = NULL;
	bufsize = 0;
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_addr = getaddress(host);
	addr.sin_port = htons(port);

	if(connect(so, (struct sockaddr *)&addr, (socklen_t)sizeof(addr)))
	{
		connectError();
		endSocket();
		return;
	}
	Allocate(size);
	Socket::state = SOCKET_CONNECTED;
};

void TCPStream::endStream(void)
{
	sync();
	if(gbuf)
	{
		delete gbuf;
		gbuf = NULL;
	}
	if(pbuf)
	{
		delete pbuf;
		pbuf = NULL;
	}
	bufsize = 0;
	endSocket();
};

void TCPStream::Allocate(int size)
{
	if(size < 2)	
	{
		bufsize = 1;
		return;
	}

	gbuf = new char[size];
	pbuf = new char[size];
	if(!pbuf || !gbuf)
	{
		Error(SOCKET_RESOURCE_FAILURE);
		return;
	}
	setg(gbuf, gbuf + size, gbuf + size);
	setp(pbuf, pbuf + size);
	bufsize = size;
}

int TCPStream::doallocate()
{
	if(bufsize)
		return 0;

	Allocate(1);
	return 1;
}

int TCPStream::underflow(void)
{
	int rlen;
	unsigned char ch;

	if(bufsize < 2)
	{
		rlen = ::recv(so, (char *)&ch, 1, 0);
		if(rlen < 1)
		{
			if(rlen < 0)
				clear(ios::failbit | rdstate());
			return EOF;
		}
		return ch;
	}

	if(!gptr())
		return EOF;

	if(gptr() < egptr())
		return (unsigned char)*gptr();

	rlen = (gbuf + bufsize) - eback();
	rlen = ::recv(so, eback(), rlen, 0);
	if(rlen < 1)
	{
		if(rlen < 0)
			clear(ios::failbit | rdstate());
		return EOF;
	}

	setg(eback(), eback(), eback() + rlen);
	return (unsigned char) *gptr();
}

int TCPStream::sync(void)
{
	overflow(EOF);
	return 0;
}

int TCPStream::overflow(int c)
{
	unsigned char ch;
	int rlen, req;

	if(bufsize < 2)
	{
		if(c == EOF)
			return 0;

		ch = (unsigned char)(c);
		rlen = ::send(so, (const char *)&ch, 1, 0);
		if(rlen < 1)
		{
			if(rlen < 0)
				clear(ios::failbit | rdstate());
			return EOF;
		}
		else
			return c;
	}

	if(!pbase())
		return EOF;

	req = pptr() - pbase();
	if(req)
	{
		rlen = ::send(so, pbase(), req, 0);
		if(rlen < 1)
		{
			if(rlen < 0)
				clear(ios::failbit | rdstate());
			return EOF;
		}

		req -= rlen;
	}

	if(req)
		memcpy(pptr(), pptr() + rlen, req);
	setp(pbuf + req, pbuf + bufsize);

	if(c != EOF)
	{
		*pptr() = (unsigned char)c;
		pbump(1);
	}
	return c;
}

TCPSession::TCPSession(Semaphore *start, TCPSocket &server, int size, int pri, int stack) :
TCPStream(server, size), Thread(start, pri, stack) {};

tcpstream::tcpstream() :
TCPStream()
{
	setError(false);
}

tcpstream::tcpstream(char *addr, int buffer) :
TCPStream()
{
	setError(false);
	open(addr, buffer);
}

tcpstream::tcpstream(TCPSocket &server, int buffer) :
TCPStream()
{
	setError(false);
	open(server, buffer);
}

void tcpstream::open(TCPSocket &tcp, int buffer)
{
	short port;
	InetHostAddress host;

	endStream();
	so = accept(tcp.so, NULL, NULL);
	if(so == INVALID_SOCKET)
		return;

	host = getPeer(&port);
	if(!tcp.OnAccept(host, port))
	{
		endSocket();
		return;
	}
	Allocate(buffer);
	Socket::state = SOCKET_CONNECTED;
}

void tcpstream::open(char *path, int buffer)
{
	char abuf[256];
	char *cp, *ep;
	struct sockaddr_in addr;
	InetHostAddress host;

	close();
	if(Socket::state != SOCKET_AVAILABLE)
		return;

	cp = strrchr(path, ':');
	if(!cp)
		return;

	++cp;
	strncpy(abuf, path, sizeof(abuf) - 1);
	abuf[sizeof(abuf) - 1] = 0;
	ep = strrchr(abuf, ':');
	if(ep)
		*ep = 0;

	host = abuf;
	addr.sin_family = AF_INET;
	addr.sin_addr = getaddress(host);
	addr.sin_port = htons((short)atoi(cp));

	if(connect(so, (struct sockaddr *)&addr, (socklen_t)sizeof(addr)))
	{
		connectError();
		endSocket();
		return;
	}
	Allocate(buffer);
	Socket::state = SOCKET_CONNECTED;
}

void tcpstream::close(void)
{
	if(Socket::state == SOCKET_AVAILABLE)
		return;

	endStream();
	so = socket(AF_INET, SOCK_STREAM, 0);
	if(so != INVALID_SOCKET)
		Socket::state = SOCKET_AVAILABLE;
}

ostream &operator<<(ostream &os, InetAddress &ia)
{
	os << inet_ntoa(getaddress(ia));
	return os;
}

init_WSA::init_WSA() 
{
	//-initialize OS socket resources!

	if (WSAStartup(MAKEWORD(1, 1), &wsaData)) 
	{	
		abort();
	}
};

init_WSA init_wsa;
