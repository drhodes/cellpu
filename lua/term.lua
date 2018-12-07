

function mycmd(arg1)
   self = {}
   self.name = "mycmd"
   self.help = "my cmd is an example cmd"

   self.action = function()
      msg = {
         "cmd" = self.name,
         "recv" = "term",
         "func" = "put",
         "args" = ["this is my message"]
      }
      sendQueue.push(msg)
   end
end

function commander()
   local self = {}
   self.commands = {}
   
   self.register_command = function(cmd)
      self.commands[cmd.name] = cmd
   end
   
end

   
      
   
   
                          
