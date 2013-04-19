# Copyright (c) 2010 Riverbank Computing Limited.
# Copyright (c) 2006 Torsten Marek.


indentwidth = 4

_indenter = None

class _IndentedCodeWriter(object):
    def __init__(self, output):
        self.level = 0
        self.output = output

    def indent(self):
        self.level += 1

    def dedent(self):
        self.level -= 1

    def write(self, line):
        if line.strip():
            if indentwidth > 0:
                indent = " " * indentwidth
                line = line.replace("\t", indent)
            else:
                indent = "\t"

            self.output.write("%s%s\n" % (indent * self.level, line))
        else:
            self.output.write("\n")


def createCodeIndenter(output):
    global _indenter
    _indenter = _IndentedCodeWriter(output)

def getIndenter():
    return _indenter

def write_code(string):
    _indenter.write(string)
