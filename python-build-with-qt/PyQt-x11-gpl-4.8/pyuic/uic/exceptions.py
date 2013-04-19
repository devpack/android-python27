# Copyright (c) 2010 Riverbank Computing Limited.
# Copyright (c) 2006 Torsten Marek.


class NoSuchWidgetError(Exception):
    def __str__(self):
        return "Unknown Qt widget: %s" % (self.args[0],)

class UnsupportedPropertyError(Exception):
    pass

class WidgetPluginError(Exception):
    pass
