# Copyright (c) 2010 Riverbank Computing Limited.
# Copyright (c) 2006 Torsten Marek.


from PyQt4.uic.Compiler.misc import Literal, moduleMember


class ProxyType(type):
    def __init__(*args):
        type.__init__(*args)
        for cls in args[0].__dict__.values():
            if type(cls) is ProxyType:
                cls.module = args[0].__name__

        if not hasattr(args[0], "module"):
            args[0].module = ""
    
    def __getattribute__(cls, name):
        try:
            return type.__getattribute__(cls, name)
        except AttributeError:
            # Handle internal (ie. non-PyQt) attributes as normal.
            if name == "module":
                raise

            # Avoid a circular import.
            from PyQt4.uic.Compiler.qtproxies import LiteralProxyClass

            return type(name, (LiteralProxyClass, ),
                        {"module": moduleMember(type.__getattribute__(cls, "module"),
                                                type.__getattribute__(cls, "__name__"))})            

    def __str__(cls):
        return moduleMember(type.__getattribute__(cls, "module"),
                            type.__getattribute__(cls, "__name__"))

    def __or__(self, r_op):
        return Literal("%s|%s" % (self, r_op))

    def __eq__(self, other):
        return str(self) == str(other)
