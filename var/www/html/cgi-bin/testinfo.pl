#####################################################
#  LEO SuperCool BBS / LeoBBS X / 雷傲极酷超级论坛  #
#####################################################
# 基于山鹰(糊)、花无缺制作的 LB5000 XP 2.30 免费版  #
#   新版程序制作 & 版权所有: 雷傲科技 (C)(R)2004    #
#####################################################
#      主页地址： http://www.LeoBBS.com/            #
#      论坛地址： http://bbs.LeoBBS.com/            #
#####################################################

sub ipwhere {
	my ($beginseek,$addrBegin,$idxBegin,$ipBegin,$ipcnt,$idxSeek,$addrcnt);
	
	my $ip=shift;
	my @ip=split(/\./,$ip);

	my $file = "${lbdir}data/$ip[0].txt";
	if(open(IPF,$file)){
		my $ips=$ip[0]*1000000000+$ip[1]*1000000+$ip[2]*1000+$ip[3];
		my @ipdata=<IPF>;
		close(IPF);
		for ($i=0;$i<@ipdata;$i++){
			($ip1,$ip2,$from1,$from2)=split(/__/,$ipdata[$i]);
			(my $ipa1,my $ipa2,my $ipa3,my $ipa4)=split(/\./,$ip1);
			(my $ipb1,my $ipb2,my $ipb3,my $ipb4)=split(/\./,$ip2);
			my $ipbegin =$ipa1*1000000000+$ipa2*1000000+$ipa3*1000+$ipa4;
			my $ipend =$ipb1*1000000000+$ipb2*1000000+$ipb3*1000+$ipb4;
			if (($ips<=$ipend)&&($ips>=$ipbegin)) {
				$fromwhere="$from1$from2";
				last;
			}
		}
		$fromwhere =~ s/[\a\f\n\e\0\r\t\)\(\*\+\?]//isg;
		return $fromwhere if($fromwhere) ;
	}

	$ipnum=$ip[0]*16777216+$ip[1]*65536+$ip[2]*256+$ip[3];

	$file="${lbdir}data/ip.dat";

	open(FILE,"$file")||return;
	binmode(FILE);

	read(FILE,$beginseek,4);
	seek(FILE,unpack("L",$beginseek),0);
	read(FILE,$addrBegin,4);
	read(FILE,$idxBegin,4);
	read(FILE,$ipBegin,4);
	read(FILE,$ipcnt,4);
	
	$addrBegin=unpack("L",$addrBegin);
	$idxBegin=unpack("L",$idxBegin);
	$ipBegin=unpack("L",$ipBegin);
	my $BeginNum=0;
	my $EndNum=unpack("L",$ipcnt);

	my $Middle=int(($BeginNum+$EndNum)/2);
	while ($Middle!=$BeginNum) {
		my ($ip0);
		seek(FILE,$ipBegin+7*$Middle,0);
		read(FILE,$ip0,4);
		my $ip0num=unpack("L",$ip0);
		if ($ip0num<$ipnum) {
			$BeginNum=$Middle;
		}
		else {
			$EndNum=$Middle;
		}
		$Middle=int(($BeginNum+$EndNum)/2);
	}
	seek(FILE,$ipBegin+7*$EndNum+4,0);
	read(FILE,$idxSeek,3);
	seek(FILE,$idxBegin+unpack("L",$idxSeek."\0"),0);
	read(FILE,$addrcnt,1);
	my @addridx;
	for (1..unpack("C",$addrcnt)) {
		my $temp;
		read(FILE,$temp,3);
		push @addridx,unpack("L",$temp."\0");
	}
	my $addr;
	$/="\0";
	while (@addridx) {
		seek(FILE,$addrBegin+(shift @addridx),0);
		my $addr1=<FILE>;
		chomp $addr1;
		$addr .= "$addr1 ";
	}
	$/="\n";
	$addr="未知地址" if($addr eq "");
	return $addr;
}
sub osinfo {
   local $os="",$Agent;
   $Agent = $ENV{'HTTP_USER_AGENT'};
   if (($Agent =~ /win/i)&&($Agent =~ /95/i)) {
      $os="Windows 95";
   }
   elsif (($Agent =~ /win 9x/i)&&($Agent =~ /4.90/i)) {
      $os="Windows ME";
   }
   elsif (($Agent =~ /win/i)&&($Agent =~ /98/i)) {
      $os="Windows 98";
   }
   elsif (($Agent =~ /win/i)&&($Agent =~ /nt 5\.0/i)) {
      $os="Windows 2000";
   }
   elsif (($Agent =~ /win/i)&&($Agent =~ /nt 5\.1/i)) {
      $os="Windows XP";
   }
   elsif (($Agent =~ /win/i)&&($Agent =~ /nt 5\.2/i)) {
      $os="Windows 2003";
   }
   elsif (($Agent =~ /win/i)&&($Agent =~ /nt/i)) {
      $os="Windows NT";
   }
   elsif (($Agent =~ /win/i)&&($Agent =~ /32/i)) {
      $os="Windows 32";
   }
   elsif ($Agent =~ /linux/i) {
      $os="Linux";
   }
   elsif ($Agent =~ /unix/i) {
      $os="Unix";
   }
   elsif (($Agent =~ /sun/i)&&($Agent =~ /os/i)) {
      $os="SunOS";
   }
   elsif (($Agent =~ /ibm/isg)&&($Agent =~ /os/isg)) {
      $os="IBM OS/2";
   }
   elsif (($Agent =~ /Mac/i)&&($Agent =~ /PC/i)) {
      $os="Macintosh";
   }
   elsif ($Agent =~ /FreeBSD/i) {
      $os="FreeBSD";
   }
   elsif ($Agent =~ /PowerPC/i) {
      $os="PowerPC";
   }
   elsif ($Agent =~ /AIX/i) {
      $os="AIX";
   }
   elsif ($Agent =~ /HPUX/i) {
      $os="HPUX";
   }
   elsif ($Agent =~ /NetBSD/i) {
      $os="NetBSD";
   }
   elsif ($Agent =~ /BSD/i) {
      $os="BSD";
   }
   elsif ($Agent =~ /OSF1/i) {
      $os="OSF1";
   }
   elsif ($Agent =~ /IRIX/i) {
      $os="IRIX";
   }
   elsif ($Agent =~ /google/i) {
      $os = "GoogleBot";
   }
   elsif ($Agent =~ /Yahoo/i) {
      $os = "YahooBot";
   }
  $os = "Unknown"  if ($os eq '');
  $os =~ s/[\a\f\n\e\0\r\t\)\(\*\+\?]//isg;
  $os = substr($os, 0, 15) if (length($os) > 15);
  return $os;
}
sub browseinfo {
       my $browser = "";
       my $browserver = "";
       my ($Agent, $Part, $browseinfo);
       $Agent = $ENV{"HTTP_USER_AGENT"};

       if ($Agent =~ /Lynx/i)
       {
               $browser = "Lynx";
       }
       elsif ($Agent =~ /MOSAIC/i)
       {
               $browser = "MOSAIC";
       }
       elsif ($Agent =~ /AOL/i)
       {
               $browser = "AOL";
       }
       elsif ($Agent =~ /Lynx/i)
       {
               $browser = "Lynx";
       }
       elsif ($Agent =~ /Opera/i)
       {
               $browser = "Opera";
       }
       elsif ($Agent =~ /JAVA/i)
       {
               $browser = "JAVA";
       }
       elsif ($Agent =~ /MacWeb/i)
       {
               $browser = "MacWeb";
       }
       elsif ($Agent =~ /WebExplorer/i)
       {
               $browser = "WebExplorer";
       }
       elsif ($Agent =~ /OmniWeb/i)
       {
               $browser = "OmniWeb";
       }
       elsif ($Agent =~ /Mozilla/i)
       {
               if ($Agent =~ "MSIE")
               {
                       if ($Agent =~ /MyIE(\d*)/)
                       {
                               $browserver = $1;
                               $browser = "MyIE";
                       }
                       else
                       {
                               $Part = (split(/\(/, $Agent))[1];
                               $Part = (split(/\;/,$Part))[1];
                               $browserver = (split(/ /,$Part))[2];
                               $browserver =~ s/([\d\.]+)/$1/isg;
                               $browser = "Internet Explorer";
                       }
               }
               elsif ($Agent =~ "Opera")
               {
                       $Part = (split(/\(/, $Agent))[1];
                       $browserver = (split(/\)/, $Part))[1];
                       $browserver = (split(/ /,$browserver))[2];
                       $browserver =~ s/([\d\.]+)/$1/isg;
                       $browser = "Opera";
               }
               else
               {
                       $Part = (split(/\(/, $Agent))[0];
                       $browserver = (split(/\//, $Part))[1];
                       $browserver = (split(/ /,$browserver))[0];
                       $browserver =~ s/([\d\.]+)/$1/isg;
                       $browser = "Netscape Navigator";
               }
       }
       elsif ($Agent =~ /google/i)
       {
               $browser = "GoogleBot";
       }
       elsif ($Agent =~ /Yahoo/i)
       {
               $browser = "YahooBot";
       }

       if ($browser ne '')
       {
               $browserver =~ s/[^0-9\.b]//isg;
               $browserver = &lbhz($browserver, 4) if (length($browserver) > 10);
               $browseinfo = "$browser $browserver";
       }
       else
       {
               $browseinfo = "Unknown";
       }
       $browseinfo =~ s/[\a\f\n\e\0\r\t\)\(\*\+\?]//isg;
  $browseinfo =~ s/[\a\f\n\e\0\r\t\)\(\*\+\?]//isg;
  $browseinfo = substr($browseinfo, 0, 28) if (length($browseinfo) > 28);
       return $browseinfo;
}
1;
