require 'rbhelium'
require 'base64'
require 'msgpack'
 
Thread.abort_on_exception = true
 
token = Base64.decode64("kdTl6U1w+sR61NBiQjm8sw==:")
 
conn = Helium::Connection.new("r01.sjc.helium.io") do |mac, datums|
  puts "Got data #{MessagePack.unpack(datums)} from mac #{mac}"
end
 
status = conn.subscribe(0x000000fffff00001, token)
 
sleep 3600
