//---------------------------------------------------------------------------

#pragma hdrstop
//---------------------------------------------------------------------------
#pragma argsused

#include <iostream.h>
#include <fstream.h>
#include "ymudobject.h"
#include "ypropertygroup.h"

int main(int argc, char* argv[])
{
  YMUDObject obj;
  YPropertyGroup& pg=*(obj.getProperties());
  pg.set("姓名","张三");
  pg.set("姓名",123);
  pg.set("年龄",20);
  pg.set("身高",1.75);
  pg.set("体重",68);
  pg.set("描述","别人笑我太疯癫\n我笑他人看不穿\n不见五陵豪杰墓\n无花无酒锄作田");
  cout<<"姓名："<<pg.getAsString("姓名")<<endl;
  pg.set("姓名","李四");
  cout<<"姓名："<<pg.getAsString("姓名")<<endl;
  cout<<"姓名："<<pg.getAsLong("姓名")<<endl;
  cout<<"年龄："<<pg.getAsLong("年龄")<<endl;
  cout<<"身高："<<pg.getAsFloat("身高")<<endl;
  cout<<"体重："<<pg.getAsLong("体重")<<endl;
  pg.save(cout);
  fstream datafile("pgtest.txt");
  pg.save(datafile);
  cin.get();
  cout<<"exist(\"身高\")="<<pg.exist("身高")<<endl;
  cout<<"exist(\"(不存在)身高\")="<<pg.exist("(不存在)身高")<<endl;
  pg.save(cout);
  cin.get();
  cout<<"身高(不存在)："<<pg.getAsFloat("(不存在)身高")<<endl;
  cout<<"姓名(不存在)："<<pg.getAsString("(不存在)姓名")<<endl;
  cout<<"ALL:"<<endl;
  pg.save(cout);
  cin.get();
  cout<<"新的YPropertyGroup: \n";
  YPropertyGroup pg1(&obj);
  datafile.seekg(0);
  pg1.load(datafile);
  pg1.save(cout);
  cin.get();
  return 0;
}
//---------------------------------------------------------------------------

