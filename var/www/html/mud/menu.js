function showmenu(n)
{
	if(selname==selfname) n=2;
	menu1=document.all.popmenu1;
	menu2=document.all.popmenu2;
	if(n==1) menu=menu1;
	else menu=menu2;
	newX = event.clientX + document.body.scrollLeft;
	newY = event.clientY + document.body.scrollTop;
	menu.style.pixelLeft = newX-2;
	menu.style.pixelTop = newY-2;
	if((menu1.style.display == "none")&&(menu2.style.display == "none")) {
		menu.style.display = "";
		menu.style.zIndex=document.MM_maxZ+1;
	}
	else {
		menu1.style.display = "none" ;
		menu2.style.display = "none" ;
	}
	return false;
}
function hidemenu() {
	document.all.popmenu1.style.display = "none";
	document.all.popmenu2.style.display = "none";
	amenu=false;
}
function smsg(s) {
	send_msg(s+" "+selname);
}
function smsg1(s,s1) {
	hidemenu();
	if(s1==null) s1=" ";
	else s1+=" ";
	document.frmCommand.tmpcmd.focus();
	document.frmCommand.tmpcmd.value = s+" "+selname+s1;
}
function genmenu()
{
	document.write("	<table id=popmenu1 class=box border=0 style=\"display:none\">");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'look\');\" class=cc>看</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'fight\');\" class=cc>较量武功</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'hit\');\" class=cc>强行较量</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg1(\'/tell\');\" class=cc>传音入密</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'follow\');\" class=cc>跟随</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'bai\');\" class=cc>拜师</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'touxi\');\" class=cc>偷袭</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'killget\');\" class=cc>杀人取物</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'killge\');\" class=cc>杀人取头</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"smsg(\'kill\');\" class=cc>决一死战</div></td></tr>");
	document.write("	</table>");
	document.write("	<table id=popmenu2 class=box border=0 style=\"display:none\">");
	document.write("	<tr><td><div onMouseDown=\"movehere();\" class=cc>移动至此</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'sleep\');\" class=cc>睡觉</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'info on\');\" class=cc>系统信息</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'enforce max\');\" class=cc>最大加力</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'enforce\');\" class=cc>取消加力</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'dazuo max\');\" class=cc>最大打坐</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'bskills\');\" class=cc>劳动技能</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'i\');\" class=cc>察看物品</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'hp\');\" class=cc>察看体力</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'skills\');\" class=cc>察看技能</div></td></tr>");
	document.write("	<tr><td><div onMouseDown=\"send_msg(\'score\');\" class=cc>察看状态</div></td></tr>");
	document.write("</table>");
}
