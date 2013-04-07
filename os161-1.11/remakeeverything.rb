#!/usr/bin/ruby
DEBUG = ARGV
debugflag = "-v"
if  DEBUG && (DEBUG[0].eql? debugflag)
  puts "Making includes"
  code = `cd ../; make includes > /dev/null`
  code = `cd kern/conf; ./config ASST2 > /dev/null`
  puts "Just ran config"
  code = `cd kern/compile/ASST2; make depend && make && make install > /dev/null`
  puts "Just ran make depend, make and make install"
  code = `cd testbin; make && make install > /dev/null`
  puts "Made userlevel code"
  puts "Making main executable"
  code = `make > /dev/null`
  puts "Finished making system"
  puts "All done!"
else
  puts "Making includes"
  code = `cd ../; make includes > /dev/null 2> /dev/null`
  code = `cd kern/conf; ./config ASST2 > /dev/null 2> /dev/null`
  puts "Just ran config"
  code = `cd kern/compile/ASST2; make depend && make && make install > /dev/null 2> /dev/null`
  puts "Just ran make depend, make and make install"
  code = `cd testbin; make && make install > /dev/null 2> /dev/null`
  puts "Made userlevel code"
  puts "Making main executable"
  code = `make > /dev/null 2> /dev/null`
  puts "Finished making system"
  puts "All done!"
end
