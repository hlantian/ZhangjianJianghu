//---------------------------------------------------------------------------
//
// ycommand.cpp    2000年6月12日
//
// 类YCommand：负责命令短语分析及命令别名的处理
//
// 作者：叶林   单位：西陆资讯娱乐网
//
//---------------------------------------------------------------------------
#include "webmudcore.h"

//---------------------------------------------------------------
//命令别名处理
YString YCommand::translate(const YString command)
{
  YString tempcmd=command;
  YString commandVerb=tempcmd.getWord();
  if(commandVerb=="e") commandVerb="go 东";    //走路方向
  else if(commandVerb=="w") commandVerb="go 西";   //走路方向
  else if(commandVerb=="s") commandVerb="go 南";    //走路方向
  else if(commandVerb=="n") commandVerb="go 北"; //走路方向
  else if(commandVerb=="se") commandVerb="go 东南";  //走路方向
  else if(commandVerb=="ne") commandVerb="go 东北";  //走路方向
  else if(commandVerb=="sw") commandVerb="go 西南";    //走路方向
  else if(commandVerb=="nw") commandVerb="go 西北";    //走路方向
  else if(commandVerb=="u") commandVerb="go 上";    //走路方向
  else if(commandVerb=="eu") commandVerb="go 东上";   //走路方向
  else if(commandVerb=="su") commandVerb="go 南上";  //走路方向
  else if(commandVerb=="wu") commandVerb="go 西上";   //走路方向
  else if(commandVerb=="nu") commandVerb="go 北上";     //走路方向
  else if(commandVerb=="d") commandVerb="go 下";      //走路方向
  else if(commandVerb=="ed") commandVerb="go 东下";    //走路方向
  else if(commandVerb=="sd") commandVerb="go 南下";   //走路方向
  else if(commandVerb=="wd") commandVerb="go 西下";    //走路方向
  else if(commandVerb=="nd") commandVerb="go 北下";   //走路方向
  else if(commandVerb=="in") commandVerb="go 里面";   //走路方向
  else if(commandVerb=="enter") commandVerb="go 里面";  //走路方向
  else if(commandVerb=="out") commandVerb="go 外面";   //走路方向
  else if(commandVerb=="东") commandVerb="go 东";     //走路方向
  else if(commandVerb=="西") commandVerb="go 西";     //走路方向
  else if(commandVerb=="南") commandVerb="go 南";      //走路方向
  else if(commandVerb=="北") commandVerb="go 北";     //走路方向
  else if(commandVerb=="东南") commandVerb="go 东南";   //走路方向
  else if(commandVerb=="东北") commandVerb="go 东北";   //走路方向
  else if(commandVerb=="西南") commandVerb="go 西南";  //走路方向
  else if(commandVerb=="西北") commandVerb="go 西北";   //走路方向
  else if(commandVerb=="上") commandVerb="go 上";      //走路方向
  else if(commandVerb=="东上") commandVerb="go 东上";   //走路方向
  else if(commandVerb=="南上") commandVerb="go 南上";  //走路方向
  else if(commandVerb=="西上") commandVerb="go 西上";  //走路方向
  else if(commandVerb=="北上") commandVerb="go 北上";  //走路方向
  else if(commandVerb=="下") commandVerb="go 下";     //走路方向
  else if(commandVerb=="东下") commandVerb="go 东下";  //走路方向
  else if(commandVerb=="南下") commandVerb="go 南下";  //走路方向
  else if(commandVerb=="西下") commandVerb="go 西下";    //走路方向
  else if(commandVerb=="北下") commandVerb="go 北下";  //走路方向
  else if(commandVerb=="里面") commandVerb="go 里面";   //走路方向
  else if(commandVerb=="外面") commandVerb="go 外面"; //走路方向
  else if(commandVerb=="l") commandVerb = "look";   //看
  else if(commandVerb=="看") commandVerb = "look";   //看
  else if(commandVerb=="L") commandVerb = "look";   //看
  else if(commandVerb=="告诉") commandVerb = "tell";  //密谈
  else if(commandVerb=="密谈") commandVerb = "tell";  //密谈
  else if(commandVerb=="买") commandVerb = "buy";    //买东西
  else if(commandVerb=="卖") commandVerb = "sell";   //卖东西
  else if(commandVerb=="说") commandVerb = "say";    //房间内说话
  else if(commandVerb=="shuo") commandVerb = "say";    //房间内说话
  else if(commandVerb=="吃") commandVerb = "eat";    //吃东西
  else if(commandVerb=="chi") commandVerb = "eat";    //吃东西
  else if(commandVerb=="喝") commandVerb = "drink";  //喝水
  else if(commandVerb=="he") commandVerb = "drink";  //喝水
  else if(commandVerb=="穿") commandVerb = "wear";       //穿上
  else if(commandVerb=="chuan") commandVerb = "wear";    //穿上
  else if(commandVerb=="戴") commandVerb = "wear";    //穿上
  else if(commandVerb=="dai") commandVerb = "wear";    //穿上
  else if(commandVerb=="装备") commandVerb = "wield";  //装备
  else if(commandVerb=="zhuangbei") commandVerb = "wield";  //装备
  else if(commandVerb=="脱") commandVerb = "unwear";   //脱下
  else if(commandVerb=="tuo") commandVerb = "unwear";  //脱下
  else if(commandVerb=="卸下") commandVerb = "unwear";  //脱下
  else if(commandVerb=="xiexia") commandVerb = "unwear";  //脱下
  else if(commandVerb=="放下") commandVerb = "unwield";  //放下武器
  else if(commandVerb=="fangxia") commandVerb = "unwield";  //放下武器
  else if(commandVerb=="加力") commandVerb = "enforce";  //加力
  else if(commandVerb=="jiali") commandVerb = "enforce"; //加力
  else if(commandVerb=="体力") commandVerb = "hp";   //查看体力
  else if(commandVerb=="读") commandVerb = "read";  //读书
  else if(commandVerb=="jifa") commandVerb = "enable";   //激发武功
  else if(commandVerb=="激发") commandVerb = "enable";  //激发武功
  else if(commandVerb=="deposite") commandVerb = "cun"; //存钱
  else if(commandVerb=="存") commandVerb = "cun"; //存钱
  else if(commandVerb=="withdraw") commandVerb = "qu"; //取钱
  else if(commandVerb=="取") commandVerb = "qu"; //取钱
  else if(commandVerb=="杀") commandVerb = "kill";   //杀人
  else if(commandVerb=="duihuan") commandVerb = "convert";  //兑换钱
  else if(commandVerb=="兑换") commandVerb = "convert"; //兑换钱
  else if(commandVerb=="yun") commandVerb = "exert";   //运气
  else if(commandVerb=="运")  commandVerb = "exert";   //运气
  else if(commandVerb=="learn") commandVerb = "xue";   //学习武功
  else if(commandVerb=="学") commandVerb = "xue";      //学习武功
  else if(commandVerb=="cha") commandVerb = "skills";  //查看武功
  else if(commandVerb=="丢掉") commandVerb = "drop";  //丢物品
  else if(commandVerb=="diudiao") commandVerb = "drop"; //丢物品
  else if(commandVerb=="拣起") commandVerb = "get";     //拣东西
  else if(commandVerb=="jian") commandVerb = "get";     //拣东西
  else if(commandVerb=="跟随") commandVerb = "follow";     //跟随
  else if(commandVerb=="gensui") commandVerb = "follow";     //跟随
  else if(commandVerb=="聊天") commandVerb = "chat";    //聊天频道
  else if(commandVerb=="新手") commandVerb = "newbie";  //新手频道
  else if(commandVerb=="谣言") commandVerb = "rumor";   //谣言频道
  else if(commandVerb=="关闭") commandVerb = "vote chblk";   //关闭频道
  else if(commandVerb=="开启") commandVerb = "vote unchblk";   //开启频道
  else if(commandVerb=="关") commandVerb = "turn";   //关闭自己的频道
  else if(commandVerb=="拜") commandVerb = "bai";   //拜师
  else if(commandVerb=="打坐") commandVerb = "dazuo";   //打坐
  else if(commandVerb=="吐纳") commandVerb = "tuna";   //吐纳
  else if(commandVerb=="采矿") commandVerb = "caikuang";
  else if(commandVerb=="冶炼") commandVerb = "yelian";  
  else if(commandVerb=="打造") commandVerb = "dazao";   
  else if(commandVerb=="领悟") commandVerb = "lingwu";   
  else if(commandVerb=="练") commandVerb = "lian";   
  else if(commandVerb=="祈福") commandVerb = "qifu";   
  else if(commandVerb=="忏悔") commandVerb = "canhui";   
  else if(commandVerb=="赌大小") commandVerb = "daxiao";   
  else if(commandVerb=="赌点数") commandVerb = "dianshu";
  else if(commandVerb=="查") commandVerb = "list";   
  else if(commandVerb=="存任务") commandVerb = "cunquit";   
  else if(commandVerb=="照镜子") commandVerb = "lookfy";   
  else {
  	//do nothing
  }
  return commandVerb+" "+tempcmd;
}

