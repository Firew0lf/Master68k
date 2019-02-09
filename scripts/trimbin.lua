local args = {...}

local file = io.open(args[1])
if not file then
	print((args[0] or "trimbin")..": No input file")
	os.exit(1)
end

local buff = file:read("*a")
file:close()

local lastData = 0
for i=1, #buff do
	if buff:sub(i,i) ~= "\0" then
		lastData = i
	end
end

file = io.open(args[1], "w")
file:write(buff:sub(1,lastData))
file:close()
