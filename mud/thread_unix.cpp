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

#define _POSIX_PTHREAD_SCHEMATICS

#include "config.h"
#include "macros.h"
#include "thread.h"
#include <stdlib.h>

typedef	void	*(*exec_t)(void *);
typedef	RETSIGTYPE (*signal_t)(int);

#ifdef	_SIG_THREAD_CANCEL

static	RETSIGTYPE	sigcancel(int)
{
	pthread_exit(NULL);
}

#endif

#ifndef	_SIG_THREAD_STOPCONT
#ifndef _THR_SUNOS5

static	RETSIGTYPE	sigsuspend(int)
{
	sigset_t sigs;

	sigemptyset(&sigs);
	sigaddset(&sigs, SIGUSR3);
	sigwait(&sigs, NULL);
}
#endif
#endif

static	sigset_t *blocked_signals(sigset_t *sig)
{
	sigemptyset(sig);
	sigaddset(sig, SIGINT);
	sigaddset(sig, SIGKILL);
	sigaddset(sig, SIGHUP);
	sigaddset(sig, SIGABRT);
	sigaddset(sig, SIGALRM);
	sigaddset(sig, SIGPIPE);
#ifndef	_SIG_THREAD_STOPCONT
	sigaddset(sig, SIGUSR3);
#endif
	return sig;
}

class MainThread : public Thread
{
protected:
	void Run(void) {return;};
	void OnSignal(int signo) {exit(signo);};

public:
	MainThread() : Thread(true) {};
};

static	ThreadKey _self;
static	MainThread _mainthread;

Thread	*Thread::_main = NULL;

#ifndef	_SIG_THREAD_ALARM
Thread	*Thread::_timer = NULL;
Mutex	Thread::_arm;
#endif

Thread::Thread(bool flag)
{
	_tid = pthread_self();
	_parent = this;
	struct sigaction act;

	if(flag == true)
	{
		siginstall(SIGHUP);
		siginstall(SIGALRM);
		siginstall(SIGPIPE);
		siginstall(SIGABRT);

		act.sa_handler = (signal_t)&SignalHandler;
		sigemptyset(&act.sa_mask);
#ifdef	SA_RESTART
		act.sa_flags = SA_RESTART;
#else
		act.sa_flags = 0;
#endif
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
#ifdef	SIGPOLL
		sigaction(SIGPOLL, &act, NULL);
#else
		sigaction(SIGIO, &act, NULL);
#endif		

#ifndef	_SIG_THREAD_STOPCONT
#ifndef	_THR_SUNOS5
		act.sa_handler = sigsuspend;
		sigemptyset(&act.sa_mask);
#ifdef	SA_RESTART
		act.sa_flags = SA_RESTART;
#else
		act.sa_flags = 0;
#endif
		sigaction(SIGUSR3, &act, NULL);
#endif
#endif

#ifdef	_SIG_THREAD_CANCEL
		act.sa_flags = 0;
		act.sa_handler = sigcancel;
		sigemptyset(&act.sa_mask);
		sigaddset(&act.sa_mask, SIGHUP);
		sigaddset(&act.sa_mask, SIGALRM);
		sigaddset(&act.sa_mask, SIGPIPE);

		sigaction(_SIG_THREAD_CANCEL, &act, NULL);
#endif		
		_main = this;
    	}
	_self.setKey(this);
}	

Thread::Thread(Semaphore *start, int pri, size_t stack)
{
	static	bool initial = false;
	struct	sigaction act;
	int	rc;

	if(!initial)
	{
		First();
		initial = true;
	}

	pthread_attr_init(&_attr);
	pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setinheritsched(&_attr, PTHREAD_INHERIT_SCHED);

#ifdef	PTHREAD_STACK_MIN
	if(pthread_attr_setstacksize(&_attr,
		stack <= PTHREAD_STACK_MIN ? PTHREAD_STACK_MIN : stack))
			throw(this);
#endif

#ifdef	_POSIX_THREAD_PRIORITY_SCHEDULING	
	if(pri)
	{
		struct sched_param sched;
		int policy;

		policy = sched_getscheduler(0);
		if(policy < 0)
			throw(this);

		sched_getparam(0, &sched);

		pri = sched.sched_priority - pri;
		if(pri 	> sched_get_priority_max(policy))
			pri = sched_get_priority_max(policy);

		if(pri < sched_get_priority_min(policy))
			pri = sched_get_priority_min(policy);

		sched.sched_priority = pri;
		pthread_attr_setschedparam(&_attr, &sched);
	}	
#endif
	_parent = getThread();
	if(!_parent)
		_parent = this;

	_cancel = THREAD_CANCEL_INITIAL;
	_start = start;
	_tid = 0;

	if(_start)
	{
		rc = pthread_create(&_tid, &_attr, exec_t(&Execute), this);
		if(rc)
			throw(this);
	}
};

Thread::Thread(const Thread &th)
{
	sigset_t mask, newmask;
	int rc;

	_parent = th._parent;
	_cancel = THREAD_CANCEL_INITIAL;
	pthread_sigmask(SIG_BLOCK, blocked_signals(&newmask), &mask);
	rc = pthread_create(&_tid, &_attr, exec_t(&Execute), this);
	pthread_sigmask(SIG_SETMASK, &mask, NULL);
	if(rc)
		throw(this);
}

int Thread::Start(Semaphore *start)
{
	if(_tid)
	{
		if(_start)
		{
			_start->Post();
			return 0;
		}
		else
			return -1;
	}

	_start = start;
	return pthread_create(&_tid, &_attr, exec_t(&Execute), this);
}

void Thread::Terminate(void)
{
	if(!_tid)
		return;

	if(pthread_self() != _tid)
	{
		pthread_cancel(_tid);
		pthread_join(_tid, NULL);
	}
	_parent->Notify(this);
	_tid = pthread_self();
}

void Thread::SignalHandler(int signo)
{
	Thread	*th = getThread();

	switch(signo)
	{
	case SIGHUP:
		if(th)
			th->OnHangup();
		break;
	case SIGABRT:
		if(th)
			th->OnException();
		break;
	case SIGPIPE:
		if(th)
			th->OnDisconnect();
		break;
	case SIGALRM:
#ifndef	_SIG_THREAD_ALARM
		if(_timer)
		{
			_timer->_alarm = 0;
			_timer->OnTimer();
		}
		else
#endif 
		    if(th)
			th->OnTimer();
		break;
#ifdef	SIGPOLL
	case SIGPOLL:
#else
	case SIGIO:
#endif
		if(th)
			th->OnPolling();
		break;
	default:
		if(th)
			th->OnSignal(signo);
	}
}

void	Thread::Execute(Thread *th)
{
	sigset_t mask;
	pthread_t tid;

	pthread_sigmask(SIG_BLOCK, blocked_signals(&mask), NULL);
	_self.setKey(th);
	th->setCancel(THREAD_CANCEL_INITIAL);
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

		th->Run();
	}

#ifndef	_SIG_THREAD_ALARM
	if(th == _timer)
		--_arm;
#endif

	th->setCancel(THREAD_CANCEL_DISABLED);
	pthread_detach(th->_tid);
	th->_parent->Notify(th);
	th->Final();
	pthread_exit(NULL);
}

void	Thread::setTimer(timeout_t timer)
{
	sigset_t sigs;

	timer /= 1000;
#ifndef	_SIG_THREAD_ALARM	
	++_arm;
	_timer = this;
#endif
	time(&_alarm);
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGALRM);
	pthread_sigmask(SIG_UNBLOCK, &sigs, NULL);
	alarm(timer);
}	

timeout_t Thread::getTimer(void)
{
	time_t now;
	if(!_alarm)
		return 0;

	time(&now);
	return (timeout_t)(((now - _alarm) * 1000) + 500);
}

void Thread::endTimer(void)
{
	sigset_t sigs;
#ifndef	_SIG_THREAD_ALARM
	if(_timer != this)
		return;
#endif

	alarm(0);
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGALRM);
	pthread_sigmask(SIG_BLOCK, &sigs, NULL);
#ifndef	_SIG_THREAD_ALARM
	--_arm;
	_timer = NULL;
#endif
}

void	Thread::WaitSignal(signo_t signo)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, signo);
#if defined(_THR_SUNOS5)
	signo = sigwait(&mask);
#else
	sigwait(&mask, &signo);
#endif
}	

void	Thread::setSuspend(thread_suspend_t mode)
{
	sigset_t mask;

	sigemptyset(&mask);
	sigaddset(&mask, _SIG_THREAD_SUSPEND);

	switch(mode)
	{
	case THREAD_SUSPEND_ENABLE:
		pthread_sigmask(SIG_UNBLOCK, &mask, NULL);
		return;
	case THREAD_SUSPEND_DISABLE:
		pthread_sigmask(SIG_BLOCK, &mask, NULL);
	}
}

#ifdef	_SIG_THREAD_CANCEL

void	Thread::setCancel(thread_cancel_t mode)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, _SIG_THREAD_CANCEL);
	
	switch(mode)
	{
	case THREAD_CANCEL_IMMEDIATE:
		pthread_sigmask(SIG_UNBLOCK, &mask, NULL);
		break;
	case THREAD_CANCEL_INITIAL:
	case THREAD_CANCEL_DISABLED:
	case THREAD_CANCEL_DEFERRED:
		pthread_sigmask(SIG_BLOCK, &mask, NULL);
		break;
	}
	_cancel = mode;
}
#else

void	Thread::setSignal(int signo, bool mode)
{
	sigset_t sigs;

	sigemptyset(&sigs);
	sigaddset(&sigs, signo);

	if(mode)
		pthread_sigmask(SIG_UNBLOCK, &sigs, NULL);
	else
		pthread_sigmask(SIG_BLOCK, &sigs, NULL);
}	

void	Thread::setCancel(thread_cancel_t mode)
{
	switch(mode)
	{
	case THREAD_CANCEL_IMMEDIATE:
		pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		break;
	case THREAD_CANCEL_DEFERRED:
		pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		break;
	case THREAD_CANCEL_INITIAL:
	case THREAD_CANCEL_DISABLED:
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		break;
	default:
		mode = THREAD_CANCEL_INVALID;
	}
	if(mode != THREAD_CANCEL_INVALID)
		_cancel = mode;
}

#endif

void	Thread::Yield(void)
{
#ifdef	_SIG_THREAD_CANCEL
	sigset_t cancel, old;

	sigemptyset(&cancel);
	sigaddset(&cancel, _SIG_THREAD_CANCEL);

	if(_cancel != THREAD_CANCEL_DISABLED && 
	   _cancel != THREAD_CANCEL_INITIAL)
		pthread_sigmask(SIG_UNBLOCK, &cancel, &old);
#else
	pthread_testcancel();
#endif
#ifdef	HAVE_PTHREAD_YIELD
	pthread_yield();
#endif

#ifdef	_SIG_THREAD_CANCEL
	if(_cancel != THREAD_CANCEL_DISABLED)
		pthread_sigmask(SIG_SETMASK, &old, NULL);
#endif
}

void siginstall(int signo)
{
	struct sigaction act;
	
	act.sa_handler = (signal_t)&Thread::SignalHandler;
	sigemptyset(&act.sa_mask);

#ifdef	SA_INTERRUPT
	act.sa_flags = SA_INTERRUPT;
#else
	act.sa_flags = 0;
#endif
	sigaction(signo, &act, NULL);
}

Thread *getThread(void)
{
	return (Thread *)_self.getKey();
}
