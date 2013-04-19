/*
 * SIP library code.
 *
 * Copyright (c) 2010 Riverbank Computing Limited <info@riverbankcomputing.com>
 *
 * This file is part of SIP.
 *
 * This copy of SIP is licensed for use under the terms of the SIP License
 * Agreement.  See the file LICENSE for more details.
 *
 * This copy of SIP may also used under the terms of the GNU General Public
 * License v2 or v3 as published by the Free Software Foundation which can be
 * found in the files LICENSE-GPL2 and LICENSE-GPL3 included in this package.
 *
 * SIP is supplied WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */


#include <Python.h>

#include <stddef.h>

#include "sip.h"
#include "sipint.h"


/* The object data structure. */
typedef struct {
    PyObject_HEAD
    void *voidptr;
    SIP_SSIZE_T size;
    int rw;
} sipVoidPtrObject;


/* The structure used to hold the results of a voidptr conversion. */
struct vp_values {
    void *voidptr;
    SIP_SSIZE_T size;
    int rw;
};


static PyObject *make_voidptr(void *voidptr, SIP_SSIZE_T size, int rw);
static int vp_convertor(PyObject *arg, struct vp_values *vp);


/*
 * Implement __new__ for the type.
 */
static PyObject *sipVoidPtr_new(PyTypeObject *subtype, PyObject *args,
        PyObject *kw)
{
    static char *kwlist[] = {"address", "size", "writeable", NULL};

    struct vp_values vp_conversion;
    SIP_SSIZE_T size = -1;
    int rw = -1;
    PyObject *obj;

    if (!PyArg_ParseTupleAndKeywords(args, kw,
#if PY_VERSION_HEX >= 0x02050000
            "O&|ni:voidptr",
#else
            "O&|ii:voidptr",
#endif
            kwlist, vp_convertor, &vp_conversion, &size, &rw))
        return NULL;

    /* Use the explicit size if one was given. */
    if (size >= 0)
        vp_conversion.size = size;

    /* Use the explicit writeable flag if one was given. */
    if (rw >= 0)
        vp_conversion.rw = rw;

    /* Create the instance. */
    if ((obj = subtype->tp_alloc(subtype, 0)) == NULL)
        return NULL;

    /* Save the values. */
    ((sipVoidPtrObject *)obj)->voidptr = vp_conversion.voidptr;
    ((sipVoidPtrObject *)obj)->size = vp_conversion.size;
    ((sipVoidPtrObject *)obj)->rw = vp_conversion.rw;

    return obj;
}


#if PY_MAJOR_VERSION >= 3
/*
 * The read buffer implementation for Python v3.
 */
static int sipVoidPtr_getbuffer(PyObject *self, Py_buffer *buf, int flags)
{
    sipVoidPtrObject *v = (sipVoidPtrObject *)self;

    return PyBuffer_FillInfo(buf, self, v->voidptr, v->size, !v->rw, flags);
}
#endif


#if PY_MAJOR_VERSION < 3
/*
 * The read buffer implementation for Python v2.
 */
static SIP_SSIZE_T sipVoidPtr_getbuffer(PyObject *self, SIP_SSIZE_T seg,
        void **ptr)
{
    SIP_SSIZE_T size = ((sipVoidPtrObject *)self)->size;

    if (size < 0 || seg != 0)
    {
        PyErr_SetString(PyExc_SystemError, "invalid buffer segment");
        return -1;
    }

    *ptr = ((sipVoidPtrObject *)self)->voidptr;

    return size;
}
#endif


#if PY_MAJOR_VERSION < 3
/*
 * The write buffer implementation for Python v2.
 */
static SIP_SSIZE_T sipVoidPtr_getwritebuffer(PyObject *self, SIP_SSIZE_T seg,
        void **ptr)
{
    if (((sipVoidPtrObject *)self)->rw)
        return sipVoidPtr_getbuffer(self, seg, ptr);

    PyErr_SetString(PyExc_TypeError, "the sip.voidptr is not writeable");
    return -1;
}
#endif


#if PY_MAJOR_VERSION < 3
/*
 * The segment count implementation for Python v2.
 */
static SIP_SSIZE_T sipVoidPtr_getsegcount(PyObject *self, SIP_SSIZE_T *lenp)
{
    SIP_SSIZE_T segs, len;

    len = ((sipVoidPtrObject *)self)->size;
    segs = (len < 0 ? 0 : 1);

    if (lenp != NULL)
        *lenp = len;

    return segs;
}
#endif


/*
 * Implement int() for the type.
 */
static PyObject *sipVoidPtr_int(sipVoidPtrObject *v)
{
    return PyLong_FromVoidPtr(v->voidptr);
}


#if PY_MAJOR_VERSION < 3
/*
 * Implement hex() for the type.
 */
static PyObject *sipVoidPtr_hex(sipVoidPtrObject *v)
{
    char buf[2 + 16 + 1];

    PyOS_snprintf(buf, sizeof (buf), "0x%.*lx", (int)(sizeof (void *) * 2),
            (unsigned long)v->voidptr);

    return PyString_FromString(buf);
}
#endif


#if defined(SIP_USE_PYCAPSULE)
/*
 * Implement ascapsule() for the type.
 */
static PyObject *sipVoidPtr_ascapsule(sipVoidPtrObject *v, PyObject *arg)
{
    return PyCapsule_New(v->voidptr, NULL, NULL);
}
#endif


#if defined(SIP_SUPPORT_PYCOBJECT)
/*
 * Implement ascobject() for the type.
 */
static PyObject *sipVoidPtr_ascobject(sipVoidPtrObject *v, PyObject *arg)
{
    return PyCObject_FromVoidPtr(v->voidptr, NULL);
}
#endif


/*
 * Implement asstring() for the type.
 */
static PyObject *sipVoidPtr_asstring(sipVoidPtrObject *v, PyObject *args,
        PyObject *kw)
{
    static char *kwlist[] = {"size", NULL};

    SIP_SSIZE_T size = -1;

    if (!PyArg_ParseTupleAndKeywords(args, kw,
#if PY_VERSION_HEX >= 0x02050000
            "|n:asstring",
#else
            "|i:asstring",
#endif
            kwlist, &size))
        return NULL;

    /* Use the current size if one wasn't explicitly given. */
    if (size < 0)
        size = v->size;

    if (size < 0)
    {
        PyErr_SetString(PyExc_ValueError,
                "a size must be given or the sip.voidptr must have a size");
        return NULL;
    }

    return SIPBytes_FromStringAndSize(v->voidptr, size);
}


/*
 * Implement getsize() for the type.
 */
static PyObject *sipVoidPtr_getsize(sipVoidPtrObject *v, PyObject *arg)
{
#if PY_MAJOR_VERSION >= 3
    return PyLong_FromSsize_t(v->size);
#elif PY_VERSION_HEX >= 0x02050000
    return PyInt_FromSsize_t(v->size);
#else
    return PyInt_FromLong(v->size);
#endif
}


/*
 * Implement setsize() for the type.
 */
static PyObject *sipVoidPtr_setsize(sipVoidPtrObject *v, PyObject *arg)
{
    SIP_SSIZE_T size;

#if PY_MAJOR_VERSION >= 3
    size = PyLong_AsSsize_t(arg);
#elif PY_VERSION_HEX >= 0x02050000
    size = PyInt_AsSsize_t(arg);
#else
    size = (int)PyInt_AsLong(arg);
#endif

    if (PyErr_Occurred())
        return NULL;

    v->size = size;

    Py_INCREF(Py_None);
    return Py_None;
}


/*
 * Implement getwriteable() for the type.
 */
static PyObject *sipVoidPtr_getwriteable(sipVoidPtrObject *v, PyObject *arg)
{
    return PyBool_FromLong(v->rw);
}


/*
 * Implement setwriteable() for the type.
 */
static PyObject *sipVoidPtr_setwriteable(sipVoidPtrObject *v, PyObject *arg)
{
    int rw;

    rw = (int)SIPLong_AsLong(arg);

    if (PyErr_Occurred())
        return NULL;

    v->rw = rw;

    Py_INCREF(Py_None);
    return Py_None;
}


/* The methods data structure. */
static PyMethodDef sipVoidPtr_Methods[] = {
#if defined(SIP_USE_PYCAPSULE)
    {"ascapsule", (PyCFunction)sipVoidPtr_ascapsule, METH_NOARGS, NULL},
#endif
#if defined(SIP_SUPPORT_PYCOBJECT)
    {"ascobject", (PyCFunction)sipVoidPtr_ascobject, METH_NOARGS, NULL},
#endif
    {"asstring", (PyCFunction)sipVoidPtr_asstring, METH_KEYWORDS, NULL},
    {"getsize", (PyCFunction)sipVoidPtr_getsize, METH_NOARGS, NULL},
    {"setsize", (PyCFunction)sipVoidPtr_setsize, METH_O, NULL},
    {"getwriteable", (PyCFunction)sipVoidPtr_getwriteable, METH_NOARGS, NULL},
    {"setwriteable", (PyCFunction)sipVoidPtr_setwriteable, METH_O, NULL},
    {NULL}
};


/* The number methods data structure. */
static PyNumberMethods sipVoidPtr_NumberMethods = {
    0,                      /* nb_add */
    0,                      /* nb_subtract */
    0,                      /* nb_multiply */
#if PY_MAJOR_VERSION < 3
    0,                      /* nb_divide */
#endif
    0,                      /* nb_remainder */
    0,                      /* nb_divmod */
    0,                      /* nb_power */
    0,                      /* nb_negative */
    0,                      /* nb_positive */
    0,                      /* nb_absolute */
    0,                      /* nb_bool (Python v3), nb_nonzero (Python v2) */
    0,                      /* nb_invert */
    0,                      /* nb_lshift */
    0,                      /* nb_rshift */
    0,                      /* nb_and */
    0,                      /* nb_xor */
    0,                      /* nb_or */
#if PY_MAJOR_VERSION < 3
    0,                      /* nb_coerce */
#endif
    (unaryfunc)sipVoidPtr_int,  /* nb_int */
    0,                      /* nb_reserved (Python v3), nb_long (Python v2) */
    0,                      /* nb_float */
#if PY_MAJOR_VERSION < 3
    0,                      /* nb_oct */
    (unaryfunc)sipVoidPtr_hex,  /* nb_hex */
#endif
    0,                      /* nb_inplace_add */
    0,                      /* nb_inplace_subtract */
    0,                      /* nb_inplace_multiply */
#if PY_MAJOR_VERSION < 3
    0,                      /* nb_inplace_divide */
#endif
    0,                      /* nb_inplace_remainder */
    0,                      /* nb_inplace_power */
    0,                      /* nb_inplace_lshift */
    0,                      /* nb_inplace_rshift */
    0,                      /* nb_inplace_and */
    0,                      /* nb_inplace_xor */
    0,                      /* nb_inplace_or */
    0,                      /* nb_floor_divide */
    0,                      /* nb_true_divide */
    0,                      /* nb_inplace_floor_divide */
    0,                      /* nb_inplace_true_divide */
#if PY_VERSION_HEX >= 0x02050000
    0                       /* nb_index */
#endif
};


/* The buffer methods data structure. */
static PyBufferProcs sipVoidPtr_BufferProcs = {
    sipVoidPtr_getbuffer,
#if PY_MAJOR_VERSION >= 3
    NULL,
#else
    sipVoidPtr_getwritebuffer,
    sipVoidPtr_getsegcount,
#if PY_VERSION_HEX >= 0x02050000
    (charbufferproc)sipVoidPtr_getbuffer
#else
    (getcharbufferproc)sipVoidPtr_getbuffer
#endif
#endif
};


/* The type data structure. */
PyTypeObject sipVoidPtr_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "sip.voidptr",          /* tp_name */
    sizeof (sipVoidPtrObject),  /* tp_basicsize */
    0,                      /* tp_itemsize */
    0,                      /* tp_dealloc */
    0,                      /* tp_print */
    0,                      /* tp_getattr */
    0,                      /* tp_setattr */
    0,                      /* tp_reserved (Python v3), tp_compare (Python v2) */
    0,                      /* tp_repr */
    &sipVoidPtr_NumberMethods,  /* tp_as_number */
    0,                      /* tp_as_sequence */
    0,                      /* tp_as_mapping */
    0,                      /* tp_hash */
    0,                      /* tp_call */
    0,                      /* tp_str */
    0,                      /* tp_getattro */
    0,                      /* tp_setattro */
    &sipVoidPtr_BufferProcs,    /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,   /* tp_flags */
    0,                      /* tp_doc */
    0,                      /* tp_traverse */
    0,                      /* tp_clear */
    0,                      /* tp_richcompare */
    0,                      /* tp_weaklistoffset */
    0,                      /* tp_iter */
    0,                      /* tp_iternext */
    sipVoidPtr_Methods,     /* tp_methods */
    0,                      /* tp_members */
    0,                      /* tp_getset */
    0,                      /* tp_base */
    0,                      /* tp_dict */
    0,                      /* tp_descr_get */
    0,                      /* tp_descr_set */
    0,                      /* tp_dictoffset */
    0,                      /* tp_init */
    0,                      /* tp_alloc */
    sipVoidPtr_new,         /* tp_new */
};


/*
 * A convenience function to convert a C/C++ void pointer from a Python object.
 */
void *sip_api_convert_to_void_ptr(PyObject *obj)
{
    if (obj == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "sip.voidptr is NULL");
        return NULL;
    }

    if (obj == Py_None)
        return NULL;

    if (PyObject_TypeCheck(obj, &sipVoidPtr_Type))
        return ((sipVoidPtrObject *)obj)->voidptr;

#if defined(SIP_USE_PYCAPSULE)
    if (PyCapsule_CheckExact(obj))
        return PyCapsule_GetPointer(obj, NULL);
#endif

#if defined(SIP_SUPPORT_PYCOBJECT)
    if (PyCObject_Check(obj))
        return PyCObject_AsVoidPtr(obj);
#endif

#if PY_MAJOR_VERSION >= 3
    return PyLong_AsVoidPtr(obj);
#else
    return (void *)PyInt_AsLong(obj);
#endif
}


/*
 * Convert a C/C++ void pointer to a sip.voidptr object.
 */
PyObject *sip_api_convert_from_void_ptr(void *val)
{
    return make_voidptr(val, -1, TRUE);
}


/*
 * Convert a C/C++ void pointer to a sip.voidptr object.
 */
PyObject *sip_api_convert_from_const_void_ptr(const void *val)
{
    return make_voidptr((void *)val, -1, FALSE);
}


/*
 * Convert a sized C/C++ void pointer to a sip.voidptr object.
 */
PyObject *sip_api_convert_from_void_ptr_and_size(void *val, SIP_SSIZE_T size)
{
    return make_voidptr(val, size, TRUE);
}


/*
 * Convert a sized C/C++ const void pointer to a sip.voidptr object.
 */
PyObject *sip_api_convert_from_const_void_ptr_and_size(const void *val,
        SIP_SSIZE_T size)
{
    return make_voidptr((void *)val, size, FALSE);
}


/*
 * Do the work of converting a void pointer.
 */
static PyObject *make_voidptr(void *voidptr, SIP_SSIZE_T size, int rw)
{
    sipVoidPtrObject *self;

    if (voidptr == NULL)
    {
        Py_INCREF(Py_None);
        return Py_None;
    }

    if ((self = PyObject_NEW(sipVoidPtrObject, &sipVoidPtr_Type)) == NULL)
        return NULL;

    self->voidptr = voidptr;
    self->size = size;
    self->rw = rw;

    return (PyObject *)self;
}


/*
 * Convert a Python object to the values needed to create a voidptr.
 */
static int vp_convertor(PyObject *arg, struct vp_values *vp)
{
    void *ptr;
    SIP_SSIZE_T size = -1;
    int rw = TRUE;

    if (arg == Py_None)
        ptr = NULL;
#if defined(SIP_USE_PYCAPSULE)
    else if (PyCapsule_CheckExact(arg))
        ptr = PyCapsule_GetPointer(arg, NULL);
#endif
#if defined(SIP_SUPPORT_PYCOBJECT)
    else if (PyCObject_Check(arg))
        ptr = PyCObject_AsVoidPtr(arg);
#endif
    else if (PyObject_TypeCheck(arg, &sipVoidPtr_Type))
    {
        ptr = ((sipVoidPtrObject *)arg)->voidptr;
        size = ((sipVoidPtrObject *)arg)->size;
        rw = ((sipVoidPtrObject *)arg)->rw;
    }
    else
    {
#if PY_MAJOR_VERSION >= 3
        ptr = PyLong_AsVoidPtr(arg);
#else
        ptr = (void *)PyInt_AsLong(arg);
#endif

        if (PyErr_Occurred())
        {
#if PY_VERSION_HEX >= 0x03010000
            PyErr_SetString(PyExc_TypeError, "a single integer, CObject, None or another voidptr is required");
#else
            PyErr_SetString(PyExc_TypeError, "a single integer, Capsule, CObject, None or another voidptr is required");
#endif
            return 0;
        }
    }

    vp->voidptr = ptr;
    vp->size = size;
    vp->rw = rw;

    return 1;
}
