# Copyright (c) 2010 Riverbank Computing Limited.


# A translation table for converting ASCII lower case to upper case.
_ascii_trans_table = bytes.maketrans(b'abcdefghijklmnopqrstuvwxyz',
        b'ABCDEFGHIJKLMNOPQRSTUVWXYZ')


# Convert a string to ASCII upper case irrespective of the current locale.
def ascii_upper(s):
    return s.translate(_ascii_trans_table)
