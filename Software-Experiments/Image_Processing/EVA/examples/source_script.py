import gdb

def print_local_variables(frame):
    block = frame.block()
    for symbol in block:
        if symbol.is_argument or symbol.is_variable:
            print(symbol.name)
 
def breakpoint_handler(event):
    if isinstance(event, gdb.BreakpointEvent):
        frame = gdb.selected_frame()
        print("Local variables at breakpoint:")
        print_local_variables(frame)
 
gdb.events.stop.connect(breakpoint_handler)
