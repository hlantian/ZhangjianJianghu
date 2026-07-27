#####################################################
#  LEO SuperCool BBS / LeoBBS X / 雷傲极酷超级论坛  #
#####################################################
# 基于山鹰(糊)、花无缺制作的 LB5000 XP 2.30 免费版  #
#   新版程序制作 & 版权所有: 雷傲科技 (C)(R)2004    #
#####################################################
#      主页地址： http://www.LeoBBS.com/            #
#      论坛地址： http://bbs.LeoBBS.com/            #
#####################################################

    if ($startnewthreads eq "onlysub") {&error("发表&对不起，这里是纯子论坛区，不允许发言！"); }
    if (($floodcontrol eq "on") && ($membercode ne "ad") && ($membercode ne 'smo') && ($membercode ne 'amo') && ($membercode ne 'cmo') && ($membercode ne "amo") && ($membercode ne "mo") && ($inmembmod ne "yes")) {
	($lastpost, $posturl, $posttopic) = split(/\%\%\%/,$lastpostdate);
	$lastpost = $lastpost + $floodcontrollimit;
	if ($lastpost > $currenttime)  {
	    &error("发表回复&灌水预防机制已经使用，您必须等待 $floodcontrollimit 秒钟才能再次发表！");
	}
    }
    if (($inhiddentopic eq "yes") && ($moneyhidden eq "yes")) { &error("发表回复&请不要在一个帖子内同时使用威望和金钱加密！"); }
    if ((($inhiddentopic eq "yes")||($moneyhidden eq "yes")) && ($userregistered eq "no")) { &error("发表回复&未注册用户无权进行威望和金钱加密！"); }

    &error("发表或回复主题&对不起，本论坛不允许发表或回复超过 <B>$maxpoststr</B> 个字符的文章！") if ((length($inpost) > $maxpoststr)&&($maxpoststr ne "")&&($membercode ne "ad")&&($membercode ne 'smo')&&($membercode ne 'cmo') && ($membercode ne "mo") && ($membercode ne "amo") && ($membercode !~ /^rz/) && ($inmembmod ne "yes"));
    if ($postopen eq "no") { &error("发表或回复主题&对不起，本论坛不允许发表或回复主题！"); }

    if ($deletepercent > 0 && $numberofposts + $numberofreplys > 0 && $membercode ne "ad" && $membercode ne "smo" && $membercode ne "cmo" && $membercode ne "mo" && $membercode ne "amo" && $inmembmod ne "yes") {
	&error("发表回复&对不起，你的删贴率超过了<b>$deletepercent</b>%，管理员不允许你发表回复！") if ($postdel / ($numberofposts + $numberofreplys) >= $deletepercent / 100);
    }

    if ((($onlinetime + $onlinetimeadd) < $onlinepost)&&($onlinepost ne "")&&($membercode ne "ad")&&($membercode ne "smo")&&($membercode ne "cmo")&&($membercode ne "mo")&&($membercode ne "amo")&&($membercode !~ /^rz/))     { $onlinetime = $onlinetime + $onlinetimeadd;  &error("回复主题&对不起，本论坛不允许在线时间少于 $onlinepost 秒的用户回复主题！你目前已经在线 $onlinetime 秒！"); }

    if (($userregistered eq "no")&&(length($inmembername) > 12)) { &error("发表新回复&您输入的用户名太长，请控制在6个汉字内！");   }
    if (($userregistered eq "no")&&($inmembername =~ /^客人/)) { &error("发表新回复&请不要在用户名的开头中使用客人字样！");   }
    if ($inmembername eq "客人") { &error("发表新回复&请不要在用户名的开头中使用客人字样！");   }
    if (($userregistered eq "no")&&($startnewthreads ne "all")) { &error("发表新回复&您没有注册！");   }
    elsif ((($inpassword ne $password)&&($userregistered ne "no"))||(($inpassword ne "")&&($userregistered eq "no"))) { &error("发表新回复&您的密码错误！"); }
    elsif (($membercode eq "banned")||($membercode eq "masked"))  { &error("发表&已被禁止发言或者发言被屏蔽，请联系坛主解决！"); }
    elsif ($inpost eq "")            { &error("发表新回复&必须输入内容！"); }
    else {
#	@allforums = @forums;

	if ($startnewthreads eq "no") {
            unless ($membercode eq "ad" || $membercode eq 'smo' || $inmembmod eq "yes") {&error("发表新回复&在此论坛中只能由坛主或者本版版主发表新回复！");}
        }
        elsif ($startnewthreads eq "cert"){
	    unless ($membercode eq "ad" ||$membercode eq 'smo'|| $inmembmod eq "yes"||$membercode eq 'cmo'||$membercode eq 'amo'||$membercode eq 'mo'||$membercode =~ /^rz/) { &error("发表新回复&在此论坛中只能由坛主、版主和认证会员发表新回复！"); }
	}
	$tempaccess = "forumsallowed". "$inforum";
	$testentry = $query->cookie("$tempaccess");

	if ((($testentry eq $forumpass)&&($testentry ne ""))||($allowedentry{$inforum} eq "yes")||($membercode eq "ad")||($membercode eq 'smo')||($inmembmod eq "yes")) { $allowed = "yes"; }
        if (($privateforum eq "yes") && ($allowed ne "yes")) { &error("发表&对不起，您不允许在此论坛发表！"); }
 	if (($startnewthreads eq "all")&&($userregistered eq "no")) { $inmembername = "$inmembername(客)"; }

        $inpost =~ s/\[这个(.+?)最后由(.+?)编辑\]//isg;

        $filetoopen = "$lbdir" . "forum$inforum/$intopic.thd.cgi";
        if (-e $filetoopen) {
           &winlock($filetoopen) if ($OS_USED eq "Nt");
	    undef $/;
           open(FILE, "$filetoopen");
           flock(FILE, 1) if ($OS_USED eq "Unix");
           $allmessages = <FILE>;
           close(FILE);
	    $/="\n";
           &winunlock($filetoopen) if ($OS_USED eq "Nt");
           @allmessages=split(/\n/,$allmessages);
        }
	else { unlink ("$lbdir" . "forum$inforum/$intopic.pl"); &error("回复&这个主题不存在！可能已经被删除！"); }

        my $file = "$lbdir" . "forum$inforum/$intopic.pl";
        &winlock($file) if ($OS_USED eq "Nt");
        open (ENT, $file);
        flock(ENT, 2) if ($OS_USED eq "Unix");
        $in = <ENT>;
        close (ENT);
	&winunlock($file) if ($OS_USED eq "Nt");
        ($topicid, $topictitle, $topicdescription, $threadstate, $threadposts ,$threadviews, $startedby, $startedpostdate, $lastposter, $lastpostdate, $posticon) = split(/\t/,$in);
        if (($threadstate eq "closed")||($threadstate eq "pollclosed")) { &error("发表回复&对不起，这个主题已经被锁定！"); }
        $numberofitems = $threadposts+ 1; 
	if ($rdays ne '') { &error("发表回复&超过 $rdays 天的帖子不允许再回复！") if ($currenttime - $lastpostdate > $rdays * 86400); }

        $inpost = &dofilter("$inpost");

        if ($emote) {
 	    my @pairs1 = split(/\&/,$emote);
	    foreach (@pairs1) {
		my ($toemote, $beemote) = split(/=/,$_);
		chomp $beemote;
		$beemote =~ s/对象/〖$inmembername〗/isg;
		$inpost =~ s/$toemote/$beemote/isg;
	    }
	}

	if (($addme)&&(($allowattachment ne "no")||($membercode eq "ad")||($membercode eq 'smo')||($inmembmod eq "yes"))) {
	    my $filesize=0;
	    $uploadreqire = 0 if ($uploadreqire < 0);
	    if (($membercode ne "ad")&&($membercode ne 'smo')&&($membercode ne 'amo')&&($membercode ne 'cmo')&&($membercode ne 'mo')&&($membercode !~ /^rz/)&&($inmembmod ne "yes")&&(($numberofposts+$numberofreplys) < $uploadreqire)) {
		&error("上传出错&你必须发帖总数达到 <B>$uploadreqire</B> 才能在本区上传！");
	    }
	    my $up_filename =$query->uploadInfo($addme);
	    ($up_name,$up_ext) = split(/.*\./,$up_filename);
	    $up_ext = lc($up_ext);
	    my $checkadd=0;
            for (split(/\,\s*/,$addtype)){
		$checkadd=1,last if ($up_ext eq lc($_));
            }
            if ($up_ext eq "exe"||$up_ext eq "com"||$up_ext eq "pl"||$up_ext eq "cgi"||$up_ext eq "asp"||$up_ext eq "pm"||$up_ext eq "php4"||$up_ext eq "php"||$up_ext eq "php3"||$up_ext eq "phtml"||$up_ext eq "jsp"||$up_ext eq "cfml"||$up_ext eq "dll") {
		&error("上传出错&为了安全，不支持你所上传的附件，请重新选择！");
	    }
	    if ($checkadd==0) { &error("上传出错&不支持你所上传的附件或者图片，请重新选择！"); }

	    my $bufferall;
            $replynumber=$#allmessages+1;
            
	    open (FILE,">${imagesdir}$usrdir/$inforum/$inforum\_$intopic\_$replynumber.$up_ext");
	    binmode (FILE);
	    while ((($buffer=$query->readUploadFile($addme,4096)))&&!(($filesize>$maxupload)&&($membercode ne "ad"))){
		print FILE $buffer;
		$bufferall .= $buffer;
		$filesize=$filesize+4;
	    }
	    close (FILE);
	    if ($up_ext eq "gif"||$up_ext eq "jpg"||$up_ext eq "bmp"||$up_ext eq "jpeg"||$up_ext eq "png"||$up_ext eq "ppm"||$up_ext eq "svg"||$up_ext eq "xbm"||$up_ext eq "xpm") {	
		eval("use Image::Info qw(image_info);"); 
		if ($@ eq "") { 
		    my $info = image_info("${imagesdir}$usrdir/$inforum/$inforum\_$intopic\_$replynumber.$up_ext");
		    if ($info->{error} eq "Unrecognized file format"){
		        unlink ("${imagesdir}$usrdir/$inforum/$inforum\_$intopic\_$replynumber.$up_ext");
		        &error("上传出错&上传文件不是图片文件，请上传标准的图片文件！");
		    }
	            undef $info;
		}
            }
	    if (($filesize>$maxupload)&&($membercode ne "ad")) {
                unlink ("${imagesdir}$usrdir/$inforum/$inforum\_$intopic\_$replynumber.$up_ext");
		&error("上传出错&上传文件大小超过$maxupload，请重新选择！ ");
	    }
	    if ($dispshowcount eq "yes"){
                open(FILE, ">>${lbdir}FileCount/$inforum/$inforum\_$intopic.cgi");
                print FILE "$inforum\_$intopic\_$replynumber\=$inforum\_$intopic\_$replynumber.$up_ext\=0\n";
                close(FILE);
	    }
	    open (FILE, ">>${lbdir}FileCount/$inforum/$inforum\_$intopic.pl");
	    print FILE "$inforum\_$intopic\_$replynumber.$up_ext\n";
	    close(FILE);
	}

        ($trash, $topictitle, $trash, $trash, $trash, $trash, $post, $trash,my $water) = split(/\t/,$allmessages[0]);

	if (($nowater eq "on")&&($water eq "no")&&($membercode ne "ad")&&($membercode ne 'smo')&&($membercode ne 'amo')&&($membercode ne 'cmo')&&($membercode ne 'mo')&&($inmembmod ne "yes")) {
	    my $inposttemp = $inpost;
	    $inposttemp =~ s/\[这个(.+?)最后由(.+?)编辑\]\<BR\>\<BR\>//isg;
	    $inposttemp =~ s/\[这个(.+?)最后由(.+?)编辑\]\<BR\>//isg;
	    $inposttemp =~ s/\[这个(.+?)最后由(.+?)编辑\]//isg;
	    $inposttemp =~ s/\[quote\]\[b\]下面引用由\[u\].+?\[\/u\]在 \[i\].+?\[\/i\] 发表的内容：\[\/b\].+?\[\/quote\]\<br\>//isg;
	    $inposttemp =~ s/\[quote\]\[b\]下面引用由\[u\].+?\[\/u\]在 \[i\].+?\[\/i\] 发表的内容：\[\/b\].+?\[\/quote\]//isg;
	    if ((length($inposttemp) < $gsnum)&&($gsnum > 0)) {
	        &error("发表回复&请不要灌水，本主题禁止 $gsnum 字节以下的灌水！");
                unlink ("${imagesdir}$usrdir/$inforum/$inforum\_$intopic\_$replynumber.$up_ext") if ($addme);
	    }
	}

        if ($moneyhidden eq "yes") { $inposttemp = "(保密)"; $inpost="LBSALE[$moneypost]LBSALE".$inpost;}

	if ($inhiddentopic eq "yes") { $inposttemp = "(保密)"; $inpost="LBHIDDEN[$postweiwang]LBHIDDEN".$inpost; }

	if ($inposttemp ne "(保密)") {
	    $inposttemp = $inpost;
	    $inposttemp = &temppost($inposttemp);
            chomp $inposttemp;
            $inposttemp = &lbhz($inposttemp,22);
	}
	$lastreplymessgae = $allmessages[-1];
        (my $ainmembername,my $no,my $no,my $no,my $no,my $no,my $ainpost,my $no) = split(/\t/,$lastreplymessgae);
 	if (($inmembername eq $ainmembername)&&($inpost eq $ainpost)) {
            unlink ("${imagesdir}$usrdir/$inforum/$inforum\_$intopic\_$replynumber.$up_ext");
    	    &error("发表回复&请不要重复回复，已经存在与此回复内容相同的而且是你发的回复了！");
            unlink ("${imagesdir}$usrdir/$inforum/$inforum\_$intopic\_$replynumber.$up_ext") if ($addme);
	}

        &winlock($filetoopen) if ($OS_USED eq "Nt");
        if (open(FILE, ">>$filetoopen")) {
            flock(FILE, 2) if ($OS_USED eq "Unix");
            print FILE "$inmembername\t$topictitle\t$postipaddress\t$inshowemoticons\t$inshowsignature\t$currenttime\t$inpost\t$inposticon\t\n";
            close(FILE);
        }
        &winunlock($filetoopen) if ($OS_USED eq "Nt");

        $threadposts = @allmessages;
        $threadviews = $threadposts if ($threadviews < $threadposts);
#	$threadviews = 9999 if ($threadviews > 10000);

        my $topictitletemp = $topictitle;
        $topictitletemp =~ s/^＊＃！＆＊//;
        &winlock($file) if ($OS_USED eq "Nt");
        if (open(FILE, ">$file")) {
            flock(FILE, 2) if ($OS_USED eq "Unix");
            print FILE "$intopic\t＊＃！＆＊$topictitletemp\t$topicdescription\t$threadstate\t$threadposts\t$threadviews\t$startedby\t$startedpostdate\t$inmembername\t$currenttime\t$posticon\t$inposttemp\t";
        close(FILE);
        }
        &winunlock($file) if ($OS_USED eq "Nt");
        
	$file = "$lbdir" . "boarddata/listno$inforum.cgi";
        &winlock($file) if ($OS_USED eq "Nt");
        undef $/;
        open (LIST, "$file");
        flock (LIST, 2) if ($OS_USED eq "Unix");
        $listall=<LIST>;
        close (LIST);
        $/="\n";
        $listall =~ s/(.*)(^|\n)$intopic\n(.*)/$1$2$3/;
        
	if (length($listall) > 500) {
	    if (open (LIST, ">$file")) {
        	flock (LIST, 2) if ($OS_USED eq "Unix");
        	print LIST "$intopic\n$listall";
        	close (LIST);
            }
            &winunlock($file) if ($OS_USED eq "Nt");
    	} else {
            &winunlock($file) if ($OS_USED eq "Nt");
	    require "rebuildlist.pl";
            my $truenumber = rebuildLIST(-Forum=>"$inforum");
            ($tpost,$treply) = split (/\|/,$truenumber);
	}

        $cleanmembername = $inmembername;
        $cleanmembername =~ s/ /\_/isg;
	$cleanmembername =~ tr/A-Z/a-z/;

      $maxpersontopic = 25;
      if ($maxpersontopic && $userregistered ne "no") {
              $cleanstart = $startedby;
              $cleanstart =~ s/ /\_/isg;
              $cleanstart =~ tr/A-Z/a-z/;
              &addmytopic("reply", $cleanmembername, $inforum, $intopic, $topictitletemp, $currenttime, $posticon);
              &addmytopic("post", $cleanstart, $inforum, $intopic, $topictitletemp, $currenttime, $posticon) if ($cleanmembername ne $cleanstart);
      }

        $numberofreplys++ if ($forumreplyallowcount ne "no");
        $lastpostdate = "$currenttime\%\%\%topic.cgi?forum=$inforum&topic=$intopic\%\%\%$topictitletemp" if ($privateforum ne "yes");
        chomp $lastpostdate;

    if (($userregistered ne "no")&&($password ne "")) {
	my $namenumber = &getnamenumber($cleanmembername);
	&checkmemfile($cleanmembername,$namenumber);
        $filetomake = "$lbdir" . "$memdir/$namenumber/$cleanmembername.cgi";
        &winlock($filetomake) if ($OS_USED eq "Nt");
        if ((open(FILE, ">$filetomake"))&&($inmembername ne "")) {
        flock(FILE, 2) if ($OS_USED eq "Unix");
        print FILE "$inmembername\t$password\t$membertitle\t$membercode\t$numberofposts|$numberofreplys\t$emailaddress\t$showemail\t$ipaddress\t$homepage\t$oicqnumber\t$icqnumber\t$location\t$interests\t$joineddate\t$lastpostdate\t$signature\t$timedifference\t$privateforums\t$useravatar\t$userflag\t$userxz\t$usersx\t$personalavatar\t$personalwidth\t$personalheight\t$rating\t$lastgone\t$visitno\t$addjy\t$meili\t$mymoney\t$postdel\t$sex\t$education\t$marry\t$work\t$born\t$chatlevel\t$chattime\t$jhmp\t$jhcount\t$ebankdata\t$onlinetime\t$userquestion\t$awards\t$useradd7\t$userface\t$soccerdata\t$useradd5\t";
        close(FILE);
        }
        &winunlock($filetomake) if ($OS_USED eq "Nt");
        unlink ("${lbdir}cache/myinfo/$cleanmembername.pl");
        if (((-M "${lbdir}cache/meminfo/$cleanmembername.pl") *86400 > 60*2)||(!(-e "${lbdir}cache/meminfo/$cleanmembername.pl"))) {
            require "getnameinfo.pl" if ($onloadinfopl ne 1);
            &getmemberinfo($cleanmembername);
        }
    }
    
    my $nowtime = &shortdate($currenttime + $timezone*3600);

    my $filetoopens = "$lbdir/data/todaypost.cgi";
    $filetoopens = &lockfilename($filetoopens);

    if (($usetodaypostreply ne "no")&&(!(-e "$filetoopens.lck"))) {
    	&winlock("$lbdir/data/todaypost.cgi") if ($OS_USED eq "Nt" || $OS_USED eq "Unix");
        if (-e "$lbdir/data/todaypost.cgi") {
            open (FILE,"+<$lbdir/data/todaypost.cgi");
            $todaypost=<FILE>;
            chomp $todaypost;
            my ($nowtoday,$todaypostno,$maxday,$maxdaypost,$yestdaypost)=split(/\t/,$todaypost);
            if ($nowtoday eq $nowtime) {
            	$todaypostno ++;
            	if ($todaypostno > $maxdaypost) {
            	    $maxday     = $nowtime;
            	    $maxdaypost = $todaypostno;
            	}
            }
            else {
            	unlink("${lbdir}cache/forumcache.pl");
            	$nowtoday = $nowtime;
            	$yestdaypost = $todaypostno;
            	$todaypostno = 1;
            }
            seek(FILE,0,0);
            print FILE "$nowtoday\t$todaypostno\t$maxday\t$maxdaypost\t$yestdaypost\t";
            close (FILE);
        }
        else {
            open (FILE,">$lbdir/data/todaypost.cgi");
            print FILE "$nowtime\t1\t$nowtime\t1\t0\t";
            close (FILE);
        }
    	&winunlock("$lbdir/data/todaypost.cgi") if ($OS_USED eq "Nt" || $OS_USED eq "Unix");
    }

	$filetoopen = "${lbdir}boarddata/foruminfo$inforum.cgi";
	my $filetoopens = &lockfilename($filetoopen);
	if (!(-e "$filetoopens.lck")) {
            &winlock($filetoopen) if ($OS_USED eq "Nt" || $OS_USED eq "Unix");
            open(FILE, "+<$filetoopen");
            ($no, $threads, $posts, $todayforumpost, $lastposter) = split(/\t/,<FILE>);
            $lastposter   = $inmembername;
            $lastposttime = $currenttime;
            if (($tpost ne "")&&($treply ne "")) {
                $threads = $tpost;
                $posts   = $treply;
            } else { $posts++; }
            if ($usetodayforumreply eq "yes") {
		($todayforumpost, $todayforumposttime) = split(/\|/,$todayforumpost);
		if (($nowtime ne $todayforumposttime)||($todayforumpost eq "")) { $todayforumpost = 1; } else { $todayforumpost++; }
                $todayforumpost = "$todayforumpost|$nowtime";
            }
            $lastposttime = "$lastposttime\%\%\%$intopic\%\%\%$topictitletemp";
	    
	    seek(FILE,0,0);
            print FILE "$lastposttime\t$threads\t$posts\t$todayforumpost\t$lastposter\t\n";
            close(FILE);

	    $posts = 0 if ($posts eq "");$threads = 0 if ($threads eq "");
	    open(FILE, ">${lbdir}boarddata/forumposts$inforum.pl");
	    print FILE "\$threads = $threads;\n\$posts = $posts;\n\$todayforumpost = \"$todayforumpost\";\n1;\n";
            close(FILE);

            &winunlock($filetoopen) if ($OS_USED eq "Nt" || $OS_USED eq "Unix");
	}
        else {
    	    unlink ("$filetoopens.lck") if ((-M "$filetoopens.lck") *86400 > 30);
	}

    require "$lbdir" . "data/boardstats.cgi";

    $filetomake = "$lbdir" . "data/boardstats.cgi";
    my $filetoopens = &lockfilename($filetomake);
    if (!(-e "$filetoopens.lck")) {
        $totalposts++;
        &winlock($filetomake) if ($OS_USED eq "Nt");
        if (open(FILE, ">$filetomake")) {
            flock(FILE, 2) if ($OS_USED eq "Unix");
            print FILE "\$lastregisteredmember = \'$lastregisteredmember\'\;\n";
            print FILE "\$totalmembers = \'$totalmembers\'\;\n";
            print FILE "\$totalthreads = \'$totalthreads\'\;\n";
            print FILE "\$totalposts = \'$totalposts\'\;\n";
            print FILE "\n1\;";
            close (FILE);
        }
        &winunlock($filetomake) if ($OS_USED eq "Nt");
    }
    else {
    	unlink ("$filetoopens.lck") if ((-M "$filetoopens.lck") *86400 > 30);
    }

    if ($emailfunctions eq "on") {
	eval("use MAILPROG qw(sendmail);");
	$filetoopen = "$lbdir" . "forum$inforum/$intopic.mal.pl";
	open (FILE, "$filetoopen");
	my @maildata = <FILE>;
	close (FILE);

	$mailall = "$inmembername\t$emailaddress\t";
	if ($innotify eq "yes") {
	    if (open (FILE, ">$filetoopen")) {
                print FILE "$mailall\n";
                foreach (@maildata) {
                    chomp $_;
                    print FILE "$_\n" if ($mailall ne $line);
                }
                close (FILE);
	    }
	}
	$toemail = '';
	foreach (@maildata) {
	    chomp $_;
	    ($postersname,$posteremailaddress) = split(/\t/,$_);
            if ($lastemailsent ne $postersname) {
                if ($inmembername eq $postersname) { next; }
                next if ($posteremailaddress eq "");
        	$posteremailaddress =~ s/[\a\f\n\e\0\r\t\`\~\!\$\%\^\&\*\(\)\=\+\\\{\}\;\'\:\"\,\/\<\>\?\|]//isg;
        	next if ($posteremailaddress !~ /^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/);
            	if ($toemail eq "") {$toemail = $posteremailaddress;} else {$toemail .= ", $posteremailaddress";}
                $lastemailsent = $postersname;
	    }
	}

	$output .= "\n\n<!-- 处理 Email 发送 --> \n\n";
	chomp $toemail;
	$toemail =~ s/\\//g;
	$fromemail = $adminemail_out;
	chomp $fromemail;
	$fromemail =~ s/\\//g;
	$topictitle =~ s/&quot\;/\"/g;
        $topictitle =~ s/^＊＃！＆＊//;

	$to = $toemail;
	$from = $fromemail;
	$subject = "[$forumname] 回复通知";
        $message .= "$boardname <br>\n";
	$message .= "$boardurl/leobbs.cgi <br>\n";
        $message .= "---------------------------------------------------------------------\n<br><br>\n";
        $message .= "你好, 你的帖子有了一个新回复！\n <br><br>\n";
        $message .= "回复人： $inmembername <br>\n";
        $message .= "分类： $category <br>\n";
        $message .= "论坛： $forumname <br>\n";
        $message .= "主题： $topictitle <br>\n";
        $message .= "点击下面的链接去查看详细内容：\n <br><br>\n";
        $message .= "$boardurl/topic.cgi?forum=$inforum&topic=$intopic\n <br><br>\n";
        $message .= "---------------------------------------------------------------------<br>\n";

        &sendmail($from, $emailaddress, $to, $subject, $message);
    }

    $numberofitems++;
    $postend = int($numberofitems / $maxtopics)*$maxtopics; 
    $pagestoshow = "";
    $numberofpages = $numberofitems / $maxtopics;
    if ($numberofitems > $maxtopics) {
        if ($maxtopics < $numberofitems) {
            ($integer,$decimal) = split(/\./,$numberofpages);
            if ($decimal > 0) { $numberofpages = $integer + 1; }
            $pagestart = 0;
            $counter = 0;
            while ($numberofpages > $counter) {
                $counter++;
                $threadpages .= qq~ <a href="topic.cgi?forum=$inforum&topic=$intopic&start=$pagestart">$counter</a> ~;
                $pagestart = $pagestart + $maxtopics;
            }
        }
	$pagestoshow = qq~<font color=$forumfontcolor> &nbsp;[ 第$threadpages页 ]~;
    }

    &mischeader("回复成功");

opendir (CATDIR, "${lbdir}cache");
@dirdata = readdir(CATDIR);
closedir (CATDIR);
@dirdata = grep(/^plcache$inforum\_/,@dirdata);
foreach (@dirdata) { unlink ("${lbdir}cache/$_"); }

    if ($refreshurl == 1) { $relocurl = "topic.cgi?forum=$inforum&topic=$intopic&start=$postend#bottom"; }
                     else { $relocurl = "forums.cgi?forum=$inforum"; }
    $output .= qq~<table cellpadding=0 cellspacing=0 width=$tablewidth bgcolor=$tablebordercolor align=center>
<tr><td><table cellpadding=6 cellspacing=1 width=100%>
<tr><td bgcolor=$titlecolor $catbackpic align=center><font color=$fontcolormisc><b>谢谢！您的回复已经成功发表！</b></font></td></tr>
<tr><td bgcolor=$miscbackone><font color=$fontcolormisc>如果浏览器没有自动返回，请点击下面的链接！：
<ul><li><a href="topic.cgi?forum=$inforum&topic=$intopic">返回主题</a>  $pagestoshow
<li><a href="forums.cgi?forum=$inforum">返回论坛</a><li><a href="leobbs.cgi">返回论坛首页</a>
<li><a href="postings.cgi?action=lock&forum=$inforum&topic=$intopic&checked=yes">锁定帖子</a>
</ul></tr></td></table></td></tr></table>
<meta http-equiv="refresh" content="3; url=$relocurl">
	~;
    }
1;
