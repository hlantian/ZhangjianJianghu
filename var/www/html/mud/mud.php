<HTML>
<HEAD>
<BODY leftMargin=0 background="http://mud.362200.org/images/club_login_bg.gif" topMargin=0 
MARGINHEIGHT="0" MARGINWIDTH="0">

<META http-equiv=Content-Type content="text/html; charset=gb2312"><LINK 
href="http://mud.362200.org/images/bamboo.css" type=text/css rel=stylesheet> 
     <TABLE height=245 cellSpacing=0 cellPadding=0 width=173 
      background=http://mud.362200.org/images/club_login_bg.gif border=0 id="table1">
        <TBODY>
        <TR>
          <TD vAlign=top width=173>
            <TABLE height=196 cellSpacing=0 cellPadding=0 width=132 align=center 
            border=0 id="table2">
              <TBODY>
              <TR>
                <TD height=51>　</TD></TR>
              <TR>
                <TD vAlign=top>
                  <TABLE class=tableBorder1 height=118 cellSpacing=1 
                  cellPadding=3 width=170 align=center id="table3">
                    <TBODY>
                    <TR>
                      <TD class=tableBody1 align=middle width=180 height=65>
                        <TABLE cellSpacing=0 cellPadding=0 width=142 
                        align=center height="112" id="table4">
         <form target="_blank" method="POST" action="http://zjjh.362200.org/cgi-bin/mud/login1">

                          <TBODY>
                          <TR>
                            <TD class=tablebody1 align=middle width="100%" 
                            height=40 colspan="2">
                              <P style="margin-top: 2px; margin-bottom: 2px">姓名 <INPUT maxLength=16 size=12 name=name> 
                              <BR>密码 <INPUT type=password maxLength=20 size=12 
                              name=password> <BR><font color="#ff6600">目前在线人数:
<?
$fd = fopen("http://zjjh.362200.org/home/mud/data/playercount.dat", "r");
echo fread($fd, 512);
fclose($fd);
?>
</font></P>
                             	<p style="margin-top: 2px; margin-bottom: 2px">
                             <input type="image" src="http://mud.362200.org/images/login_01.gif" name="I1" width="55" height="17"> 
								</TD></TR>
                          <TR>
                            <TD class=tablebody1 align=middle width="50%" 
                            height=17>
                              <a target="_blank" href="http://zjjh.362200.org/home/mud/upass.php">密码修改</a></TD>
                            <TD class=tablebody1 align=middle width="50%" 
                            height=17>
								<a target="_blank" href="http://zjjh.362200.org/cgi-bin/mud/register">注册帐号</a></TD></TR>
                          <TR>
                            <TD class=tablebody1 align=middle width="100%" 
                            height=17 colspan="2">
                              <a target="_blank" href="http://zjjh.362200.org/home/mud/level.php">武功与经验对比</a></TD></TR></FORM></TBODY></TABLE></TD></TR></TBODY></TABLE></TD></TR></TBODY></TABLE></TD></TR></TBODY></TABLE>
      