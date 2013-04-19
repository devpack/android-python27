Potential Incompatibilities with Earlier Versions
=================================================

This section describes incompatibilities introduced by particular versions of
SIP.  Normally these are the removal of previously deprecated features.


SIP v4.10.1
-----------

Newly Deprecated Features
*************************

The following parts of the :ref:`C API <ref-c-api>` are now deprecated (but
still supported).

- The ``D`` format character of :cfunc:`sipParseResult()`.


SIP v4.8
--------

__truediv__
***********

Prior to this version the :meth:`__div__` special method implicitly defined the
:meth:`__truediv__` special method.  From this version the :meth:`__truediv__`
special method must be explicitly defined.


sipWrapper user Member
**********************

Prior to this version the :ctype:`sipWrapper` structure had a member called
:ctype:`user` which is available for handwritten code to use.  From this
version :ctype:`user` is a member of the :ctype:`sipSimpleWrapper` structure.

:ctype:`sipWrapper` pointers can be safely cast to :ctype:`sipSimpleWrapper`
pointers, so if your code does something like::

    ((sipWrapper *)obj)->user = an_object_reference;

then you just need to change it to::

    ((sipSimpleWrapper *)obj)->user = an_object_reference;


Removal of Previously Deprecated Features
*****************************************

The following parts of the :ref:`C API <ref-c-api>` have been removed.

- The ``a``, ``A``, ``M``, ``N``, ``O``, ``P`` and ``T`` format characters
  from :cfunc:`sipBuildResult()` and :cfunc:`sipCallMethod()`.

- The ``a``, ``A``, ``L`` and ``M`` format characters from
  :cfunc:`sipParseResult()`.

- :cfunc:`sipConvertToCpp()`

- :cfunc:`sipIsSubClassInstance()`

- :cfunc:`sipTransfer()`

- The :func:`transfer` function of the :mod:`sip` module.

- The old-style generated type convertors.

In addition the :option:`-a` command line option to :file:`configure.py` has
been removed.


Removal of PyQt-specific Features
*********************************

The following PyQt-specific support functions have been removed.

- :cfunc:`sipConnectRx()`

- :cfunc:`sipDisconnectRx()`

- :cfunc:`sipEmitSlot()`

- :cfunc:`sipGetSender()`


Newly Deprecated Features
*************************

The following parts of the :ref:`C API <ref-c-api>` are now deprecated (but
still supported).

- The :ref:`ref-type-objects`.

- The :ref:`ref-enum-type-objects`.

- :cfunc:`sipConvertFromInstance()`

- :cfunc:`sipConvertFromMappedType()`

- :cfunc:`sipConvertFromNamedEnum()`

- :cfunc:`sipConvertFromNewInstance()`

- :cfunc:`sipCanConvertToInstance()`

- :cfunc:`sipCanConvertToMappedType()`

- :cfunc:`sipConvertToInstance()`

- :cfunc:`sipConvertToMappedType()`

- :cfunc:`sipForceConvertToInstance()`

- :cfunc:`sipForceConvertToMappedType()`

- :cfunc:`sipClassName()`

- :cfunc:`sipFindClass()`

- :cfunc:`sipFindNamedEnum()`

- :cfunc:`sipFindMappedType()`

- :cfunc:`sipGetWrapper()`

- :cfunc:`sipReleaseInstance()`

- :cfunc:`sipReleaseMappedType()`

- :cfunc:`sipWrapper_Check()`

- The ``B``, ``C`` and ``E`` format characters of :cfunc:`sipBuildResult()` and
  :cfunc:`sipCallMethod()`.

- The ``s``, ``C`` and ``E`` format characters of :cfunc:`sipParseResult()`.


SIP v4.7.8
----------

Automatic int to Enum Conversions
*********************************

This version allows a Python ``int`` object to be passed whenever an enum is
expected.  This can mean that two signatures that were different with prior
versions are now the same as far as Python is concerned.

The :aanno:`Constrained` argument annotation can now be applied to an enum
argument to revert to the earlier behaviour.


SIP v4.7.3
----------

Complementary Comparison Operators
**********************************

Prior to this version SIP did not automatically generate missing complementary
comparison operators.  Typically this was worked around by adding them
explicitly to the .sip files, even though they weren't implemented in C++ and
relied on the C++ compiler calling the complementary operator that was
implemented.

A necessary change to the code generator meant that this not longer worked and
so SIP was changed to automatically generate any missing complementary
operators.  If you have added such operators explicitly then you should remove
them or make them dependent on the particular version of SIP.


SIP v4.4
--------

%ConvertFromTypeCode and %ConvertToTypeCode
*******************************************

Handwritten :directive:`%ConvertFromTypeCode` and
:directive:`%ConvertToTypeCode` now have the responsibility for implementing
the :aanno:`Transfer` and :aanno:`TransferBack` annotations.


SIP_BUILD
*********

The :cmacro:`SIP_BUILD` C preprocessor symbol has been removed.


Newly Deprecated Features
*************************

The following parts of the :ref:`C API <ref-c-api>` are now deprecated (but
still supported).

- The old-style generated type convertors.

- :cfunc:`sipConvertToCpp()`

- :cfunc:`sipIsSubClassInstance()`
