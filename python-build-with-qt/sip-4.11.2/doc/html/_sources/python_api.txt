.. _ref-python-api:

Python API for Applications
===========================

.. module:: sip

The main purpose of the :mod:`sip` module is to provide functionality common to
all SIP generated bindings.  It is loaded automatically and most of the time
you will completely ignore it.  However, it does expose some functionality that
can be used by applications.


.. function:: cast(obj, type) -> object

    This does the Python equivalent of casting a C++ instance to one of its
    sub or super-class types.

    :param obj:
        the Python object.
    :param type:
        the type.
    :return:
        a new Python object is that wraps the same C++ instance as *obj*, but
        has the type *type*.


.. function:: delete(obj)

    For C++ instances this calls the C++ destructor.  For C structures it
    returns the structure's memory to the heap.

    :param obj:
        the Python object.


.. function:: dump(obj)

    This displays various bits of useful information about the internal state
    of the Python object that wraps a C++ instance or C structure.

    :param obj:
        the Python object.


.. function:: getapi(name) -> version

    .. versionadded:: 4.9

    This returns the version number that has been set for an API.  The version
    number is either set explicitly by a call to :func:`sip.setapi` or
    implicitly by importing the module that defines it.

    :param name:
        the name of the API.
    :return:
        The version number that has been set for the API.  An exception will
        be raised if the API is unknown.


.. function:: isdeleted(obj) -> bool

    This checks if the C++ instance or C structure has been deleted and
    returned to the heap.

    :param obj:
        the Python object.
    :return:
        ``True`` if the C/C++ instance has been deleted.


.. function:: ispyowned(obj) -> bool

    This checks if the C++ instance or C structure is owned by Python.

    :param obj:
        the Python object.
    :return:
        ``True`` if the C/C++ instance is owned by Python.


.. function:: setapi(name, version)

    .. versionadded:: 4.9

    This sets the version number of an API.  An exception is raised if a
    different version number has already been set, either explicitly by a
    previous call, or implicitly by importing the module that defines it.

    :param name:
        the name of the API.
    :param version:
        The version number to set for the API.  Version numbers must be
        greater than or equal to 1.


.. function:: setdeleted(obj)

    This marks the C++ instance or C structure as having been deleted and
    returned to the heap so that future references to it raise an exception
    rather than cause a program crash.  Normally SIP handles such things
    automatically, but there may be circumstances where this isn't possible.

    :param obj:
        the Python object.


.. function:: settracemask(mask)

    If the bindings have been created with SIP's :option:`-r <sip -r>` command
    line option then the generated code will include debugging statements that
    trace the execution of the code.  (It is particularly useful when trying to
    understand the operation of a C++ library's virtual function calls.)

    :param mask:
        the mask that determines which debugging statements are enabled.

    Debugging statements are generated at the following points:

    - in a C++ virtual function (*mask* is ``0x0001``)
    - in a C++ constructor (*mask* is ``0x0002``)
    - in a C++ destructor (*mask* is ``0x0004``)
    - in a Python type's __init__ method (*mask* is ``0x0008``)
    - in a Python type's __del__ method (*mask* is ``0x0010``)
    - in a Python type's ordinary method (*mask* is ``0x0020``).

    By default the trace mask is zero and all debugging statements are
    disabled.


.. data:: SIP_VERSION

    This is a Python integer object that represents the SIP version number as
    a 3 part hexadecimal number (e.g. v4.0.0 is represented as ``0x040000``).
    It was first implemented in SIP v4.2.


.. data:: SIP_VERSION_STR

    This is a Python string object that defines the SIP version number as
    represented as a string.  For development snapshots it will start with
    ``snapshot-``.  It was first implemented in SIP v4.3.


.. function:: transferback(obj)

    This function is a wrapper around :cfunc:`sipTransferBack()`.


.. function:: transferto(obj, owner)

    This function is a wrapper around :cfunc:`sipTransferTo()`.


.. function:: unwrapinstance(obj) -> integer

    This returns the address, as an integer, of a wrapped C/C++ structure or
    class instance.

    :param obj:
        the Python object.
    :return:
        an integer that is the address of the C/C++ instance.


.. class:: voidptr

    This is the type object for the type SIP uses to represent a C/C++
    ``void *``.  It may have a size associated with the address in which case
    the Python buffer protocol is supported.  This means that the memory can
    be treated as a mutable array of bytes when wrapped with the ``buffer()``
    builtin.  The type has the following methods.

    .. method:: __init__(address[, size=-1[, writeable=True]])

        :param address:
            the address, either another :class:`sip.voidptr`, ``None``, a
            Python Capsule, a Python CObject, or an integer.
        :param size:
            the optional associated size of the block of memory and is negative
            if the size is not known.
        :param writeable:
            set if the memory is writeable.  If it is not specified, and
            *address* is a :class:`sip.voidptr` instance then its value will be
            used.

    .. method:: __int__() -> integer

        This returns the address as an integer.

        :return:
            the integer address.

    .. method:: __hex__() -> string

        This returns the address as a hexadecimal string.

        :return:
            the hexadecimal string address.

    .. method:: ascapsule() -> capsule

        .. versionadded:: 4.10

        This returns the address as an unnamed Python Capsule.  This requires
        Python v3.1 or later or Python v2.7 or later.

        :return:
            the Capsule.

    .. method:: ascobject() -> cObject

        This returns the address as a Python CObject.  This is deprecated with
        Python v3.1 and is not supported with Python v3.2 and later.

        :return:
            the CObject.

    .. method:: asstring([size=-1]) -> string/bytes

        This returns a copy of the block of memory as a Python v2 string object
        or a Python v3 bytes object.
        
        :param size:
            the number of bytes to copy.  If it is negative then the size
            associated with the address is used.  If there is no associated
            size then an exception is raised.
        :return:
            the string or bytes object.

    .. method:: getsize() -> integer

        This returns the size associated with the address.
        
        :return:
            the associated size which will be negative if there is none.

    .. method:: setsize(size)

        This sets the size associated with the address.
        
        :param size:
            the size to associate.  If it is negative then no size is
            associated.

    .. method:: getwriteable() -> bool

        This returns the writeable state of the memory.

        :return:
            ``True`` if the memory is writeable.

    .. method:: setwriteable(writeable)

        This sets the writeable state of the memory.

        :param writeable:
            the writeable state to set.


.. function:: wrapinstance(addr, type) -> object

    This wraps a C structure or C++ class instance in a Python object.  If the
    instance has already been wrapped then a new reference to the existing
    object is returned.
    
    :param addr:
        the address of the instance as a number.
    :param type:
        the Python type of the instance.
    :return:
        the Python object that wraps the instance.


.. class:: wrapper

    This is the type object of the base type of all instances wrapped by SIP.


.. class:: wrappertype

    This is the type object of the metatype of the :class:`sip.wrapper` type.
