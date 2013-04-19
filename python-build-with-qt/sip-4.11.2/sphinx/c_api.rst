.. _ref-c-api:

C API for Handwritten Code
==========================

In this section we describe the API that can be used by handwritten code in
specification files.


.. cmacro:: SIP_API_MAJOR_NR

    This is a C preprocessor symbol that defines the major number of the SIP
    API.  Its value is a number.  There is no direct relationship between this
    and the SIP version number.


.. cmacro:: SIP_API_MINOR_NR

    This is a C preprocessor symbol that defines the minor number of the SIP
    API.  Its value is a number.  There is no direct relationship between this
    and the SIP version number.


.. cmacro:: SIP_BLOCK_THREADS

    This is a C preprocessor macro that will make sure the Python Global
    Interpreter Lock (GIL) is acquired.  Python API calls must only be made
    when the GIL has been acquired.  There must be a corresponding
    :cmacro:`SIP_UNBLOCK_THREADS` at the same lexical scope.


.. cmacro:: SIP_NO_CONVERTORS

    This is a flag used by various type convertors that suppresses the use of a
    type's :directive:`%ConvertToTypeCode`.


.. cmacro:: SIP_NOT_NONE

    This is a flag used by various type convertors that causes the conversion
    to fail if the Python object being converted is ``Py_None``.


.. cmacro:: SIP_PROTECTED_IS_PUBLIC

    .. versionadded:: 4.10

    This is a C preprocessor symbol that is defined automatically by the build
    system to specify that the generated code is being compiled with
    ``protected`` redefined as ``public``.  This allows handwritten code to
    determine if the generated helper functions for accessing protected C++
    functions are available (see :directive:`%MethodCode`).


.. cmacro:: SIP_SSIZE_T

    This is a C preprocessor macro that is defined as ``Py_ssize_t`` for Python
    v2.5 and later, and as ``int`` for earlier versions of Python.  It makes it
    easier to write PEP 353 compliant handwritten code.


.. cmacro:: SIP_UNBLOCK_THREADS

    This is a C preprocessor macro that will restore the Python Global
    Interpreter Lock (GIL) to the state it was prior to the corresponding
    :cmacro:`SIP_BLOCK_THREADS`.


.. cmacro:: SIP_USE_PYCAPSULE

    .. versionadded:: 4.11

    This is a C preprocessor symbol that is defined when ``PyCapsule`` objects
    are being used rather than the (now deprecated) ``PyCObject`` objects.


.. cmacro:: SIP_VERSION

    This is a C preprocessor symbol that defines the SIP version number
    represented as a 3 part hexadecimal number (e.g. v4.0.0 is represented as
    ``0x040000``).


.. cmacro:: SIP_VERSION_STR

    This is a C preprocessor symbol that defines the SIP version number
    represented as a string.  For development snapshots it will start with
    ``snapshot-``.


.. cfunction:: sipErrorState sipBadCallableArg(int arg_nr, PyObject *arg)

    .. versionadded:: 4.10

    This is called from :directive:`%MethodCode` to raise a Python exception
    when an argument to a function, a C++ constructor or method is found to
    have an unexpected type.  This should be used when the
    :directive:`%MethodCode` does additional type checking of the supplied
    arguments.

    :param arg_nr:
        the number of the argument.  Arguments are numbered from 0 but are
        numbered from 1 in the detail of the exception.
    :param arg:
        the argument.
    :return:
        the value that should be assigned to ``sipError``.


.. cfunction:: void sipBadCatcherResult(PyObject *method)

    This raises a Python exception when the result of a Python reimplementation
    of a C++ method doesn't have the expected type.  It is normally called by
    handwritten code specified with the :directive:`%VirtualCatcherCode`
    directive.

    :param method:
        the Python method and would normally be the supplied ``sipMethod``.


.. cfunction:: void sipBadLengthForSlice(SIP_SSIZE_T seqlen, SIP_SSIZE_T slicelen)

    This raises a Python exception when the length of a slice object is
    inappropriate for a sequence-like object.  It is normally called by
    handwritten code specified for :meth:`__setitem__` methods.

    :param seqlen:
        the length of the sequence.
    :param slicelen:
        the length of the slice.


.. cfunction:: PyObject *sipBuildResult(int *iserr, const char *format, ...)

    This creates a Python object based on a format string and associated
    values in a similar way to the Python :cfunc:`Py_BuildValue()` function.

    :param iserr:
        if this is not ``NULL`` then the location it points to is set to a
        non-zero value.
    :param format:
        the string of format characters.
    :return:
        If there was an error then ``NULL`` is returned and a Python exception
        is raised.
        
    If the format string begins and ends with parentheses then a tuple of
    objects is created.  If it contains more than one format character then
    parentheses must be specified.

    In the following description the first letter is the format character, the
    entry in parentheses is the Python object type that the format character
    will create, and the entry in brackets are the types of the C/C++ values
    to be passed. 

    ``a`` (string) [char]
        Convert a C/C++ ``char`` to a Python v2 or v3 string object.

    ``b`` (boolean) [int]
        Convert a C/C++ ``int`` to a Python boolean.

    ``c`` (string/bytes) [char]
        Convert a C/C++ ``char`` to a Python v2 string object or a Python v3
        bytes object.

    ``d`` (float) [double]
        Convert a C/C++ ``double`` to a Python floating point number.

    ``e`` (integer) [enum]
        Convert an anonymous C/C++ ``enum`` to a Python integer.

    ``f`` (float) [float]
        Convert a C/C++ ``float`` to a Python floating point number.

    ``g`` (string/bytes) [char \*, :cmacro:`SIP_SSIZE_T`]
        Convert a C/C++ character array and its length to a Python v2 string
        object or a Python v3 bytes object.  If the array is ``NULL`` then the
        length is ignored and the result is ``Py_None``.

    ``h`` (integer) [short]
        Convert a C/C++ ``short`` to a Python integer.

    ``i`` (integer) [int]
        Convert a C/C++ ``int`` to a Python integer.

    ``l`` (long) [long]
        Convert a C/C++ ``long`` to a Python integer.

    ``m`` (long) [unsigned long]
        Convert a C/C++ ``unsigned long`` to a Python long.

    ``n`` (long) [long long]
        Convert a C/C++ ``long long`` to a Python long.

    ``o`` (long) [unsigned long long]
        Convert a C/C++ ``unsigned long long`` to a Python long.

    ``r`` (wrapped instance) [*type* \*, :cmacro:`SIP_SSIZE_T`, const :ctype:`sipTypeDef` \*]
        Convert an array of C structures, C++ classes or mapped type instances
        to a Python tuple.  Note that copies of the array elements are made.

    ``s`` (string/bytes) [char \*]
        Convert a C/C++ ``'\0'`` terminated string to a Python v2 string object
        or a Python v3 bytes object.  If the string pointer is ``NULL`` then
        the result is ``Py_None``.

    ``t`` (long) [unsigned short]
        Convert a C/C++ ``unsigned short`` to a Python long.

    ``u`` (long) [unsigned int]
        Convert a C/C++ ``unsigned int`` to a Python long.

    ``w`` (unicode/string) [wchar_t]
        Convert a C/C++ wide character to a Python v2 unicode object or a
        Python v3 string object.

    ``x`` (unicode/string) [wchar_t \*]
        Convert a C/C++ ``L'\0'`` terminated wide character string to a Python
        v2 unicode object or a Python v3 string object.  If the string pointer
        is ``NULL`` then the result is ``Py_None``.

    ``A`` (string) [char \*]
        Convert a C/C++ ``'\0'`` terminated string to a Python v2 or v3 string
        object.  If the string pointer is ``NULL`` then the result is
        ``Py_None``.

    ``B`` (wrapped instance) [*type* \*, :ctype:`sipWrapperType` \*, PyObject \*]
        Convert a new C structure or a new C++ class instance to a Python class
        instance object.  Ownership of the structure or instance is determined
        by the ``PyObject *`` argument.  If it is ``NULL`` and the instance has
        already been wrapped then the ownership is unchanged.  If it is
        ``NULL`` or ``Py_None`` then ownership will be with Python.  Otherwise
        ownership will be with C/C++ and the instance associated with the
        ``PyObject *`` argument.  The Python class is influenced by any
        applicable :directive:`%ConvertToSubClassCode` code.

        .. note::
            This is deprecated from SIP v4.8.  Instead you should use ``N``.

    ``C`` (wrapped instance) [*type* \*, :ctype:`sipWrapperType` \*, PyObject \*]
        Convert a C structure or a C++ class instance to a Python class
        instance object.  If the structure or class instance has already been
        wrapped then the result is a new reference to the existing class
        instance object.  Ownership of the structure or instance is determined
        by the ``PyObject *`` argument.  If it is ``NULL`` and the instance has
        already been wrapped then the ownership is unchanged.  If it is
        ``NULL`` and the instance is newly wrapped then ownership will be with
        C/C++.  If it is ``Py_None`` then ownership is transferred to Python
        via a call to :cfunc:`sipTransferBack()`.  Otherwise ownership is
        transferred to C/C++ and the instance associated with the
        ``PyObject *`` argument via a call to :cfunc:`sipTransferTo()`.  The
        Python class is influenced by any applicable
        :directive:`%ConvertToSubClassCode` code.

        .. note::
            This is deprecated from SIP v4.8.  Instead you should use ``D``.

    ``D`` (wrapped instance) [*type* \*, const :ctype:`sipTypeDef` \*, PyObject \*]
        Convert a C structure, C++ class or mapped type instance to a Python
        object.  If the instance has already been wrapped then the result is a
        new reference to the existing object.  Ownership of the instance is
        determined by the ``PyObject *`` argument.  If it is ``NULL`` and the
        instance has already been wrapped then the ownership is unchanged.  If
        it is ``NULL`` and the instance is newly wrapped then ownership will be
        with C/C++.  If it is ``Py_None`` then ownership is transferred to
        Python via a call to :cfunc:`sipTransferBack()`.  Otherwise ownership
        is transferred to C/C++ and the instance associated with the
        ``PyObject *`` argument via a call to :cfunc:`sipTransferTo()`.  The
        Python class is influenced by any applicable
        :directive:`%ConvertToSubClassCode` code.

    ``E`` (wrapped enum) [enum, PyTypeObject \*]
        Convert a named C/C++ ``enum`` to an instance of the corresponding
        Python named enum type.

        .. note::
            This is deprecated from SIP v4.8.  Instead you should use ``F``.

    ``F`` (wrapped enum) [enum, :ctype:`sipTypeDef` \*]
        Convert a named C/C++ ``enum`` to an instance of the corresponding
        Python named enum type.

    ``G`` (unicode) [wchar_t \*, :cmacro:`SIP_SSIZE_T`]
        Convert a C/C++ wide character array and its length to a Python unicode
        object.  If the array is ``NULL`` then the length is ignored and the
        result is ``Py_None``.

    ``N`` (wrapped instance) [*type* \*, :ctype:`sipTypeDef` \*, PyObject \*]
        Convert a new C structure, C++ class or mapped type instance to a
        Python object.  Ownership of the instance is determined by the
        ``PyObject *`` argument.  If it is ``NULL`` and the instance has
        already been wrapped then the ownership is unchanged.  If it is
        ``NULL`` or ``Py_None`` then ownership will be with Python.  Otherwise
        ownership will be with C/C++ and the instance associated with the
        ``PyObject *`` argument.  The Python class is influenced by any
        applicable :directive:`%ConvertToSubClassCode` code.

    ``R`` (object) [PyObject \*]
        The result is value passed without any conversions.  The reference
        count is unaffected, i.e. a reference is taken.

    ``S`` (object) [PyObject \*]
        The result is value passed without any conversions.  The reference
        count is incremented.

    ``V`` (sip.voidptr) [void \*]
        Convert a C/C++ ``void *`` Python :class:`sip.voidptr` object.


.. cfunction:: PyObject *sipCallMethod(int *iserr, PyObject *method, const char *format, ...)

    This calls a Python method passing a tuple of arguments based on a format
    string and associated values in a similar way to the Python
    :cfunc:`PyObject_CallObject()` function.

    :param iserr:
        if this is not ``NULL`` then the location it points to is set to a
        non-zero value if there was an error.
    :param method:
        the Python bound method to call.
    :param format:
        the string of format characters (see :cfunc:`sipBuildResult()`).
    :return:
        If there was an error then ``NULL`` is returned and a Python exception
        is raised.

    It is normally called by handwritten code specified with the
    :directive:`%VirtualCatcherCode` directive with method being the supplied
    ``sipMethod``.


.. cfunction:: int sipCanConvertToEnum(PyObject *obj, const sipTypeDef *td)

    This checks if a Python object can be converted to a named enum.

    :param obj:
        the Python object.
    :param td:
        the enum's :ref:`generated type structure <ref-type-structures>`.
    :return:
        a non-zero value if the object can be converted.


.. cfunction:: int sipCanConvertToInstance(PyObject *obj, sipWrapperType *type, int flags)

    This checks if a Python object can be converted to an instance of a C
    structure or C++ class.

    :param obj:
        the Python object.
    :param type:
        the C/C++ type's :ref:`generated type object <ref-type-objects>`.
    :param flags:
        any combination of the :cmacro:`SIP_NOT_NONE` and
        :cmacro:`SIP_NO_CONVERTORS` flags.
    :return:
        a non-zero value if the object can be converted.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipCanConvertToType()`.


.. cfunction:: int sipCanConvertToMappedType(PyObject *obj, const sipMappedType *mt, int flags)

    This checks if a Python object can be converted to an instance of a C
    structure or C++ class which has been implemented as a mapped type.

    :param obj:
        the Python object.
    :param mt:
        the opaque structure returned by :cfunc:`sipFindMappedType()`.
    :param flags:
        this may be the :cmacro:`SIP_NOT_NONE` flag.
    :return:
        a non-zero value if the object can be converted.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipCanConvertToType()`.


.. cfunction:: int sipCanConvertToType(PyObject *obj, const sipTypeDef *td, int flags)

    This checks if a Python object can be converted to an instance of a C
    structure, C++ class or mapped type.

    :param obj:
        the Python object.
    :param td:
        the C/C++ type's :ref:`generated type structure <ref-type-structures>`.
    :param flags:
        any combination of the :cmacro:`SIP_NOT_NONE` and
        :cmacro:`SIP_NO_CONVERTORS` flags.
    :return:
        a non-zero value if the object can be converted.


.. cfunction:: PyObject *sipClassName(PyObject *obj)

    This gets the class name of a wrapped instance as a Python string.  It
    comes with a reference.

    :param obj:
        the wrapped instance.
    :return:
        the name of the instance's class.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use the
        following::

            PyString_FromString(obj->ob_type->tp_name)


.. cfunction:: PyObject *sipConvertFromConstVoidPtr(const void *cpp)

    This creates a :class:`sip.voidptr` object for a memory address.  The
    object will not be writeable and has no associated size.

    :param cpp:
        the memory address.
    :return:
        the :class:`sip.voidptr` object.


.. cfunction:: PyObject *sipConvertFromConstVoidPtrAndSize(const void *cpp, SIP_SSIZE_T size)

    This creates a :class:`sip.voidptr` object for a memory address.  The
    object will not be writeable and can be used as an immutable buffer object.

    :param cpp:
        the memory address.
    :param size:
        the size associated with the address.
    :return:
        the :class:`sip.voidptr` object.


.. cfunction:: PyObject *sipConvertFromEnum(int eval, const sipTypeDef *td)

    This converts a named C/C++ ``enum`` to an instance of the corresponding
    generated Python type.

    :param eval:
        the enumerated value to convert.
    :param td:
        the enum's :ref:`generated type structure <ref-type-structures>`.
    :return:
        the Python object.


.. cfunction:: PyObject *sipConvertFromInstance(void *cpp, sipWrapperType *type, PyObject *transferObj)

    This converts a C structure or a C++ class instance to an instance of the
    corresponding generated Python type.

    :param cpp:
        the C/C++ instance.
    :param type:
        the type's :ref:`generated type object <ref-type-objects>`.
    :param transferObj:
        this controls the ownership of the returned value.
    :return:
        the Python object.

    If the C/C++ instance has already been wrapped then the result is a
    new reference to the existing class instance object.
    
    If *transferObj* is ``NULL`` and the instance has already been wrapped then
    the ownership is unchanged.
    
    If *transferObj* is ``NULL`` and the instance is newly wrapped then
    ownership will be with C/C++.
    
    If *transferObj* is ``Py_None`` then ownership is transferred to Python via
    a call to :cfunc:`sipTransferBack()`.
    
    Otherwise ownership is transferred to C/C++ and the instance associated
    with *transferObj* via a call to :cfunc:`sipTransferTo()`.
    
    The Python type is influenced by any applicable
    :directive:`%ConvertToSubClassCode` code.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipConvertFromType()`.


.. cfunction:: PyObject *sipConvertFromMappedType(void *cpp, const sipMappedType *mt, PyObject *transferObj)

    This converts a C structure or a C++ class instance wrapped as a mapped
    type to an instance of the corresponding generated Python type.
    
    :param cpp:
        the C/C++ instance.
    :param mt:
        the opaque structure returned by :cfunc:`sipFindMappedType()`.
    :param transferObj:
        this controls the ownership of the returned value.
    :return:
        the Python object.

    If *transferObj*  is ``NULL`` then the ownership is unchanged.
    
    If *transferObj* is ``Py_None`` then ownership is transferred to Python
    via a call to :cfunc:`sipTransferBack()`.
    
    Otherwise ownership is transferred to C/C++ and the instance associated
    with *transferObj* argument via a call to :cfunc:`sipTransferTo()`.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipConvertFromType()`.


.. cfunction:: PyObject *sipConvertFromNamedEnum(int eval, PyTypeObject *type)

    This converts a named C/C++ ``enum`` to an instance of the corresponding
    generated Python type.
    
    :param eval:
        the enumerated value to convert.
    :param type:
        the enum's :ref:`generated type object <ref-type-objects>`.
    :return:
        the Python object.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipConvertFromEnum()`.


.. cfunction:: PyObject *sipConvertFromNewInstance(void *cpp, sipWrapperType *type, PyObject *transferObj)

    This converts a new C structure or a C++ class instance to an instance of
    the corresponding generated Python type.

    :param cpp:
        the C/C++ instance.
    :param type:
        the type's :ref:`generated type object <ref-type-objects>`.
    :param transferObj:
        this controls the ownership of the returned value.
    :return:
        the Python object.

    If *transferObj* is ``NULL`` or ``Py_None`` then ownership will be with
    Python.
    
    Otherwise ownership will be with C/C++ and the instance associated with
    *transferObj*.
    
    The Python type is influenced by any applicable
    :directive:`%ConvertToSubClassCode` code.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipConvertFromNewType()`.


.. cfunction:: PyObject *sipConvertFromNewType(void *cpp, const sipTypeDef *td, PyObject *transferObj)

    This converts a new C structure or a C++ class instance to an instance of
    the corresponding generated Python type.

    :param cpp:
        the C/C++ instance.
    :param td:
        the type's :ref:`generated type structure <ref-type-structures>`.
    :param transferObj:
        this controls the ownership of the returned value.
    :return:
        the Python object.

    If *transferObj* is ``NULL`` or ``Py_None`` then ownership will be with
    Python.
    
    Otherwise ownership will be with C/C++ and the instance associated with
    *transferObj*.
    
    The Python type is influenced by any applicable
    :directive:`%ConvertToSubClassCode` code.


.. cfunction:: SIP_SSIZE_T sipConvertFromSequenceIndex(SIP_SSIZE_T idx, SIP_SSIZE_T len)

    This converts a Python sequence index (i.e. where a negative value refers
    to the offset from the end of the sequence) to a C/C++ array index.  If the
    index was out of range then a negative value is returned and a Python
    exception raised.

    :param idx:
        the sequence index.
    :param len:
        the length of the sequence.
    :return:
        the unsigned array index.


.. cfunction:: int sipConvertFromSliceObject(PyObject *slice, SIP_SSIZE_T length, SIP_SSIZE_T *start, SIP_SSIZE_T *stop, SIP_SSIZE_T *step, SIP_SSIZE_T *slicelength)

    This is a thin wrapper around the Python :cfunc:`PySlice_GetIndicesEx()`
    function provided to make it easier to write handwritten code that is
    compatible with SIP v3.x and versions of Python earlier that v2.3.


.. cfunction:: PyObject *sipConvertFromType(void *cpp, const sipTypeDef *td, PyObject *transferObj)

    This converts a C structure or a C++ class instance to an instance of the
    corresponding generated Python type.

    :param cpp:
        the C/C++ instance.
    :param td:
        the type's :ref:`generated type structure <ref-type-structures>`.
    :param transferObj:
        this controls the ownership of the returned value.
    :return:
        the Python object.

    If the C/C++ instance has already been wrapped then the result is a new
    reference to the existing object.

    If *transferObj* is ``NULL`` and the instance has already been wrapped then
    the ownership is unchanged.
    
    If *transferObj* is ``NULL`` and the instance is newly wrapped then
    ownership will be with C/C++.
    
    If *transferObj* is ``Py_None`` then ownership is transferred to Python via
    a call to :cfunc:`sipTransferBack()`.
    
    Otherwise ownership is transferred to C/C++ and the instance associated
    with *transferObj* via a call to :cfunc:`sipTransferTo()`.
    
    The Python class is influenced by any applicable
    :directive:`%ConvertToSubClassCode` code.


.. cfunction:: PyObject *sipConvertFromVoidPtr(void *cpp)

    This creates a :class:`sip.voidptr` object for a memory address.  The
    object will be writeable but has no associated size.

    :param cpp:
        the memory address.
    :return:
        the :class:`sip.voidptr` object.


.. cfunction:: PyObject *sipConvertFromVoidPtrAndSize(void *cpp, SIP_SSIZE_T size)

    This creates a :class:`sip.voidptr` object for a memory address.  The
    object will be writeable and can be used as a mutable buffer object.
    
    :param cpp:
        the memory address.
    :param size:
        the size associated with the address.
    :return:
        the :class:`sip.voidptr` object.


.. cfunction:: void *sipConvertToInstance(PyObject *obj, sipWrapperType *type, PyObject *transferObj, int flags, int *state, int *iserr)

    This converts a Python object to an instance of a C structure or C++ class
    assuming that a previous call to :cfunc:`sipCanConvertToInstance()` has
    been successful.

    :param obj:
        the Python object.
    :param type:
        the type's :ref:`generated type object <ref-type-objects>`.
    :param transferObj:
        this controls any ownership changes to *obj*.
    :param flags:
        any combination of the :cmacro:`SIP_NOT_NONE` and
        :cmacro:`SIP_NO_CONVERTORS` flags.
    :param state:
        the state of the returned C/C++ instance is returned via this pointer.
    :param iserr:
        the error flag is passed and updated via this pointer.
    :return:
        the C/C++ instance.
    
    If *transferObj* is ``NULL`` then the ownership is unchanged.
    
    If *transferObj* is ``Py_None`` then ownership is transferred to Python via
    a call to :cfunc:`sipTransferBack()`.
    
    Otherwise ownership is transferred to C/C++ and *obj* associated with
    *transferObj* via a call to :cfunc:`sipTransferTo()`.

    If *state* is not ``NULL`` then the location it points to is set to
    describe the state of the returned C/C++ instance and is the value returned
    by any :directive:`%ConvertToTypeCode`.  The calling code must then release
    the value at some point to prevent a memory leak by calling
    :cfunc:`sipReleaseInstance()`.

    If there is an error then the location *iserr* points to is set to a
    non-zero value.  If it was initially a non-zero value then the conversion
    isn't attempted in the first place.  (This allows several calls to be made
    that share the same error flag so that it only needs to be tested once
    rather than after each call.)

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipConvertToType()`.


.. cfunction:: void *sipConvertToMappedType(PyObject *obj, const sipMappedType *mt, PyObject *transferObj, int flags, int *state, int *iserr)

    This converts a Python object to an instance of a C structure or C++
    class that is implemented as a mapped type assuming that a previous call to
    :cfunc:`sipCanConvertToMappedType()` has been successful.

    :param obj:
        the Python object.
    :param mt:
        the opaque structure returned by :cfunc:`sipFindMappedType()`.
    :param transferObj:
        this controls any ownership changes to *obj*.
    :param flags:
        this may be the :cmacro:`SIP_NOT_NONE` flag.
    :param state:
        the state of the returned C/C++ instance is returned via this pointer.
    :param iserr:
        the error flag is passed and updated via this pointer.
    :return:
        the C/C++ instance.

    If *transferObj* is ``NULL`` then the ownership is unchanged.
    
    If *transferObj* is ``Py_None`` then ownership is transferred to Python via
    a call to :cfunc:`sipTransferBack()`.
    
    Otherwise ownership is transferred to C/C++ and *obj* associated with
    *transferObj* via a call to :cfunc:`sipTransferTo()`.
    
    If *state* is not ``NULL`` then the location it points to is set to
    describe the state of the returned C/C++ instance and is the value returned
    by any :directive:`%ConvertToTypeCode`.  The calling code must then release
    the value at some point to prevent a memory leak by calling
    :cfunc:`sipReleaseMappedType()`.
    
    If there is an error then the location *iserr* points to is set to a
    non-zero value.  If it was initially a non-zero value then the conversion
    isn't attempted in the first place.  (This allows several calls to be made
    that share the same error flag so that it only needs to be tested once
    rather than after each call.)

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipConvertToType()`


.. cfunction:: void *sipConvertToType(PyObject *obj, const sipTypeDef *td, PyObject *transferObj, int flags, int *state, int *iserr)

    This converts a Python object to an instance of a C structure, C++ class or
    mapped type assuming that a previous call to :cfunc:`sipCanConvertToType()`
    has been successful.

    :param obj:
        the Python object.
    :param td:
        the type's :ref:`generated type structure <ref-type-structures>`.
    :param transferObj:
        this controls any ownership changes to *obj*.
    :param flags:
        any combination of the :cmacro:`SIP_NOT_NONE` and
        :cmacro:`SIP_NO_CONVERTORS` flags.
    :param state:
        the state of the returned C/C++ instance is returned via this pointer.
    :param iserr:
        the error flag is passed and updated via this pointer.
    :return:
        the C/C++ instance.
    
    If *transferObj* is ``NULL`` then the ownership is unchanged.  If it is
    ``Py_None`` then ownership is transferred to Python via a call to
    :cfunc:`sipTransferBack()`.
    
    Otherwise ownership is transferred to C/C++ and *obj* associated with
    *transferObj* via a call to :cfunc:`sipTransferTo()`.

    If *state* is not ``NULL`` then the location it points to is set to
    describe the state of the returned C/C++ instance and is the value returned
    by any :directive:`%ConvertToTypeCode`.  The calling code must then release
    the value at some point to prevent a memory leak by calling
    :cfunc:`sipReleaseType()`.
    
    If there is an error then the location *iserr* points to is set to a
    non-zero value.  If it was initially a non-zero value then the conversion
    isn't attempted in the first place.  (This allows several calls to be made
    that share the same error flag so that it only needs to be tested once
    rather than after each call.)


.. cfunction:: void *sipConvertToVoidPtr(PyObject *obj)

    This converts a Python object to a memory address.
    :cfunc:`PyErr_Occurred()` must be used to determine if the conversion was
    successful.

    :param obj:
        the Python object which may be ``Py_None``, a :class:`sip.voidptr` or a
        :ctype:`PyCObject`.
    :return:
        the memory address.


.. cfunction:: int sipExportSymbol(const char *name, void *sym)

    Python does not allow extension modules to directly access symbols in
    another extension module.  This exports a symbol, referenced by a name,
    that can subsequently be imported, using :cfunc:`sipImportSymbol()`, by
    another module.

    :param name:
        the name of the symbol.
    :param sym:
        the value of the symbol.
    :return:
        0 if there was no error.  A negative value is returned if *name* is
        already associated with a symbol or there was some other error.


.. cfunction:: sipWrapperType *sipFindClass(const char *type)

    This returns a pointer to the :ref:`generated type object
    <ref-type-objects` corresponding to a C/C++ type.

    :param type:
        the C/C++ declaration of the type.
    :return:
        the generated type object.  This will not change and may be saved in a
        static cache.  ``NULL`` is returned if the C/C++ type doesn't exist.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipFindType()`.


.. cfunction:: const sipMappedType *sipFindMappedType(const char *type)

    This returns a pointer to an opaque structure describing a mapped type.

    :param type:
        the C/C++ declaration of the type.
    :return:
        the opaque structure.  This will not change and may be saved in a
        static cache.  ``NULL`` is returned if the C/C++ type doesn't exist.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipFindType()`.


.. cfunction:: PyTypeObject *sipFindNamedEnum(const char *type)

    This returns a pointer to the :ref:`generated Python type object
    <ref-enum-type-objects>` corresponding to a named C/C++ enum.

    :param type:
        the C/C++ declaration of the enum.
    :return:
        the generated Python type object.  This will not change and may be
        saved in a static cache.  ``NULL`` is returned if the C/C++ enum
        doesn't exist.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipFindType()`.


.. cfunction:: const sipTypeDef *sipFindType(const char *type)

    This returns a pointer to the :ref:`generated type structure
    <ref-type-structures>` corresponding to a C/C++ type.

    :param type:
        the C/C++ declaration of the type.
    :return:
        the generated type structure.  This will not change and may be saved in
        a static cache.  ``NULL`` is returned if the C/C++ type doesn't exist.


.. cfunction:: void *sipForceConvertToInstance(PyObject *obj, sipWrapperType *type, PyObject *transferObj, int flags, int *state, int *iserr)

    This converts a Python object to an instance of a C structure or C++ class
    by calling :cfunc:`sipCanConvertToInstance()` and, if it is successfull,
    calling :cfunc:`sipConvertToInstance()`.

    See :cfunc:`sipConvertToInstance()` for a full description of the
    arguments.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipForceConvertToType()`.


.. cfunction:: void *sipForceConvertToMappedType(PyObject *obj, const sipMappedType *mt, PyObject *transferObj, int flags, int *state, int *iserr)

    This converts a Python object to an instance of a C structure or C++ class
    which has been implemented as a mapped type by calling
    :cfunc:`sipCanConvertToMappedType()` and, if it is successfull, calling
    :cfunc:`sipConvertToMappedType()`.

    See :cfunc:`sipConvertToMappedType()` for a full description of the
    arguments.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipForceConvertToType()`.


.. cfunction:: void *sipForceConvertToType(PyObject *obj, const sipTypeDef *td, PyObject *transferObj, int flags, int *state, int *iserr)

    This converts a Python object to an instance of a C structure, C++ class or
    mapped type by calling :cfunc:`sipCanConvertToType()` and, if it is
    successfull, calling :cfunc:`sipConvertToType()`.

    See :cfunc:`sipConvertToType()` for a full description of the arguments.


.. cfunction:: void sipFree(void *mem)

    This returns an area of memory allocated by :cfunc:`sipMalloc()` to the
    heap.

    :param mem:
        the memory address.


.. cfunction:: PyObject *sipGetPyObject(void *cppptr, const sipTypeDef *td)

    This returns a borrowed reference to the Python object for a C structure or
    C++ class instance.

    :param cppptr:
        the pointer to the C/C++ instance.
    :param td:
        the :ref:`generated type structure <ref-type-structures>` corresponding
        to the C/C++ type.
    :return:
        the Python object or ``NULL`` (and no exception is raised) if the
        C/C++ instance hasn't been wrapped.


.. cfunction:: int sipGetState(PyObject *transferObj)

    The :directive:`%ConvertToTypeCode` directive requires that the provided
    code returns an ``int`` describing the state of the converted value.  The
    state usually depends on any transfers of ownership that have been
    requested.  This is a convenience function that returns the correct state
    when the converted value is a temporary.

    :param transferObj:
        the object that describes the requested transfer of ownership.
    :return:
        the state of the converted value.


.. cfunction:: PyObject *sipGetWrapper(void *cppptr, sipWrapperType *type)

    This returns a borrowed reference to the wrapped instance object for a C
    structure or C++ class instance.
    
    :param cppptr:
        the pointer to the C/C++ instance.
    :param type:
        the :ref:`generated type object <ref-type-objects>` corresponding to
        the C/C++ type.
    :return:
        the Python object or ``NULL`` (and no exception is raised) if the
        C/C++ instance hasn't been wrapped.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipGetPyObject()`.


.. cfunction:: void *sipImportSymbol(const char *name)

    Python does not allow extension modules to directly access symbols in
    another extension module.  This imports a symbol, referenced by a name,
    that has previously been exported, using :cfunc:`sipExportSymbol()`, by
    another module.

    :param name:
        the name of the symbol.
    :return:
        the value of the symbol.  ``NULL`` is returned if there is no such
        symbol.


.. ctype:: sipIntTypeClassMap

    This C structure is used with :cfunc:`sipMapIntToClass()` to define a
    mapping between integer based RTTI and :ref:`generated type objects
    <ref-type-objects>`.  The structure elements are as follows.

    .. cmember:: int typeInt

        The integer RTTI.

    .. cmember:: sipWrapperType **pyType.

        A pointer to the corresponding generated type object.

    .. note::
        This is deprecated from SIP v4.8.


.. cfunction:: int sipIsAPIEnabled(const char *name, int from, int to)

    .. versionadded:: 4.9

    This checks to see if the current version number of an API falls within a
    given range.  See :ref:`ref-incompat-apis` for more detail.

    :param name:
        the name of the API.
    :param from:
        the lower bound of the range.  For the API to be enabled its version
        number must be greater than or equal to *from*.  If *from* is 0 then
        this check isn't made.
    :param to:
        the upper bound of the range.  For the API to be enabled its version
        number must be less than *to*.  If *to* is 0 then this check isn't
        made.
    :return:
        a non-zero value if the API is enabled.


.. cfunction:: unsigned long sipLong_AsUnsignedLong(PyObject *obj)

    This function is a thin wrapper around :cfunc:`PyLong_AsUnsignedLong()`
    that works around a bug in Python v2.3.x and earlier when converting
    integer objects.


.. cfunction:: void *sipMalloc(size_t nbytes)

    This allocates an area of memory on the heap using the Python
    :cfunc:`PyMem_Malloc()` function.  The memory is freed by calling
    :cfunc:`sipFree()`.

    :param nbytes:
        the number of bytes to allocate.
    :return:
        the memory address.  If there was an error then ``NULL`` is returned
        and a Python exception raised.


.. cfunction:: sipWrapperType *sipMapIntToClass(int type, const sipIntTypeClassMap *map, int maplen)

    This can be used in :directive:`%ConvertToSubClassCode` code as a
    convenient way of converting integer based RTTI to the corresponding
    :ref:`generated type object <ref-type-objects>`.

    :param type:
        the integer RTTI.
    :param map:
        the table of known RTTI and the corresponding type objects (see
        :ctype:`sipIntTypeClassMap`).  The entries in the table must be sorted
        in ascending order of RTTI.
    :param maplen:
        the number of entries in the table.
    :return:
        the corresponding type object, or ``NULL`` if *type* wasn't in *map*.

    .. note::
        This is deprecated from SIP v4.8.


.. cfunction:: sipWrapperType *sipMapStringToClass(char *type, const sipStringTypeClassMap *map, int maplen)

    This can be used in :directive:`%ConvertToSubClassCode` code as a
    convenient way of converting ``'\0'`` terminated string based RTTI to the
    corresponding :ref:`generated type object <ref-type-objects>`.

    :param type:
        the string RTTI.
    :param map:
        the table of known RTTI and the corresponding type objects (see
        :ctype:`sipStringTypeClassMap`).  The entries in the table must be
        sorted in ascending order of RTTI.
    :param maplen:
        the number of entries in the table.
    :return:
        the corresponding type object, or ``NULL`` if *type* wasn't in *map*.

    .. note::
        This is deprecated from SIP v4.8.


.. cfunction:: int sipParseResult(int *iserr, PyObject *method, PyObject *result, const char *format, ...)

    This converts a Python object (usually returned by a method) to C/C++ based
    on a format string and associated values in a similar way to the Python
    :cfunc:`PyArg_ParseTuple()` function.

    :param iserr:
        if this is not ``NULL`` then the location it points to is set to a
        non-zero value if there was an error.
    :param method:
        the Python method that returned *result*.
    :param result:
        the Python object returned by *method*.
    :param format:
        the format string.
    :return:
        0 if there was no error.  Otherwise a negative value is returned, and
        an exception raised.

    This is normally called by handwritten code specified with the
    :directive:`%VirtualCatcherCode` directive with *method* being the supplied
    ``sipMethod`` and *result* being the value returned by
    :cfunc:`sipCallMethod()`.

    If *format* begins and ends with parentheses then *result* must be a Python
    tuple and the rest of *format* is applied to the tuple contents.

    In the following description the first letter is the format character, the
    entry in parentheses is the Python object type that the format character
    will convert, and the entry in brackets are the types of the C/C++ values
    to be passed. 

    ``ae`` (object) [char \*]
        Convert a Python string-like object of length 1 to a C/C++ ``char``
        according to the encoding ``e``.  ``e`` can either be ``A`` for ASCII,
        ``L`` for Latin-1, or ``8`` for UTF-8.  For Python v2 the object may be
        either a string or a unicode object that can be encoded.  For Python v3
        the object may either be a bytes object or a string object that can be
        encoded.  An object that supports the buffer protocol may also be used.

    ``b`` (integer) [bool \*]
        Convert a Python integer to a C/C++ ``bool``.

    ``c`` (string/bytes) [char \*]
        Convert a Python v2 string object or a Python v3 bytes object of length
        1 to a C/C++ ``char``.

    ``d`` (float) [double \*]
        Convert a Python floating point number to a C/C++ ``double``.

    ``e`` (integer) [enum \*]
        Convert a Python integer to an anonymous C/C++ ``enum``.

    ``f`` (float) [float \*]
        Convert a Python floating point number to a C/C++ ``float``.

    ``g`` (string/bytes) [const char \*\*, :cmacro:`SIP_SSIZE_T` \*]
        Convert a Python v2 string object or a Python v3 bytes object to a
        C/C++ character array and its length.  If the Python object is
        ``Py_None`` then the array and length are ``NULL`` and zero
        respectively.

    ``h`` (integer) [short \*]
        Convert a Python integer to a C/C++ ``short``.

    ``i`` (integer) [int \*]
        Convert a Python integer to a C/C++ ``int``.

    ``l`` (long) [long \*]
        Convert a Python long to a C/C++ ``long``.

    ``m`` (long) [unsigned long \*]
        Convert a Python long to a C/C++ ``unsigned long``.

    ``n`` (long) [long long \*]
        Convert a Python long to a C/C++ ``long long``.

    ``o`` (long) [unsigned long long \*]
        Convert a Python long to a C/C++ ``unsigned long long``.

    ``s`` (string/bytes) [const char \*\*]
        Convert a Python v2 string object or a Python v3 bytes object to a
        C/C++ ``'\0'`` terminated string.  If the Python object is ``Py_None``
        then the string is ``NULL``.

        .. note::
            This is deprecated from SIP v4.8.  Instead you should use ``B``.

    ``t`` (long) [unsigned short \*]
        Convert a Python long to a C/C++ ``unsigned short``.

    ``u`` (long) [unsigned int \*]
        Convert a Python long to a C/C++ ``unsigned int``.

    ``w`` (unicode/string) [wchar_t \*]
        Convert a Python v2 string or unicode object or a Python v3 string
        object of length 1 to a C/C++ wide character.

    ``x`` (unicode/string) [wchar_t \*\*]
        Convert a Python v2 string or unicode object or a Python v3 string
        object to a C/C++ ``L'\0'`` terminated wide character string.  If the
        Python object is ``Py_None`` then the string is ``NULL``.

    ``Ae`` (object) [int, const char \*\*]
        Convert a Python string-like object to a C/C++ ``'\0'`` terminated
        string according to the encoding ``e``.  ``e`` can either be ``A`` for
        ASCII, ``L`` for Latin-1, or ``8`` for UTF-8.  If the Python object is
        ``Py_None`` then the string is ``NULL``.  The integer uniquely
        identifies the object in the context defined by the ``S`` format
        character and allows an extra reference to the object to be kept to
        ensure that the string remains valid.  For Python v2 the object may be
        either a string or a unicode object that can be encoded.  For Python v3
        the object may either be a bytes object or a string object that can be
        encoded.  An object that supports the buffer protocol may also be used.

    ``B`` (string/bytes) [int, const char \*\*]
        Convert a Python v2 string object or a Python v3 bytes object to a
        C/C++ ``'\0'`` terminated string.  If the Python object is ``Py_None``
        then the string is ``NULL``.  The integer uniquely identifies the
        object in the context defined by the ``S`` format character and allows
        an extra reference to the object to be kept to ensure that the string
        remains valid.

    ``Cf`` (wrapped class) [:ctype:`sipWrapperType` \*, int \*, void \*\*]
        Convert a Python object to a C structure or a C++ class instance and
        return its state as described in :cfunc:`sipConvertToInstance()`.
        ``f`` is a combination of the following flags encoded as an ASCII
        character by adding ``0`` to the combined value:

            0x01 disallows the conversion of ``Py_None`` to ``NULL``

            0x02 implements the :fanno:`Factory` and :fanno:`TransferBack`
                 annotations

            0x04 suppresses the return of the state of the returned C/C++
                 instance.  Note that the ``int *`` used to return the state is
                 not passed if this flag is specified.

        .. note::
            This is deprecated from SIP v4.8.  Instead you should use ``Hf``.

    ``Df`` (wrapped instance) [const :ctype:`sipTypeDef` \*, int \*, void \*\*]
        Convert a Python object to a C structure, C++ class or mapped type
        instance and return its state as described in
        :cfunc:`sipConvertToType()`.  ``f`` is a combination of the following
        flags encoded as an ASCII character by adding ``0`` to the combined
        value:

            0x01 disallows the conversion of ``Py_None`` to ``NULL``

            0x02 implements the :fanno:`Factory` and :fanno:`TransferBack`
                 annotations

            0x04 suppresses the return of the state of the returned C/C++
                 instance.  Note that the ``int *`` used to return the state is
                 not passed if this flag is specified.

        .. note::
            This is deprecated from SIP v4.10.1.  Instead you should use
            ``Hf``.

    ``E`` (wrapped enum) [PyTypeObject \*, enum \*]
        Convert a Python named enum type to the corresponding C/C++ ``enum``.

        .. note::
            This is deprecated from SIP v4.8.  Instead you should use ``F``.

    ``F`` (wrapped enum) [:ctype:`sipTypeDef` \*, enum \*]
        Convert a Python named enum type to the corresponding C/C++ ``enum``.

    ``G`` (unicode/string) [wchar_t \*\*, :cmacro:`SIP_SSIZE_T` \*]
        Convert a Python v2 string or unicode object or a Python v3 string
        object to a C/C++ wide character array and its length.  If the Python
        object is ``Py_None`` then the array and length are ``NULL`` and zero
        respectively.

    ``Hf`` (wrapped instance) [const :ctype:`sipTypeDef` \*, int \*, void \*\*]
        Convert a Python object to a C structure, C++ class or mapped type
        instance as described in :cfunc:`sipConvertToType()`.  ``f`` is a
        combination of the following flags encoded as an ASCII character by
        adding ``0`` to the combined value:

            0x01 disallows the conversion of ``Py_None`` to ``NULL``

            0x02 implements the :fanno:`Factory` and :fanno:`TransferBack`
                 annotations

            0x04 returns a copy of the C/C++ instance.

    ``N`` (object) [PyTypeObject \*, :PyObject \*\*]
        A Python object is checked to see if it is a certain type and then
        returned without any conversions.  The reference count is incremented.
        The Python object may be ``Py_None``.

    ``O`` (object) [PyObject \*\*]
        A Python object is returned without any conversions.  The reference
        count is incremented.

    ``S`` [:ctype:`sipSimpleWrapper` \*]
        This format character, if used, must be the first.  It is used with
        other format characters to define a context and doesn't itself convert
        an argument.

    ``T`` (object) [PyTypeObject \*, PyObject \*\*]
        A Python object is checked to see if it is a certain type and then
        returned without any conversions.  The reference count is incremented.
        The Python object may not be ``Py_None``.

    ``V`` (:class:`sip.voidptr`) [void \*]
        Convert a Python :class:`sip.voidptr` object to a C/C++ ``void *``.

    ``Z`` (object) []
        Check that a Python object is ``Py_None``.  No value is returned.


.. cfunction:: int sipRegisterAttributeGetter(const sipTypeDef *td, sipAttrGetterFunc getter)

    This registers a handler that will called just before SIP needs to get an
    attribute from a wrapped type's dictionary for the first time.  The handler
    must then populate the type's dictionary with any lazy attributes.

    :param td:
        the optional :ref:`generated type structure <ref-type-structures>` that
        determines which types the handler will be called for.
    :param getter:
        the handler function.
    :return:
        0 if there was no error, otherwise -1 is returned.

    If *td* is not ``NULL`` then the handler will only be called for types with
    that type or that are sub-classed from it.  Otherwise the handler will be
    called for all types.

    A handler has the following signature.

    int handler(const :ctype:`sipTypeDef` \*td, PyObject \*dict)

        *td* is the generated type definition of the type whose dictionary is
        to be populated.

        *dict* is the dictionary to be populated.

        0 if there was no error, otherwise -1 is returned.

    See the section :ref:`ref-lazy-type-attributes` for more details.


.. cfunction:: int sipRegisterPyType(PyTypeObject *type)

    This registers a Python type object that can be used as the meta-type or
    super-type of a wrapped C++ type.
    
    :param type:
        the type object.
    :return:
        0 if there was no error, otherwise -1 is returned.

    See the section :ref:`ref-types-metatypes` for more details.


.. cfunction:: void sipReleaseInstance(void *cpp, sipWrapperType *type, int state)

    This destroys a wrapped C/C++ instance if it was a temporary instance.  It
    is called after a call to either :cfunc:`sipConvertToInstance()` or
    :cfunc:`sipForceConvertToInstance()`.
    
    :param cpp:
        the C/C++ instance.
    :param type:
        the type's :ref:`generated type object <ref-type-objects>`.
    :param state:
        describes the state of the C/C++ instance.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipReleaseType()`.


.. cfunction:: void sipReleaseMappedType(void *cpp, const sipMappedType *mt, int state)

    This destroys a wrapped C/C++ mapped type if it was a temporary instance.
    It is called after a call to either :cfunc:`sipConvertToMappedType()` or
    :cfunc:`sipForceConvertToMappedType()`.
    
    :param cpp:
        the C/C++ instance.
    :param mt:
        the opaque structure returned by :cfunc:`sipFindMappedType()`.
    :param state:
        describes the state of the C/C++ instance.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use
        :cfunc:`sipReleaseType()`.


.. cfunction:: void sipReleaseType(void *cpp, const sipTypeDef *td, int state)

    This destroys a wrapped C/C++ or mapped type instance if it was a temporary
    instance.  It is called after a call to either :cfunc:`sipConvertToType()`
    or :cfunc:`sipForceConvertToType()`.
    
    :param cpp:
        the C/C++ instance.
    :param td:
        the type's :ref:`generated type structure <ref-type-structures>`.
    :param state:
        describes the state of the C/C++ instance.


.. cfunction:: const char *sipResolveTypedef(const char *name)

    This returns the value of a C/C++ typedef.

    :param name:
        the name of the typedef.
    :return:
        the value of the typedef or ``NULL`` if there was no such typedef.


.. ctype:: sipSimpleWrapper

    This is a C structure that represents a Python wrapped instance whose type
    is :class:`sip.simplewrapper`.  It is an extension of the ``PyObject``
    structure and so may be safely cast to it.

    .. cmember:: void *data

        This is initialised to the address of the C/C++ instance.  If an access
        function is subsequently provided then it may be used for any purpose
        by the access function.

    .. cmember:: sipAccessFunc access_func

        This is the address of an optional access function that is called, with
        a pointer to this structure as its first argument.  If its second
        argument is ``UnguardedPointer`` then it returns the address of the
        C/C++ instance, even if it is known that its value is no longer valid.
        If the second argument is ``GuardedPointer`` then it returns the
        address of the C++ instance or ``0`` if it is known to be invalid.  If
        the second argument is ``ReleaseGuard`` then the structure is being
        deallocated and any dynamic resources used by the access function
        should be released.  If there is no access function then the
        :cmember:`sipSimpleWrapper.data` is used as the address of the C/C++
        instance.  Typically a custom meta-type is used to set an access method
        after the Python object has been created.

    .. cmember:: PyObject *user

        This can be used for any purpose by handwritten code and will
        automatically be garbage collected at the appropriate time.


.. cvar:: PyTypeObject *sipSimpleWrapper_Type

    This is the type of a :ctype:`sipSimpleWrapper` structure and is the C
    implementation of :class:`sip.simplewrapper`.  It may be safely cast to
    :ctype:`sipWrapperType`.


.. ctype:: sipStringTypeClassMap

    This C structure is used with :cfunc:`sipMapStringToClass()` to define a
    mapping between ``'\0'`` terminated string based RTTI and
    :ref:`ref-type-objects`.  The structure elements are as follows.

    .. cmember:: char *typeString

        The ``'\0'`` terminated string RTTI.

    .. cmember:: sipWrapperType **pyType.

        A pointer to the corresponding generated type object.

    .. note::
        This is deprecated from SIP v4.8.


.. cfunction:: void sipTransferBack(PyObject *obj)

    This transfers ownership of a Python wrapped instance to Python (see
    :ref:`ref-object-ownership`).

    :param obj:
        the wrapped instance.
        
    In addition, any association of the instance with regard to the cyclic
    garbage collector with another instance is removed.


.. cfunction:: void sipTransferBreak(PyObject *obj)

    Any association of a Python wrapped instance with regard to the cyclic
    garbage collector with another instance is removed.  Ownership of the
    instance should be with C++.

    :param obj:
        the wrapped instance.


.. cfunction:: void sipTransferTo(PyObject *obj, PyObject *owner)

    This transfers ownership of a Python wrapped instance to C++ (see
    :ref:`ref-object-ownership`).

    :param obj:
        the wrapped instance.
    :param owner:
        an optional wrapped instance that *obj* becomes associated with with
        regard to the cyclic garbage collector.  If *owner* is ``NULL`` then no
        such association is made.  If *owner* is the same value as *obj* then
        any reference cycles involving *obj* can never be detected or broken by
        the cyclic garbage collector.  Responsibility for calling the C++
        instance's destructor is always transfered to C++.


.. cfunction:: PyTypeObject *sipTypeAsPyTypeObject(sipTypeDef *td)

    This returns a pointer to the Python type object that SIP creates for a
    :ref:`generated type structure <ref-type-structures>`.

    :param td:
        the type structure.
    :return:
        the Python type object.  If the type structure refers to a mapped type
        then ``NULL`` will be returned.

    If the type structure refers to a C structure or C++ class then the
    Python type object may be safely cast to a :ctype:`sipWrapperType`.


.. cfunction:: const sipTypeDef *sipTypeFromPyTypeObject(PyTypeObject *py_type)

    This returns the :ref:`generated type structure <ref-type-structures>` for
    a Python type object.

    :param py_type:
        the Python type object.
    :return:
        the type structure or ``NULL`` if the Python type object doesn't
        correspond to a type structure.


.. cfunction:: int sipTypeIsClass(sipTypeDef *td)

    This checks if a :ref:`generated type structure <ref-type-structures>`
    refers to a C structure or C++ class.

    :param td:
        the type structure.
    :return:
        a non-zero value if the type structure refers to a structure or class.


.. cfunction:: int sipTypeIsEnum(sipTypeDef *td)

    This checks if a :ref:`generated type structure <ref-type-structures>`
    refers to a named enum.

    :param td:
        the type structure.
    :return:
        a non-zero value if the type structure refers to an enum.


.. cfunction:: int sipTypeIsMapped(sipTypeDef *td)

    This checks if a :ref:`generated type structure <ref-type-structures>`
    refers to a mapped type.

    :param td:
        the type structure.
    :return:
        a non-zero value if the type structure refers to a mapped type.


.. cfunction:: int sipTypeIsNamespace(sipTypeDef *td)

    This checks if a :ref:`generated type structure <ref-type-structures>`
    refers to a C++ namespace.

    :param td:
        the type structure.
    :return:
        a non-zero value if the type structure refers to a namespace.


.. cfunction:: const char *sipTypeName(const sipTypeDef *td)

    This returns the C/C++ name of a wrapped type.

    :param td:
        the type's :ref:`generated type structure <ref-type-structures>`.
    :return:
        the name of the C/C++ type.


.. cfunction:: const sipTypeDef *sipTypeScope(const sipTypeDef *td)

    This returns the :ref:`generated type structure <ref-type-structures>` of
    the enclosing scope of another generated type structure.

    :param td:
        the type structure.
    :return:
        the type structure of the scope or ``NULL`` if the type has no scope.


.. cvar:: PyTypeObject *sipVoidPtr_Type

    This is the type of a ``PyObject`` structure that is used to wrap a
    ``void *``.


.. ctype:: sipWrapper

    This is a C structure that represents a Python wrapped instance whose type
    is :class:`sip.wrapper`.  It is an extension of the
    :ctype:`sipSimpleWrapper` and ``PyObject`` structures and so may be safely
    cast to both.


.. cfunction:: int sipWrapper_Check(PyObject *obj)

    This checks if a Python object is a wrapped instance.

    :param obj:
        the Python object.
    :return:
        a non-zero value if the Python object is a wrapped instance.

    .. note::
        This is deprecated from SIP v4.8.  Instead you should use the
        following::

            PyObject_TypeCheck(obj, sipWrapper_Type)


.. cvar:: PyTypeObject *sipWrapper_Type

    This is the type of a :ctype:`sipWrapper` structure and is the C
    implementation of :class:`sip.wrapper`.  It may be safely cast to
    :ctype:`sipWrapperType`.


.. ctype:: sipWrapperType

    This is a C structure that represents a SIP generated type object.  It is
    an extension of the ``PyTypeObject`` structure (which is itself an
    extension of the ``PyObject`` structure) and so may be safely cast to
    ``PyTypeObject`` (and ``PyObject``).


.. cvar:: PyTypeObject *sipWrapperType_Type

    This is the type of a :ctype:`sipWrapperType` structure and is the C
    implementation of :class:`sip.wrappertype`.


.. _ref-type-structures:

Generated Type Structures
-------------------------

SIP generates an opaque type structure for each C structure, C++ class, C++
namespace, named enum or mapped type being wrapped.  These are
:ctype:`sipTypeDef` structures and are used extensively by the SIP API.

The names of these structure are prefixed by ``sipType_``.

For those structures that correspond to C structures, C++ classes, C++
namespaces or named enums the remaining part of the name is the fully
qualified name of the structure, class, namespace or enum name.  Any ``::``
scope separators are replaced by an underscore.  For example, the type object
for class ``Klass`` is ``sipType_Klass``.

For those structure that correspond to mapped types the remaining part of the
name is generated by SIP.  The only way for handwritten code to obtain a
pointer to a structure for a mapped type is to use :cfunc:`sipFindType()`.

The type structures of all imported types are available to handwritten code.


.. _ref-type-objects:

Generated Type Objects
----------------------

SIP generates a :ctype:`sipWrapperType` type object for each C structure or
C++ class being wrapped.

These objects are named with the structure or class name prefixed by
``sipClass_``.  For example, the type object for class ``Klass`` is
``sipClass_Klass``.

.. note::
    Using these names is deprecated from SIP v4.8.  Instead use the
    corresponding generated type structure (see :ref:`ref-type-structures`) and
    :cfunc:`sipTypeAsPyTypeObject()`.


.. _ref-enum-type-objects:

Generated Named Enum Type Objects
---------------------------------

SIP generates a type object for each named enum being wrapped.  These are
PyTypeObject structures.  (Anonymous enums are wrapped as Python integers.)

These objects are named with the fully qualified enum name (i.e. including any
enclosing scope) prefixed by ``sipEnum_``.  For example, the type object for
enum ``Enum`` defined in class ``Klass`` is ``sipEnum_Klass_Enum``.

.. note::
    Using these names is deprecated from SIP v4.8.  Instead use the
    corresponding generated type structure (see :ref:`ref-type-structures`) and
    :cfunc:`sipTypeAsPyTypeObject()`.


.. _ref-derived-classes:

Generated Derived Classes
-------------------------

For most C++ classes being wrapped SIP generates a derived class with the same
name prefixed by ``sip``.  For example, the derived class for class ``Klass``
is ``sipKlass``.

If a C++ class doesn't have any virtual or protected methods in it or any of
it's super-class hierarchy, or does not emit any Qt signals, then a derived
class is not generated.

Most of the time handwritten code should ignore the derived classes.  The only
exception is that handwritten constructor code specified using the
:directive:`%MethodCode` directive should call the derived class's constructor
(which has the same C++ signature) rather then the wrapped class's constructor.


.. _ref-exception-objects:

Generated Exception Objects
---------------------------

SIP generates a Python object for each exception defined with the
:directive:`%Exception` directive.

These objects are named with the fully qualified exception name (i.e. including
any enclosing scope) prefixed by ``sipException_``.  For example, the type
object for enum ``Except`` defined in class ``Klass`` is
``sipException_Klass_Except``.

The objects of all imported exceptions are available to handwritten code.
