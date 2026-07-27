#!/usr/bin/perl
#####################################################
#  LEO SuperCool BBS / LeoBBS X / 雷傲极酷超级论坛  #
#####################################################
# 基于山鹰(糊)、花无缺制作的 LB5000 XP 2.30 免费版  #
#   新版程序制作 & 版权所有: 雷傲科技 (C)(R)2004    #
#####################################################
#      主页地址： http://www.LeoBBS.com/            #
#      论坛地址： http://bbs.LeoBBS.com/            #
#####################################################

BEGIN {
    $startingtime=(times)[0]+(times)[1];
    foreach ($0,$ENV{'PATH_TRANSLATED'},$ENV{'SCRIPT_FILENAME'}){
    	my $LBPATH = $_;
    	next if ($LBPATH eq '');
    	$LBPATH =~ s/\\/\//g; $LBPATH =~ s/\/[^\/]+$//o;
        unshift(@INC,$LBPATH);
    }
}

use LBCGI;
require "data/boardinfo.cgi";
require "bbs.lib.pl";

      @n0 = ("c3","99","99","99","99","99","99","99","99","c3");
      @n1 = ("cf","c7","cf","cf","cf","cf","cf","cf","cf","c7");
      @n2 = ("c3","99","9f","9f","cf","e7","f3","f9","f9","81");
      @n3 = ("c3","99","9f","9f","c7","9f","9f","9f","99","c3");
      @n4 = ("cf","cf","c7","c7","cb","cb","cd","81","cf","87");
      @n5 = ("81","f9","f9","f9","c1","9f","9f","9f","99","c3");
      @n6 = ("c7","f3","f9","f9","c1","99","99","99","99","c3");
      @n7 = ("81","99","9f","9f","cf","cf","e7","e7","f3","f3");
      @n8 = ("c3","99","99","99","c3","99","99","99","99","c3");
      @n9 = ("c3","99","99","99","99","83","9f","9f","cf","e3");

for($i=0;$i<10;$i++) {
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(3));
  $b=substr("def",$num,1);
  $a1="$b$a";
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(4));
  $b=substr("bdef",$num,1);
  $a2="$a$b";
  $n = "n$i";
  $num=int(myrand(2));
  if ($num eq 1) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(2));
  if ($num eq 0) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(3));
  $b=substr("def",$num,1);
  $a1="$b$a";
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(4));
  $b=substr("bdef",$num,1);
  $a2="$a$b";
  $n = "n$i";
  $num=int(myrand(2));
  if ($num eq 1) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(2));
  if ($num eq 0) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(4));
  $b=substr("9def",$num,1);
  $a1="$a$b";
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(5));
  $b=substr("9adef",$num,1);
  $a2="$b$a";
  $n = "n$i";
  $num=int(myrand(2));
  if ($num eq 1) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(2));
  if ($num eq 0) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(3));
  $b=substr("def",$num,1);
  $a1="$b$a";
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(4));
  $b=substr("bdef",$num,1);
  $a2="$a$b";
  $n = "n$i";
  $num=int(myrand(2));
  if ($num eq 1) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(2));
  if ($num eq 0) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(4));
  $b=substr("9def",$num,1);
  $a1="$a$b";
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(5));
  $b=substr("9adef",$num,1);
  $a2="$b$a";
  $n = "n$i";
  $num=int(myrand(2));
  if ($num eq 1) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(2));
  if ($num eq 0) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(4));
  $b=substr("9def",$num,1);
  $a1="$a$b";
  $num=int(myrand(6));
  $a=substr("abcdef",$num,1);
  $num=int(myrand(5));
  $b=substr("9adef",$num,1);
  $a2="$b$a";
  $n = "n$i";
  $num=int(myrand(2));
  if ($num eq 1) { push(@$n,$a1); } else { unshift(@$n,$a1); }
  $num=int(myrand(2));
  if ($num eq 0) { push(@$n,$a1); } else { unshift(@$n,$a1); }
}

if ($ENV{'HTTP_REFERER'} !~ /$ENV{'HTTP_HOST'}/i && $ENV{'HTTP_REFERER'} ne '' && $ENV{'HTTP_HOST'} ne '' && $canotherlink ne "yes") { print "Content-type: text/html\n\n"; print "<font color=red>出错，请不要用外部连接本程序！</font>"; exit;}

###获取真实的 IP 地址
$ipaddress = $ENV{'REMOTE_ADDR'};
$trueipaddress = $ENV{'HTTP_X_FORWARDED_FOR'};
$ipaddress = $trueipaddress if ($trueipaddress ne "" && $trueipaddress ne "unknown" && $trueipaddress !~ m/^192\.168\./ && $trueipaddress !~ m/^10\./);
$trueipaddress = $ENV{'HTTP_CLIENT_IP'};
$ipaddress = $trueipaddress if ($trueipaddress ne "" && $trueipaddress ne "unknown" && $trueipaddress !~ m/^192\.168\./ && $trueipaddress !~ m/^10\./);

###生成随机验证码
$verifynum = int(myrand(10000));
$verifynum = sprintf("%04d", $verifynum);
###获取当前时间
$currenttime = time;

###将当前进程验证码保存
mkdir ("${lbdir}verifynum", 0777) if (!(-e "${lbdir}verifynum"));
mkdir ("${lbdir}verifynum/login", 0777) if (!(-e "${lbdir}verifynum/login"));
chmod (0777,"${lbdir}verifynum");
chmod (0777,"${lbdir}verifynum/login");

$filetomake = $lbdir . "verifynum/" . $ipaddress . ".cgi";
$filetomake =~ s/[<>\^\(\)\{\}\a\f\n\e\0\r\"\`\&\;\|\*\?]//g;
open(FILE, ">$filetomake");
print FILE "$verifynum\t$currenttime";
close(FILE);

   $counter = $verifynum;
   $len=length($counter);
   
   @bitmap=();
   for($i=0;$i<20;$i++) {
      for($j=0;$j<$len;$j++) {
         $n=substr($counter,$j,1);
         $bytes=&takebitmap($n,$i);
         my $a = int(myrand(15));
         if ($a eq 1)  { $bytes =~ s/9/8/g; } elsif ($a eq 3)  { $bytes =~ s/c/e/g; } elsif ($a eq 6)  { $bytes =~ s/3/b/g; } elsif ($a eq 8)  { $bytes =~ s/8/9/g; } elsif ($a eq 0)  { $bytes =~ s/e/f/g; }
         push(@bitmap,$bytes);
      }
   }
   for ($i=0;$i<$len*2;$i++) {
   	  $num=int(myrand(6));
   	  $a=substr("abcdef",$num,1);
   	  $num=int(myrand(3));
   	  $b=substr("def",$num,1);
          $a="$b$a";
          unshift(@bitmap,$a);    
          push(@bitmap,$a);       
   }
   print "Content-type: image/x-xbitmap\n\n";
   printf ("#define count_width %d\n#define count_height 24\n",$len*8);
   printf STDOUT "static char count_bits[] = {\n";
   for($i = 0; $i < ($#bitmap+1); $i++) {
      print("0x$bitmap[$i]");
      if ($i != $#bitmap) {
         print(",");
         if (($i+1) % 7 == 0) {
            print("\n");
         }
      }
   }
   print("};\n");

    opendir (DIRS, "${lbdir}verifynum");
    my @files = readdir(DIRS);
    closedir (DIRS);
    my $ci = 1;
    foreach (@files) {
    	unlink ("${lbdir}verifynum/$_") if ((-M "${lbdir}verifynum/$_") *86400 > 60*30 ); #30分钟
    	$ci ++;
    	last if ($ci > 100);
    }
    opendir (DIRS, "${lbdir}verifynum/login");
    my @files = readdir(DIRS);
    closedir (DIRS);
    my $ci = 1;
    foreach (@files) {
    	unlink ("${lbdir}verifynum/login/$_") if ((-M "${lbdir}verifynum/login/$_") *86400 > 60*30);
    	$ci ++;
    	last if ($ci > 100);
    }

exit 0;

sub takebitmap {
if ($_[0]==0) {return $n0[$_[1]];}   
elsif ($_[0]==1) {return $n1[$_[1]];}   
elsif ($_[0]==2) {return $n2[$_[1]];} 
elsif ($_[0]==3) {return $n3[$_[1]];} 
elsif ($_[0]==4) {return $n4[$_[1]];} 
elsif ($_[0]==5) {return $n5[$_[1]];} 
elsif ($_[0]==6) {return $n6[$_[1]];} 
elsif ($_[0]==7) {return $n7[$_[1]];} 
elsif ($_[0]==8) {return $n8[$_[1]];} 
elsif ($_[0]==9) {return $n9[$_[1]];} 
}
