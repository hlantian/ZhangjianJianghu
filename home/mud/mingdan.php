因前段时间注册出了问题，导致15号以后注册玩家信息不全，现在公布信息不全玩家名称<br>
因为江湖刚刚起步，很多地方要完善，注册页面暂时关闭了，这部分玩家数据等候讨论处理。<br>
对于这次事件，我深深的表示歉意。                   ---意随<br>

<?
    $server = mysql_pconnect("localhost","root","yinglei$");
    $db = mysql_select_db("lp");
    $sql = "select name from mytest where trim(backpass)='' or backpass is null";
       $rst = mysql_query($sql);
       $num_fields = mysql_num_fields($rst);
       $i = 0;
       $j = 0;
       echo '<table border="1" cellspacing="0" cellpadding="0">';
       while($i<$num_fields){
          $fields[$i] = mysql_field_name($rst,$i);
          $i++;
       }
       echo '<table border="1" cellspacing="0" cellpadding="0">';
       while($row=mysql_fetch_array($rst)){
          echo '<tr>';
          reset($fields);
          while(list(,$field_name)=each($fields)){
             $field_value = $row[$field_name];
             if($field_value==""){
                echo '<td>&nbsp;</td>';
             }
             else{
                echo "<td>$field_value</td>";
             }
          }
          echo '</tr>';
	  $j++;
       }
       echo '</table>';
       mysql_free_result($rst);
       echo "共".$j."人";
    mysql_close($server);
?>