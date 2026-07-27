#调试
#CFLAGS := -g -ggdb -Wall -DHAVE_CONFIG_H -I/usr/include/g++-2 -I/usr/local/include -I/usr/include/mysql -I. -D__JAVACLIENT__ -D_REENTRANT -D_THREAD_SAFE -pthread -c  -fPIC -DPIC 

#时间分析
#PG= -pg

#普通
CFLAGS := $(PG) -g -DHAVE_CONFIG_H -I/usr/local/include/cc++2 -I/usr/include/mysql -I. -D__cplusplus -D_REENTRANT -D__JAVACLIENT__ -D_THREAD_SAFE -pthread -c  -fPIC -DPIC 
#CFLAGS := $(PG) -g -DHAVE_CONFIG_H -I/usr/include/g++-2 -I/usr/local/include -I/usr/include/mysql -I. -D_REENTRANT -D__JAVACLIENT__ -D_THREAD_SAFE -pthread -c  -fPIC -DPIC 


#优化
#CFLAGS :=  -O3 -Wall -DHAVE_CONFIG_H -I/usr/include/g++-2 -I/usr/local/include -I/usr/include/mysql -I. --D__JAVACLIENT__ D_REENTRANT -D_THREAD_SAFE -pthread -c  -fPIC -DPIC 

THREADFLAGS := -static -pthread   
MYSQLFLAGS := -I/usr/include/mysql   
MYSQLLIBS :=  -L/usr/lib/mysql  -lmysqlclient -lz
CRYPTLIBS := -lcrypt
POSIX1BLIBS :=
#POSIX1BLIBS := ../posix1b/semaphore.o
CC := g++ 
 
 
 
SOURCE := autobackup.cpp yfiledir.cpp ylocalfiledir.cpp yftpfiledir.cpp ysettings.cpp yautobackup.cpp yerr.cpp 

WEBMUDOBJS := ymudobject.o yproperty.o ypropertygroup.o yobjectgroup.o ytimer.o \
              ychat.o yabstractactor.o yabstractroom.o yabstractthing.o yuser.o yusermanager.o \
              yplayermanager.o ywebmud.o yfifo.o yfifo_unix.o yactor.o yplayer.o ynpc.o yroom.o ything.o \
              yerr.o ymudsettings.o yxiluuser.o ysession.o ysessionmanager.o yxiluusermanager.o \
              ymap.o ystring.o ystringlist.o ydatetime.o ycommand.o loadobject.o webmud.o \
              ycommandtranslate.o ycookroom.o yretiringroom.o ybankroom.o ypawnroom.o ylogfile.o yemote.o \
              yworkroom.o ynewplayerroom.o yyelianroom.o yteachernpc.o ywugong.o yquest.o ybetraynpc.o \
              ycollectroom.o yofferrewardnpc.o ystopwatch.o ycounter.o ydestroything.o ycomm.o\
              ymarrynpc.o ymoneynpc.o yjollityroom.o ymarryroom.o yjailroom.o ydoorroom.o yspecialnpc.o ywizard.o \
              yloadroom.o yliandanroom.o ychatmanager.o yfaction.o ylingwuroom.o ytailplayer.o yhidedoorroom.o ycangkuroom.o

LOGINOBJS :=yfifo.o yerr.o ymudsettings.o ystring.o writecgi.o readcgi.o login.o ylogfile.o ypropertygroup.o 

LOGIN1OBJS :=yfifo.o yfifo_unix.o yerr.o ymudsettings.o ystring.o writecgi.o readcgi.o login1.o ylogfile.o ypropertygroup.o ydatetime.o 

LOGINTESTOBJS :=yfifo.o yerr.o ymudsettings.o ystring.o writecgi.o readcgi.o logintest.o ylogfile.o ypropertygroup.o 

LOGIN_NSOBJS :=yfifo.o yerr.o ymudsettings.o ystring.o writecgi.o readcgi.o login_ns.o ylogfile.o ypropertygroup.o 

REGISTEROBJS :=yerr.o ystring.o writecgi.o readcgi.o register.o ylogfile.o 

COMMANDOBJS :=yfifo.o yerr.o ymudsettings.o ystring.o writecgi.o readcgi.o command.o ylogfile.o ypropertygroup.o ystopwatch.o ycounter.o ydatetime.o

FIFOBUFFEROBJS :=threadkey.o thread.o yfifo.o ystring.o fifobuffer.o ylogfile.o yerr.o ystopwatch.o ycounter.o

#CCXXOBJS := mutex.o semaphore.o friends.o
CCXXOBJS := -L/usr/local/lib -lccgnu2 -lz

WEBMUD_H :=webmud.h global.h debug.h ymudobject.h ystring.h ystringlist.h yproperty.h yobjectgroup.h ypropertygroup.h \
           ytimer.h yabstractactor.h yabstractroom.h ychat.h yabstractthing.h yuser.h ywebmud.h \
           yusermanager.h yplayermanager.h yfifo.h yactor.h yplayer.h ynpc.h yroom.h ything.h yerr.h \
           ymudsettings.h ysessionmanager.h ysession.h yxiluusermanager.h yxiluuser.h ymap.h ydatetime.h \
           ycommand.h loadobject.h ycookroom.h yretiringroom.h ybankroom.h ypawnroom.h ylogfile.h yemote.h \
           yworkroom.h ynewplayerroom.h yjollityroom.h ymarryroom.h yteachernpc.h ywugong.h yquest.h yfifo_shm.h \
	   ystopwatch.h ycounter.h ymarrynpc.h ymoneynpc.h ytailplayer.h yhidedoorroom.h ycangkuroom.h\
           yyelianroom.h ydoorroom.h ydestroything.h ycomm.h yloadroom.h yliandanroom.h ychatmanager.h yfaction.h ylingwuroom.h


LIBS := -L/usr/lib -lpthread 
 
INCLUDES := -I/usr/local/include/cc++

THREADOBJS :=

all : webmud
 
webmud : $(WEBMUDOBJS) 
	$(CC) $(THREADFLAGS) $(LIBS) -o webmud $(POSIX1BLIBS) $(WEBMUDOBJS) $(CCXXOBJS) $(PG)

messageserver : $(MESSAGESERVEROBJS) 
	$(CC) $(THREADFLAGS) $(LIBS) -o messageserver $(MESSAGESERVEROBJS) $(CCXXOBJS) $(POSIX1BLIBS)

command : $(COMMANDOBJS) 
	$(CC) $(THREADFLAGS) $(LIBS) -o command $(COMMANDOBJS) $(CCXXOBJS) $(POSIX1BLIBS)

login : $(LOGINOBJS) 
	$(CC) $(THREADFLAGS) $(LIBS) -o login $(LOGINOBJS) $(CCXXOBJS) $(POSIX1BLIBS)

login1 : $(LOGIN1OBJS) 
	$(CC) $(THREADFLAGS) $(LIBS) -o login1 $(LOGIN1OBJS) $(CCXXOBJS) $(POSIX1BLIBS) $(MYSQLLIBS)

register : $(REGISTEROBJS) 
	$(CC) $(THREADFLAGS) -o register $(REGISTEROBJS) $(CCXXOBJS) $(POSIX1BLIBS)  $(INCLUDES) $(LIBS) $(MYSQLLIBS)
	
logintest : $(LOGINTESTOBJS) 
	$(CC) $(THREADFLAGS) $(LIBS) -o logintest $(LOGINTESTOBJS) $(CCXXOBJS) $(POSIX1BLIBS)

login_ns : $(LOGIN_NSOBJS) 
	$(CC) $(THREADFLAGS) $(LIBS) -o login_ns $(LOGIN_NSOBJS) $(CCXXOBJS) $(POSIX1BLIBS)

fifobuffer : $(FIFOBUFFEROBJS)
	$(CC) $(THREADFLAGS) $(LIBS) -o fifobuffer $(FIFOBUFFEROBJS) $(CCXXOBJS) $(POSIX1BLIBS)

fifotest : fifotestw fifotestr

fifotestw : fifotestw.o yfifo.o ystring.o yerr.o
	$(CC) $(THREADFLAGS) $(LIBS) -o fifotestw fifotestw.o yfifo.o ystring.o yerr.o

fifotestr : fifotestr.o yfifo.o ystring.o yerr.o
	$(CC) $(THREADFLAGS) $(LIBS) -o fifotestr fifotestr.o yfifo.o ystring.o yerr.o

install :
	cp webmud.conf /home/httpd/cgi-bin/mud
	cp webmud.conf /home/mud/bin
	cp webmud /home/mud/bin
	cp messageserver /home/mud/bin
	cp login /home/httpd/cgi-bin/mud
	cp login1 /home/httpd/cgi-bin/mud
	cp register /home/httpd/cgi-bin/mud
	cp login_ns /home/httpd/cgi-bin/mud
	cp command /home/httpd/cgi-bin/mud

install_register : register
	cp register /var/www/cgi-bin/mud/

clean :
	rm -f *.o

newmemfile :
	rm /home/mud/memfile
	cp /home/mud/memfile.new /home/mud/memfile

ystring.o : ystring.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ystring.o -c ystring.cpp

ystringlist.o : ystringlist.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ystringlist.o -c ystringlist.cpp

ymudobject.o : ymudobject.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ymudobject.o -c ymudobject.cpp

yproperty.o : yproperty.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yproperty.o -c yproperty.cpp

ypropertygroup.o : ypropertygroup.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ypropertygroup.o -c ypropertygroup.cpp

yobjectgroup.o : yobjectgroup.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yobjectgroup.o -c yobjectgroup.cpp

ytimer.o : ytimer.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ytimer.o -c ytimer.cpp

threadkey.o : threadkey_unix.cpp thread.h config.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o threadkey.o -c threadkey_unix.cpp

thread.o : thread_unix.cpp thread.h config.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o thread.o -c thread_unix.cpp

ychat.o : ychat.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ychat.o -c ychat.cpp

yemote.o : yemote.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yemote.o -c yemote.cpp

yabstractactor.o : yabstractactor.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yabstractactor.o -c yabstractactor.cpp

yabstractroom.o : yabstractroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yabstractroom.o -c yabstractroom.cpp

yabstractthing.o : yabstractthing.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yabstractthing.o -c yabstractthing.cpp

yuser.o : yuser.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yuser.o -c yuser.cpp

yusermanager.o : yusermanager.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yusermanager.o -c yusermanager.cpp

yplayermanager.o : yplayermanager.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yplayermanager.o -c yplayermanager.cpp

ywebmud.o : ywebmud.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ywebmud.o -c ywebmud.cpp

yfifo_unix.o : yfifo_unix.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yfifo_unix.o -c yfifo_unix.cpp
	
#yfifo.o : yfifo_unix.cpp $(WEBMUD_H)
#	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yfifo.o -c yfifo_unix.cpp
#yfifo.o : yfifo.cpp $(WEBMUD_H)
#	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yfifo.o -c yfifo.cpp
yfifo.o : yfifo_shm.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yfifo.o -c yfifo_shm.cpp

fifotestw.o : fifotestw.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o fifotestw.o -c fifotestw.cpp

fifotestr.o : fifotestr.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o fifotestr.o -c fifotestr.cpp

ylogfile.o : ylogfile.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ylogfile.o -c ylogfile.cpp

socket.o : socket_unix.cpp thread.h config.h socket.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o socket.o -c socket_unix.cpp

yactor.o : yactor.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yactor.o -c yactor.cpp

yplayer.o : yplayer.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yplayer.o -c yplayer.cpp

ynpc.o : ynpc.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ynpc.o -c ynpc.cpp

yroom.o : yroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yroom.o -c yroom.cpp

ything.o : ything.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ything.o -c ything.cpp

ydestroything.o : ydestroything.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ydestroything.o -c ydestroything.cpp

yerr.o : yerr.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yerr.o -c yerr.cpp

ymudsettings.o : ymudsettings.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ymudsettings.o -c ymudsettings.cpp

yxiluuser.o : yxiluuser.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yxiluuser.o -c yxiluuser.cpp

ysession.o : ysession.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ysession.o -c ysession.cpp

ysessionmanager.o : ysessionmanager.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ysessionmanager.o -c ysessionmanager.cpp

yxiluusermanager.o : yxiluusermanager.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS) $(MYSQLFLAGS) -o yxiluusermanager.o -c yxiluusermanager.cpp

ymap.o : ymap.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ymap.o -c ymap.cpp

ydatetime.o : ydatetime.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ydatetime.o -c ydatetime.cpp

ycommand.o : ycommand.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ycommand.o -c ycommand.cpp

loadobject.o : loadobject.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o loadobject.o -c loadobject.cpp

webmud.o : webmud.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o webmud.o -c webmud.cpp

writecgi.o : writecgi.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o writecgi.o -c writecgi.cpp

readcgi.o : readcgi.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o readcgi.o -c readcgi.cpp

login.o : login.cpp readcgi.h writecgi.h ystring.h yfifo.h ymudsettings.h yerr.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o login.o -c login.cpp

login1.o : login1.cpp readcgi.h writecgi.h ystring.h yfifo.h ymudsettings.h yerr.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o login1.o -c login1.cpp

register.o : register.cpp readcgi.h writecgi.h ystring.h yfifo.h ymudsettings.h yerr.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o register.o -c register.cpp

logintest.o : logintest.cpp readcgi.h writecgi.h ystring.h yfifo.h ymudsettings.h yerr.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o logintest.o -c logintest.cpp

login_ns.o : login.cpp readcgi.h writecgi.h ystring.h yfifo.h ymudsettings.h yerr.h
	$(CC) -D__NETSCAPE__ $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o login_ns.o -c login.cpp

inaddr_unix.o : inaddr_unix.cpp $(WEBMUD_H) thread.h config.h socket.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o inaddr_unix.o -c inaddr_unix.cpp

messageserver.o : messageserver_unix.cpp ystring.h config.h macros.h thread.h socket.h yfifo.h ymudsettings.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o messageserver.o -c messageserver_unix.cpp

command.o : command.cpp readcgi.h writecgi.h ystring.h yfifo.h ymudsettings.h yerr.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o command.o -c command.cpp
	
fifobuffer.o : fifobuffer.cpp ystring.h yfifo.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o fifobuffer.o -c fifobuffer.cpp

ycommandtranslate.o : ycommandtranslate.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ycommandtranslate.o -c ycommandtranslate.cpp

ycookroom.o : ycookroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ycookroom.o -c ycookroom.cpp

yretiringroom.o : yretiringroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yretiringroom.o -c yretiringroom.cpp

ypawnroom.o : ypawnroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ypawnroom.o -c ypawnroom.cpp

ybankroom.o : ybankroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ybankroom.o -c ybankroom.cpp

yworkroom.o : yworkroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yworkroom.o -c yworkroom.cpp

ynewplayerroom.o : ynewplayerroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ynewplayerroom.o -c ynewplayerroom.cpp

ycollectroom.o : ycollectroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ycollectroom.o -c ycollectroom.cpp

yyelianroom.o : yyelianroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yyelianroom.o -c yyelianroom.cpp

ymarryroom.o : ymarryroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ymarryroom.o -c ymarryroom.cpp 

yjollityroom.o : yjollityroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yjollityroom.o -c yjollityroom.cpp

yjailroom.o : yjailroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yjailroom.o -c yjailroom.cpp

ydoorroom.o : ydoorroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ydoorroom.o -c ydoorroom.cpp

yloadroom.o : yloadroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yloadroom.o -c yloadroom.cpp

yliandanroom.o : yliandanroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yliandanroom.o -c yliandanroom.cpp

ymoneynpc.o : ymoneynpc.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ymoneynpc.o -c ymoneynpc.cpp

ymarrynpc.o : ymarrynpc.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ymarrynpc.o -c ymarrynpc.cpp

yteachernpc.o : yteachernpc.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yteachernpc.o -c yteachernpc.cpp 

ybetraynpc.o : ybetraynpc.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ybetraynpc.o -c ybetraynpc.cpp

yspecialnpc.o : yspecialnpc.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yspecialnpc.o -c yspecialnpc.cpp

yofferrewardnpc.o : yofferrewardnpc.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yofferrewardnpc.o -c yofferrewardnpc.cpp

ywugong.o : ywugong.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ywugong.o -c ywugong.cpp

yquest.o : yquest.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yquest.o -c yquest.cpp
	
ysemaphore.o : ysemaphore.c ysemaphore.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ysemaphore.o -c ysemaphore.c

globalnew.o : globalnew.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o globalnew.o -c globalnew.cpp

yalloc.o : yalloc.cpp yalloc.h
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yalloc.o -c yalloc.cpp

ystopwatch.o : ystopwatch.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ystopwatch.o -c ystopwatch.cpp

ycounter.o : ycounter.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ycounter.o -c ycounter.cpp

ycomm.o : ycomm.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ycomm.o -c ycomm.cpp

ywizard.o : ywizard.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ywizard.o -c ywizard.cpp

ychatmanager.o : ychatmanager.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ychatmanager.o -c ychatmanager.cpp

yfaction.o : yfaction.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yfaction.o -c yfaction.cpp

ylingwuroom.o : ylingwuroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ylingwuroom.o -c ylingwuroom.cpp

ytailplayer.o : ytailplayer.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ytailplayer.o -c ytailplayer.cpp

yhidedoorroom.o : yhidedoorroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o yhidedoorroom.o -c yhidedoorroom.cpp

ycangkuroom.o : ycangkuroom.cpp $(WEBMUD_H)
	$(CC) $(CFLAGS) $(INCLUDES) $(THREADFLAGS)  -o ycangkuroom.o -c ycangkuroom.cpp
