// This file declares the ITask Interface for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration
#include "PyIScheduledWorkItem.h"

class PyITask : public PyIScheduledWorkItem {
   public:
    MAKE_PYCOM_CTOR(PyITask);
    static ITask *GetI(PyObject *self);
    static PyComTypeObject type;

    // The Python methods
    static PyObject *SetApplicationName(PyObject *self, PyObject *args);
    static PyObject *GetApplicationName(PyObject *self, PyObject *args);
    static PyObject *SetParameters(PyObject *self, PyObject *args);
    static PyObject *GetParameters(PyObject *self, PyObject *args);
    static PyObject *SetWorkingDirectory(PyObject *self, PyObject *args);
    static PyObject *GetWorkingDirectory(PyObject *self, PyObject *args);
    static PyObject *SetPriority(PyObject *self, PyObject *args);
    static PyObject *GetPriority(PyObject *self, PyObject *args);
    static PyObject *SetTaskFlags(PyObject *self, PyObject *args);
    static PyObject *GetTaskFlags(PyObject *self, PyObject *args);
    static PyObject *SetMaxRunTime(PyObject *self, PyObject *args);
    static PyObject *GetMaxRunTime(PyObject *self, PyObject *args);

   protected:
    PyITask(IUnknown *pdisp);
    ~PyITask();
};