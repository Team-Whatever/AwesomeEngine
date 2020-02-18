testString = "Hello, Lua";
printMessage( testString )

function init()
	printMessage("Initialize from lua")
end

frame = 0
function update()
	frame = frame + 1
	return frame
end