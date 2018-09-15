# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.
import _SWIGME
def _swig_setattr(self,class_type,name,value):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    self.__dict__[name] = value

def _swig_getattr(self,class_type,name):
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


SWIGFunction = _SWIGME.SWIGFunction

class SWIGClass(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SWIGClass, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SWIGClass, name)
    def __init__(self,*args):
        _swig_setattr(self, SWIGClass, 'this', apply(_SWIGME.new_SWIGClass,args))
        _swig_setattr(self, SWIGClass, 'thisown', 1)
    def PrintValue(*args): return apply(_SWIGME.SWIGClass_PrintValue,args)
    def __del__(self, destroy= _SWIGME.delete_SWIGClass):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __repr__(self):
        return "<C SWIGClass instance at %s>" % (self.this,)

class SWIGClassPtr(SWIGClass):
    def __init__(self,this):
        _swig_setattr(self, SWIGClass, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, SWIGClass, 'thisown', 0)
        _swig_setattr(self, SWIGClass,self.__class__,SWIGClass)
_SWIGME.SWIGClass_swigregister(SWIGClassPtr)


