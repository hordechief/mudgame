import SWIGME

s = SWIGME.SWIGFunction()
print "Result of SWIGME.SWIGFunction: " + s

print "Creating SWIGME.SWIGClass of 10:"
a = SWIGME.SWIGClass( 10 )
a.PrintValue()

print "Creating SWIGME.SWIGClass of 42:"
b = SWIGME.SWIGClass( 42 )
b.PrintValue()
