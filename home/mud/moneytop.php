<html>
<head>
<title>江湖富豪榜</title>
<META http-equiv=Content-Type content="text/html; charset=gb2312"><LINK 
href="http://www.qzmms.com/mud/images/bamboo.css" type=text/css rel=stylesheet>
</head>
<body bgcolor="#FAE6A9">
<p align=center><font color="#FF0000"><span style="font-size: 9pt">江湖富豪榜</span></font></p>
<font color="#FF9933"><span style="font-size: 9pt">
<?
    $server = mysql_pconnect("localhost","root","yinglei$");
    $db = mysql_select_db("lp");
    $sql = "delete from moneytop where inday = now()";
    mysql_query($sql,$server) or die($sql.'出错');
    $sql = "select name,sum(money) from money group by name";
    $rst = mysql_query($sql);
    while($row=mysql_fetch_array($rst)){
	    $sql = "insert into moneytop values ('".$row[0]."',".$row[1].",now())";
    	    mysql_query($sql,$server) or die($sql.'出错');
       }
       echo '<table border="0" cellspacing="0" cellpadding="0" align="center">';
       echo '<tr><td>排名</td><td>名字</td><td>金子</td></tr>';
       $i = 1;    
    $sql = "select name,money from moneytop where inday=now() order by money desc limit 10";
    $rst1 = mysql_query($sql);
    while($row1=mysql_fetch_array($rst1)){
	echo '<tr><td>'.$i.'</td><td>'.$row1[0].'</td><td>'.$row1[1].'</td></tr>';
	$i++;
       }
    echo '</table>';
    mysql_free_result($rst);
    mysql_free_result($rst1);
    mysql_close($server);
?>
</span></font>
<p align="center"><font color="#FF9933"><span style="font-size: 9pt">从今天开始江湖每天都会记录玩家的金钱情况，并有程序进行对比。</span></font></p>
</body>
</html>