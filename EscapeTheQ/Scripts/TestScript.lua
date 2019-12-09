testString = "Hello, Lua";

update = function(delta)
	printMessage( "update in lua : ", delta )
	number += 1;
	return number;
end
