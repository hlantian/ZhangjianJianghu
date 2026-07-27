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


#ifndef	__CCXX_MACROS_H__
#define	__CCXX_MACROS_H__

// Commonly used Common C++ macros

#define	ENTER_CRITICAL	EnterMutex();
#define	LEAVE_CRITICAL	LeaveMutex();
#define	ENTER_DEFERRED	setCancel(THREAD_CANCEL_DEFERRED);
#define LEAVE_DEFERRED 	setCancel(THREAD_CANCEL_IMMEDIATE);

// These macros override common functions with thread-safe versions. In
// particular the common "libc" sleep() has problems since it normally
// uses SIGARLM (as actually defined by "posix").  The pthread_delay and
// usleep found in libpthread are gaurenteed not to use SIGALRM and offer
// higher resolution. 

#define	sleep(x)	ccxx_sleep((x) * 1000)
#define	delay(x)	ccxx_sleep(x)
#define	yield()		ccxx_yield()

// Some tests for DLL relared macros.

#ifndef	__EXPORT
#define	__EXPORT
#endif

#ifndef	__DLL
#define	__DLL
#endif

#endif

// Hide class names so they do not collide with other C++ libraries.
// Macros are used to provide a portable means of hiding rather than
// relying on namespace support.

#define RandomFile		cc_RandomFile
#define File			cc_File
#define NewFile			cc_NewFile
#define NamedPipe		cc_NamedPipe
#define MappedFile		cc_MappedFile
#define ThreadFile		cc_ThreadFile
#define SharedFile		cc_SharedFile
#define	Socket			cc_Socket
#define	TCPSocket		cc_TCPSocket
#define	TCPStream		cc_TCPStream
#define	TCPSession		cc_TCPSession
#define	UDPSocket		cc_UDPSocket
#define	UDPBroadcast		cc_UDPBroadcast
#define	UDPTransmit		cc_UDPTransmit
#define	UDPReceive		cc_UDPReceive
#define	UDPDuplex		cc_UDPDuplex
#define	SocketPort		cc_SocketPort
#define	TimerPort		cc_TimerPort
#define	SocketService		cc_SocketService
#define InetAddress		cc_InetAddress 
#define InetMaskAddress		cc_InetMaskAddress
#define InetHostAddress		cc_InetHostAddress
#define BroadcastAddress	cc_BroadcastAddress
#define Mutex			cc_Mutex
#define MutexCounter		cc_MutexCounter
#define	AtomicCounter		cc_AtomicCounter
#define Semaphore		cc_Semaphore
#define Event			cc_Event
#define Buffer			cc_Buffer
#define FixedBuffer		cc_FixedBuffer
#define Pipe			cc_Pipe
#define Thread			cc_Thread
#define	ThreadKey		cc_ThreadKey
#define	MemPager		cc_MemPager
#define	Keydata			cc_Keydata
#define	PersistException	cc_PersistException
#define	TypeManager		cc_TypeManager
#define	BaseObject		cc_BaseObject
#define	Engine			cc_Engine
#define	Vector2D		cc_Vector2D
#define	Serial			cc_Serial
#define	Slog			cc_Slog
#define	Dir			cc_Dir
#define	FIFOSession		cc_FIFOSession
#define	SharedMemPager		cc_SharedMemPager
#define	ScriptCommand		cc_ScriptCommand
#define	ScriptSymbol		cc_ScriptSymbol
#define	ScriptInterp		cc_ScriptInterp
#define	ScriptImage		cc_ScriptImage

