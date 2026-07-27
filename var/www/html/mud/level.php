<?

   $server = mysql_pconnect("localhost","root","yinglei$");
    $db = mysql_select_db("lp");
    $sql = "select name,sex,email,ipdres,firstday,backpass from mytest";
       $rst = mysql_query($sql);
       $num_fields = mysql_num_fields($rst);
       $i = 0;
       $j = 0;
       while($i<$num_fields){
          $fields[$i] = mysql_field_name($rst,$i);
          $i++;
       }
       echo '<table border="1" cellspacing="0" cellpadding="0">';
       echo '<tr>';
       reset($fields);
       while(list(,$field_name)=each($fields)){
          echo "<th>$field_name</th>";
       }
       echo '</tr>';
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
       mysql_free_result($rst);
       echo $j;
    mysql_close($server);

?>