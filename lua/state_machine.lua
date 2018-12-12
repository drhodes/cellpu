



function StateMachine(name)
   self = {}
   self.name = name   
   self.currentState = nil
   self.transitions = {}
   
   -------------------------------------------------------------------------------------------------
   self.add = function(source, trigger, target, action)
      if not self.transitions[source] then
         self.transitions[source] = {}
      end
      
      if self.transitions[source][trigger] then         
         local badTransition = "[" .. source .. " >" .. trigger .. "> " .. target "]"
         local msg = "StateMachine.add trying to replace a transition: " .. badTransition
         return {err = true, msg = msg}
      else
         self.transitions[source][trigger] = target
         return {err = false, msg=""}
      end
   end


   self.graphviz = function()      
      print ("digraph " .. self.name .. " {")
      for src, srcTable in pairs(self.transitions) do
         if srcTable then
            for trans, target in pairs(srcTable) do
               print (src .. " -> " .. target .. ' [label="' .. trans .. '"];')
            end
         end
      end
      print ("}")

   end
   
   return self
end


function main()
   local sm = StateMachine("Door")

   
   sm.add("opened", "push", "closed")
   sm.add("opened", "pull", "opened")
   sm.add("closed", "pull", "opened")
   sm.add("closed", "push", "closed")
   
   sm.graphviz()
      
end

function CellMachine()
   local sm = StateMachine("Cell")

   sm.add("sleep", "MouseOver", "", )


main()
