#include <thread.h>
#include <iostream.h>
#include "yfifo.h"
#include "ystring.h"

class YFIFOBuffer : public Thread {
  public:
    YFIFOBuffer(YString FIFOName,YString content);
    //bool fin;
  protected:
		YFIFO* targetFIFO;
		YString m_content;
    virtual void Run(void);
//    virtual void Final(void);

};

long count;

int main(int argc, char* argv[])
{
	count=0;
	YFIFO bufferFIFO("/home/newmud/data/fifo/buffer.fifo","r");
	
	YString FIFOName;
	YString bigcontent;
	YString content;
	YFIFOBuffer* fifobuffer;
	while(true) {
		bigcontent=bufferFIFO.read();
		//cout<<"read: "<<bigcontent<<endl;
		while((content=bigcontent.getWord("\xff"))!="") {
			FIFOName=content.getWord();
			fifobuffer=new YFIFOBuffer(FIFOName,content);
			if(fifobuffer) fifobuffer->Start();
		}
	}
  return 0;
}
//---------------------------------------------------------------------------
YFIFOBuffer::YFIFOBuffer(YString FIFOName,YString content):m_content(content)
{
	//count++;
	//cout<<"Thread "<<count<<" starting...."<<endl;
	//cout<<"open FIFO "<<"/home/mud/data/fifo/"+FIFOName+".fifo"<<endl;
	targetFIFO=new YFIFO("/home/newmud/data/fifo/"+FIFOName+".fifo","w");
}
//---------------------------------------------------------------------------
void  YFIFOBuffer::Run(void)
{
	//cout<<"write "<<m_content<<" to "<<targetFIFO->getName()<<"....."<<endl;
	if(targetFIFO) targetFIFO->write(m_content);
	//cout<<"write "<<m_content<<" to "<<targetFIFO->getName()<<" OK."<<endl;
  //fin=true;
}
//---------------------------------------------------------------------------
/*void YFIFOBuffer::Final(void)
{
	cout<<"Thread "<<count<<" ended."<<endl;
	count--;	
	delete this;
}
*/