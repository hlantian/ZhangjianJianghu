#####################################################
#  LEO SuperCool BBS / LeoBBS X / 雷傲极酷超级论坛  #
#####################################################
# 基于山鹰(糊)、花无缺制作的 LB5000 XP 2.30 免费版  #
#   新版程序制作 & 版权所有: 雷傲科技 (C)(R)2004    #
#####################################################
#      主页地址： http://www.LeoBBS.com/            #
#      论坛地址： http://bbs.LeoBBS.com/            #
#####################################################

    my @sortedthreads = reverse(@threads);
    my $threadsize=@sortedthreads;
    $listmy=0 if ($listmy eq "");
    if ($listmy==0){
	$listmy=qq~[<a href=$thisprog?action=$action&forum=$inforum&topic=$intopic&postno=$inpostno&listmy=1>列出所有回复</a>]~;
	$listme=",最多列出 $maxlistpost 个";
	$threadsize=$maxlistpost if ($threadsize>$maxlistpost);
    } else {
	$listmy=qq~[<a href=$thisprog?action=$action&forum=$inforum&topic=$intopic&postno=$inpostno&listmy=0>列出前 $maxlistpost 个回复</a>]~;
	$listme="";
    }
    $output .= qq~<p><table cellpadding=0 cellspacing=0 width=$tablewidth bgcolor=$tablebordercolor align=center>
<tr><td><table cellpadding=6 cellspacing=1 width=100% >
<tr><td bgcolor=$titlecolor colspan=2 $catbackpic><font color=$titlefontcolor><b>帖子一览：$topictitle (新回复在最前$listme)</b>　 $listmy</td>
~;

    $postbackcolor = $miscbackone;
    for (my $i=0;$i<$threadsize;$i++){
        ($membername, $topictitle, $postipaddress ,$showemoticons ,$showsignature ,$postdate ,$post, $posticon) = split(/\t/, $sortedthreads[$i]);
	&getmember($membername,"no");
	$post = "此用户的发言已经被屏蔽！" if ($membercode eq "masked");

        $postdate = $postdate + ($timedifferencevalue + $timezone)*3600;
        $postdate = &dateformat("$postdate");
	$post =~ s/\[hide\](.*)\[\/hide\]/<font color=red>隐藏内容不能预览<\/font>/isg; 
	$post="<font color=red>加密帖子不能预览<\/font>" if (($post=~/LBHIDDEN\[(.*?)\]LBHIDDEN/sg)||($post=~/LBSALE\[(.*?)\]LBSALE/sg));
	$post =~ s/\[curl=\s*(http|https|ftp):\/\/(.*?)\s*\]/\[加密连结\]/isg if ($usecurl ne "no");
	$post =~ s/\[USECHGFONTE\]//sg;
	$post =~ s/\[post=(.+?)\](.+?)\[\/post\]/<blockquote><font face=$font>文章内容 : <hr noshade size=1><font color=red>本内容已被隐藏 , 总发言数须有$1才能查看<\/font><hr noshade size=1><\/font><\/blockquote>/isg; 
        if ($idmbcodestate eq 'on') {
	    &lbcode(\$post);
            if ($post =~/<blockquote><font face=$font>代码/isg){
                $post =~ s/\&amp\;/\&/ig ;
                $post =~ s/\&lt\;br\&gt\;/<br>/ig;
	    }
        } else { $post =~ s/\[DISABLELBCODE\]//isg; }
        if (($emoticons eq 'on') && ($showemoticons eq 'yes')) {
            &doemoticons(\$post);
 	    &smilecode(\$post);
	}

	$output .= qq~<table style="TABLE-LAYOUT:fixed" cellpadding=8 cellspacing=1 width=100%>
<tr><td bgcolor=$miscbackone rowspan=2 valign="top" width=20%><font color=$fontcolormisc><b>$membername</b></font></td>
<td bgcolor=$miscbackone><font color=$fontcolormisc><b>发表于： $postdate</b></td></tr>
<tr><td bgcolor="$miscbackone" style="LEFT:0px;WIDTH:100%;WORD-WRAP:break-word"><font color=$fontcolormisc>$post</td></tr>
<tr><td colspan=2 bgcolor=$miscbacktwo>&nbsp;</td></tr></table>
        ~;
    }
    $output .= qq~</table></td></tr></table>~;
1;
