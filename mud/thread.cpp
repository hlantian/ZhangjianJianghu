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
#include <process.h>

typedef	unsigned (__stdcall *exec_t)(void *);

class MainThread : public Thread
{
protected:
	void Run(void) {return;};
public:
	MainThread() : Thread(true) {};
};

static ThreadKey _self;
static MainThread _mainthread;

Thread *Thread::_main = NULL;

Thread *getThread(void)
{
	return (Thread *)_self.getKey();
}

DWORD waitThread(HANDLE hRef, timeout_t timeout)
{
	Thread *th = getThread();

	if(th)
		return th->WaitHandle(hRef, timeout);
	else
		return WaitForSingleObject(hRef, timeout);
}


void  delay(timeout_t timeout)
{
	Thread *th = getThread();
	if(th)
		th->Sleep(timeout);
	else
		SleepEx(timeout, FALSE);
}

void yield(void)
{
	Thread *th = getThread();
	if(th)
		th->Yield();
	else
		SleepEx(0, FALSE);
}

Thread::Thread(bool flag)
{
	_tid = GetCurrentThreadId();
	_parent = this;

	if(flag)
	{
		_main = this;
		_cancellation = CreateEvent(NULL, true, false, NULL);
	}

	_self.setKey(this);
};

Thread::Thread(Semaphore *start, int pri, unsigned stack)
{
	if(!_main)
	{
		_self.setKey(NULL);
		_main = this;
	}

	_tid = 0;
	_parent = getThread();
	if(!_parent)
		_parent = this;
	_hThread = (HANDLE)_beginthreadex(NULL, stack, (exec_t)&Execute, (void *)this, CREATE_SUSPENDED, (unsigned *)&_tid);
	_cancellation = CreateEvent(NULL, true, false, NULL);
	_start = start;
	setCancel(THREAD_CANCEL_INITIAL);

	if(!_hThread)
	{
		throw(this);
		return;
	}

	switch(pri)
	{
	case 1:
		pri = THREAD_PRIORITY_ABOVE_NORMAL;
		break;
	case -1:
		pri = THREAD_PRIORITY_BELOW_NORMAL;
		break;
	case 2:
		pri = THREAD_PRIORITY_HIGHEST;
		break;
	case -2:
		pri = THREAD_PRIORITY_LOWEST;
	default:
		pri = THREAD_PRIORITY_NORMAL;
	}

	SetThreadPriority(_hThread, pri);
	if(_start)
		ResumeThread(_hThread);
};

int Thread::Start(Semaphore *start)
{
	_start = start;
	ResumeThread(_hThread);
	return 0;
}	

void Thread::Terminate(void)
{
	if(!_tid)
		return;

	if(_tid == GetCurrentThreadId())
		return;

	switch(_cancel)	{
	case THREAD_CANCEL_IMMEDIATE:
		TerminateThread(_hThread, 0);
		break;
	default:
		SetEvent(_cancellation);
	}	
	WaitForSingleObject(_hThread, INFINITE);
	_parent->Notify(this);
	CloseHandle(_hThread);
	CloseHandle(_cancellation);
	_tid = GetCurrentThreadId();
}

unsigned __stdcall Thread::Execute(Thread *th)
{
	_self.setKey(th);
	th->Yield();
	if(th->_start)
	{
		th->_start->Wait();
		th->_start = NULL;
	}

	if(!setjmp(th->_env))
 	{
		th->Initial();
		if(th->getCancel() == THREAD_CANCEL_INITIAL) 
			th->setCancel(THREAD_CANCEL_DEFAULT);

		if(!setjmp(th->_env))
			th->Run();
	}

	th->setCancel(THREAD_CANCEL_DISABLED);
	th->_parent->Notify(th);
	th->Final();
	return 0;
}

void Thread::Yield(void)
{
	if(_cancel == THREAD_CANCEL_DISABLED)
		SleepEx(0, FALSE);
	else if(WaitForSingleObject(_cancellation, 0) == WAIT_OBJECT_0)
		Exit();
}

void Thread::Sleep(timeout_t timeout) 
{
	if(_cancel == THREAD_CANCEL_DISABLED)
		SleepEx(timeout, FALSE);
	else if(WaitForSingleObject(_cancellation, timeout) == WAIT_OBJECT_0)
		Exit();
}

DWORD Thread::WaitHandle(HANDLE obj, timeout_t timeout) 
{
	HANDLE objects[2];
	DWORD stat;

	objects[0] = _cancellation;
	objects[1] = obj;

	if(_cancel == THREAD_CANCEL_DISABLED)
		return WaitForSingleObject(obj, timeout);

	switch(stat = WaitForMultipleObjects(2, objects, false, timeout)) 	{
	case WAIT_OBJECT_0:
		Exit();
	case WAIT_OBJECT_0 + 1:
		return WAIT_OBJECT_0;
	default:
		return stat;
	}
}

void Thread::setCancel(thread_cancel_t cancel)
{
	switch(cancel)	
	{
	case THREAD_CANCEL_DEFERRED:
	case THREAD_CANCEL_IMMEDIATE:
		_cancel = cancel;
		Yield();
		break;
	case THREAD_CANCEL_DISABLED:
	case THREAD_CANCEL_INITIAL:
		_cancel = cancel;
	}
}	
