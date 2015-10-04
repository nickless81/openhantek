#!/usr/bin/perl 
use strict;
use Getopt::Std;
use Data::Dumper;
sub fwDownload
{
  my @lsusb = 	`lsusb`;
  my $usbDevice;
  my $my_firmware = "/opt/git-repos/openhantek/fw/hantek6022be-firmware.hex";
  my $my_loader = "/opt/git-repos/openhantek/fw/hantek6022be-loader.hex";
  for my $line (@lsusb)
  {
    chomp($line);
    if( $line =~ /04b4/)
    {
      if($line =~ /602a/)
      {
        my($Bus,$BusID,$Device,$DeviceID) = (split(/ /, $line));
        $usbDevice = "/dev/bus/usb/$BusID/$DeviceID";
        $usbDevice =~ s/[<>?;:!,.='"]//g;
        print "$line\n";
        print "$usbDevice\n";
        my $loadFW = `sudo /sbin/fxload -t fx2 -I $my_firmware -s $my_loader -D $usbDevice`
      }
    }
	}
}
sub checkDownload
{
  my @lsusb = `lsusb`;
	for my $line (@lsusb)
  {
    chomp($line);
    if( $line =~ /04b5/)
    {
      if($line =~ /6022/)
      {
        print "Firmware Downloaded\n";
        print "$line\n";
        return 0;
      }
    }
  }
  return -1;
}
sub run
{
  if(checkDownload()<0)
  {
    fwDownload();
    print "Waiting for firmware booted\n";
    sleep 2;
    checkDownload();
  }
}
run();
