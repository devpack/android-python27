# Copyright (c) 2010 Riverbank Computing Limited.
# Copyright (c) 2006 Torsten Marek.


from PyQt4.uic.Compiler.indenter import write_code


def write_import(module_name, from_imports):
    if from_imports:
        write_code("from . import %s" % module_name)
    else:
        write_code("import %s" % module_name)


def moduleMember(module, name):
    if module:
        return "%s.%s" % (module, name)

    return name


class Literal(object):
    """Literal(string) -> new literal

    string will not be quoted when put into an argument list"""
    def __init__(self, string):
        self.string = string

    def __str__(self):
        return self.string

    def __or__(self, r_op):
        return Literal("%s|%s" % (self, r_op))
