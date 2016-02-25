#!/usr/local/bin/perl

# usage: perl scriptname.pl 

$debug=1;

# open file as read_only
$mydir = "$ENV{PWD}";
$filelist = "${mydir}/runlist";
open(LIST,"< $filelist") or die "Can not open ${filelist} !\n";
$counter = 0;
$isMedium = 0;

while (<LIST>) {

$counter++;

$onefile = $_;
chomp($onefile);

$newfile="${mydir}/$onefile";   

printf("file=%s\n", $onefile);
 
# open file as write_only
$execfile="${mydir}/tmp/qa_${onefile}.sh";

open(ROOT,">$execfile") || die "Could not open temp file\n";
print ROOT "#!/bin/bash\n";
print ROOT "cd ${mydir}/prog\n";
print ROOT "root.exe -l -b <<EOF\n";
print ROOT ".x QA.cpp($onefile)\n";
print ROOT ".q\n";
print ROOT "EOF\n";
close ROOT;
chmod(0700,"$execfile");

# submit job to 

if ($isMedium%2 == 0) { system("qsub -q short ${mydir}/tmp/qa_${onefile}.sh");}
else { system("qsub -q medium ${mydir}/tmp/qa_${onefile}.sh");}

# to sleep in seconds		
sleep 1;
if ($counter%10 == 0)
{
	sleep 30;
	$isMedium++;
}

}  # end of while file_list

# to close the file handles
close LIST;




















