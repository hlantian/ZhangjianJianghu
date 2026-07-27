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
// If you write modifications of your own for Common C++, it is your
// choice whether to permit this exception to apply to your modifications.
// If you do not wish that, delete this exception notice.  

#include "config.h"
#include "thread.h"
#include "socket.h"
#include <string.h>
#include <stdlib.h>

InetAddress::InetAddress() 
{
	memset(&ipaddr, 0, sizeof(in_addr));
};

InetAddress::InetAddress(const char *address)
{
	*(long *)(&ipaddr) = inet_addr(address);
};

InetAddress::InetAddress(struct in_addr addr)
{
	ipaddr = addr;
};

bool InetAddress::isInetAddress(void)
{
	struct in_addr addr;
	memset(&addr, 0, sizeof(addr));
	if(memcmp(&addr, &ipaddr, sizeof(addr)))
		return true;
	return false;
}

InetAddress &InetAddress::operator=(struct in_addr addr){
	ipaddr = addr;
	return *this;
}

InetAddress &InetAddress::operator=(char *str)
{
	*(long *)&ipaddr = inet_addr(str);
	return *this;
}

bool InetAddress::operator==(InetAddress &a)
{
	if(memcmp((char *)&ipaddr, (char *)&a.ipaddr, sizeof(ipaddr)))
		return false;

	return true;
}

InetHostAddress &InetHostAddress::operator&=(InetMaskAddress &ma)
{
	struct in_addr mask = getaddress(ma);
	unsigned char *a = (unsigned char *)&ipaddr;
	unsigned char *m = (unsigned char *)&mask;
	size_t i;
	
	for(i = 0; i < sizeof(ipaddr); ++i)
		*(a++) &= *(m++);

	return *this;
}	

bool InetAddress::operator!=(InetAddress &a)
{
	if(memcmp((char *)&ipaddr, (char *)&a.ipaddr, sizeof(ipaddr)))
		return true;

	return false;
}

InetHostAddress::InetHostAddress(struct in_addr addr) : InetAddress(addr)
{};

InetHostAddress::InetHostAddress(const char *host) : InetAddress("127.0.0.1"){
	struct hostent *hp;
	struct in_addr **bptr;
	char	hostname[256];
	
	if(!host)	{
		if(gethostname(hostname, sizeof(hostname)))		{
			throw((InetAddress *)this);
			return;
		}
		host = hostname;
	}

	if(*host >= '0' && *host <= '9')	{
		*(long *)(&ipaddr) = inet_addr(host);
	}
	else	{
		hp = gethostbyname(host);
		if(!hp)
			throw(this);

		bptr = (struct in_addr **)hp->h_addr_list;
		while(*bptr != NULL)
			++bptr;
		--bptr;
		ipaddr = **bptr; 

	}
};

BroadcastAddress::BroadcastAddress(const char *net) : 
InetAddress(net)
{
};

InetMaskAddress::InetMaskAddress(const char *mask) 
{	
	unsigned long	x = 0xffffffff;
	int	l = 32 - atoi(mask);

	char *cp =(char*) strchr(mask, '.');
	if(cp)	{
		*(long *)&ipaddr = inet_addr(mask);
		return;
	}

	if(l < 1 || l > 32)	{
		throw((InetAddress *)this);
		return;
	}

	*(unsigned long *)&ipaddr = htonl(x << l);
};

char *InetAddress::getHostname(void)
{
	struct hostent *hp;
	struct in_addr addr0;

	memset(&addr0, 0, sizeof(addr0));
	if(!memcmp(&addr0, &ipaddr, sizeof(addr0)))
		return NULL;

	hp = gethostbyaddr((char *)&ipaddr, sizeof(ipaddr), AF_INET);
	
	if(hp)
		return hp->h_name;
	else
		return inet_ntoa(ipaddr);
}

InetHostAddress operator&(InetHostAddress &addr, InetMaskAddress &mask)
{
	InetHostAddress temp = addr;
	temp &= mask;
	return temp;
}


