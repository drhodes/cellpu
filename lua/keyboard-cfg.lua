print("LUA: loading keyboard-cfg.lua")

local key_bindings = {
   a = "pan-west",
   b = nil,
   c = nil,
   d = "pan-east",
   e = nil,
   f = nil,
   g = nil,
   h = nil,
   i = nil,
   j = nil,
   k = nil,
   l = nil,
   m = nil,
   n = nil,
   o = nil,
   p = nil,
   q = "quit",
   r = nil,
   s = "pan-south",
   t = nil,
   u = nil,
   v = nil,
   w = "pan-north",
   x = nil,
   y = nil,
   z = nil,
}

for key, value in pairs(key_bindings)
do
   --print("binding", key, "to", value)
   bindKey(key, value)
end

