var autoScrollOn = 1;
var scrollOnFunction;
var scrollOffFunction;

function scrollWindow( )
{
	if ( autoScrollOn == 1 ) {
		this.scroll(0, 65000);
		setTimeout('scrollWindow()', 200);
	}  // end if

}  // end scrollWindow

function scrollOn( )
{
	autoScrollOn = 1;
	scrollWindow( );
}  // end scrollOn

function scrollOff( )
{
	autoScrollOn = 0;
}  // end scrollOff

function StartUp( )        
{
	this.onblur  = scrollOnFunction;
	this.onfocus = scrollOffFunction;
	scrollWindow( );
	//genmenu();
	//document.onmouseup=showhidemenu;
}  // end StartUp

scrollOnFunction = new Function('scrollOn( )')
scrollOffFunction = new Function('scrollOff( )')
StartUp();

function sa(str) 
{
	//document.write("<a href=\'javascript:actor(\""+str+"\")\'>"+str+"</a>");
	//document.write("<a href=\"#\" onclack=actor(\""+str+"\")>"+str+"</a>");
	document.write("<span style=\"color=#0000ff;text-decoration:underline;cursor:hand;\" onclick=actor(\""+str+"\")>"+str+"</span>");
} 

//function actor(str) {return showmenu();} 
function actor(str) {addname(str);}
function thing(str){addname(str);}
function room(str){sendmsg("goto "+str);}

function addname(str) 
{
	top.main.document.frmCommand.tmpcmd.value += str;
}
 
function sendmsg(msg)
{
	top.main.send_msg(msg);
}

