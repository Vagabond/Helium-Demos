var helium = require('nodehelium');
var msgpack = require('msgpack');

// create a helium connection
obj = new helium.Helium();
// open it
obj.open();

var token = "kdTl6U1w+sR61NBiQjm8sw==";
var mac = "000000fffff00001";

//every time obj receives a message, run the following function
obj.on( 'message', function(data){
	//declare message, unpack the message from the data obj into it
	var message = msgpack.unpack(data.message);
	//print the result to the terminal
	console.log(message);
})

//subscribe to your device
obj.subscribe(mac,token);
