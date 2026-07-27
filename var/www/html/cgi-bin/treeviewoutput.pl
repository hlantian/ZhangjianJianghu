#####################################################
#  LEO SuperCool BBS / LeoBBS X / 雷傲极酷超级论坛  #
#####################################################
# 基于山鹰(糊)、花无缺制作的 LB5000 XP 2.30 免费版  #
#   新版程序制作 & 版权所有: 雷傲科技 (C)(R)2004    #
#####################################################
#      主页地址： http://www.LeoBBS.com/            #
#      论坛地址： http://bbs.LeoBBS.com/            #
#####################################################

    @treelist=();
    $pages = qq~<font color=$menufontcolor><b>本主题共有一页</b>~;
    if (($screenmode >=8)||($tablewidth > 770)) { $topictitlemax = 96; } else { $topictitlemax = 50; }
    $output .= qq~<p><table cellpadding=4 cellspacing=1 width=$tablewidth align=center><tr><td colspan=3 bgcolor=$titlecolor><font color=$titlefontcolor><B>&nbsp;* 树形目录</B></td></tr>~;
    $i = 0;
    foreach (@threads) {
	($membername, $topictitle, $postipaddresstemp, $showemoticons, $showsignature, $postdate, $post, $posticon) = split(/\t/,$_);
	$topictitle =~ s/^＊＃！＆＊//;
	chomp $posticon;
	$postdate = &shortdate($postdate + $addtimes);

        if (($post =~ /LBHIDDEN\[(.*?)\]LBHIDDEN/)||($post =~ /LBSALE\[(.*?)\]LBSALE/)) {
            $post = "保密";
        } else {
	    $post =~ s/\[quote\](.*)\[quote\](.*)\[\/quote](.*)\[\/quote\]//isg;
	    $post =~ s/\[quote\](.*)\[\/quote\]//isg;
	    $post =~ s/\[hidepoll\]//isg;
	    $post =~ s/\[这个(.+?)最后由(.+?)编辑\]\n//isg;
	    $post =~ s/\[hide\](.*)\[hide\](.*)\[\/hide](.*)\[\/hide\]//isg; 
	    $post =~ s/\[hide\](.*)\[\/hide\]//isg; 
	    $post =~ s/\[post=(.+?)\](.+?)\[\/post\](.*)\[post=(.+?)\](.+?)\[\/post\]//isg; 
	    $post =~ s/\[post=(.+?)\](.+?)\[\/post\]//isg;
	    $post =~ s/\[curl=(http|https|ftp):\/\/(.*?)\]/\[加密连结\]/isg;
	    $post = &temppost("$post");
	}

	if (length($post)>=$topictitlemax) {
            $post=&lbhz($post,$topictitlemax);
	}

	if ($post eq "") { $post="(无内容)"; }

	if (($posticon ne "")&&($posticon !~ /\<br\>/i)) { $posticon = qq~<img src=$imagesurl/posticons/$posticon $defaultsmilewidth $defaultsmileheight>~; } else { $posticon = ""; }

	my $memberfilename = $membername;
	$memberfilename =~ y/ /_/;
	$memberfilename =~ tr/A-Z/a-z/;
	if ($membername=~/\(客\)/) {
	    $membername=~s/\(客\)//isg;
	    $h4 = qq~<font color=$postfontcolorone title=此为未注册用户>$membername</font>~;
	}
	else {
	    $h4 = qq~<a href=profile.cgi?action=show&member=~ . uri_escape($memberfilename) . qq~ title=\"查看$membername的个人资料\">$membername</a>~;
	}
	
	$editpostnumber=$i+1; 
	$h5="　　"; 
   	$h5 =qq(<input type="checkbox" name="postno$editpostnumber" value="yes">) if(($mymembercode eq "ad")||($mymembercode eq 'smo')||($mymembercode eq 'cmo')||($myinmembmod eq "yes"));
	if ($i==0) { $h3 = "　主贴："; } else { $h3 = "$h5回复："; } 

	if ($treebackcolor ne $postcolorone) { $treebackcolor=$postcolorone; } else { $treebackcolor=$postcolortwo; }
	if ($i==$replynum) {
	    $treefontcolor="$fonthighlight";
            $h1=$h2="";
	}
	else {
	    $treefontcolor=$postfontcolorone;
	    $h1="<a href=$thisprog?forum=${inforum}&topic=${intopic}&replynum=$i&show=$show>";
	    $h2="</a>";
	}
	$output .=qq~<tr bgcolor="$treebackcolor"><td><font color=$treefontcolor> $h3 $posticon $h1 $post $h2</td><td width=130> &nbsp 作者：$h4</td><td width=70 align=right> $postdate&nbsp;</font></td></tr>~;
	$i ++;
    }
    $output .= qq~</table><img src=$imagesurl/images/none.gif height=3 width=0><BR>~;
1;