# Copyright (c) 2010 Riverbank Computing Limited.


import re


def as_string(obj, encode=True):
    if isinstance(obj, basestring):
        s = '"' + _escape(obj.encode('UTF-8')) + '"'

        if encode:
            s = '_fromUtf8(' + s + ')'

        return s

    return str(obj)


_esc_regex = re.compile(r"(\"|\'|\\)")

def _escape(text):
    # This escapes any escaped single or double quote or backslash.
    x = _esc_regex.sub(r"\\\1", text)

    # This replaces any '\n' with an escaped version and a real line break.
    return re.sub(r'\n', r'\\n"\n"', x)
