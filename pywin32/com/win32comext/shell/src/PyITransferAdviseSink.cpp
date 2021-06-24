// This file implements the ITransferAdviseSink Interface and Gateway for Python.
// Generated by makegw.py

#include "shell_pch.h"
#include "PyITransferAdviseSink.h"

// Borrowed from propsys module, need to move somewhere common
BOOL PyWinObject_AsPROPERTYKEY(PyObject *obkey, PROPERTYKEY *pkey)
{
    return PyArg_ParseTuple(obkey, "O&k:PROPERTYKEY", PyWinObject_AsIID, &pkey->fmtid, &pkey->pid);
}

PyObject *PyWinObject_FromPROPERTYKEY(REFPROPERTYKEY key)
{
    return Py_BuildValue("Nk", PyWinObject_FromIID(key.fmtid), key.pid);
}

// @doc - This file contains autoduck documentation
// ---------------------------------------------------
//
// Interface Implementation

PyITransferAdviseSink::PyITransferAdviseSink(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyITransferAdviseSink::~PyITransferAdviseSink() {}

/* static */ ITransferAdviseSink *PyITransferAdviseSink::GetI(PyObject *self)
{
    return (ITransferAdviseSink *)PyIUnknown::GetI(self);
}

// @pymethod |PyITransferAdviseSink|UpdateProgress|Gives an estimate of amount of work completed
PyObject *PyITransferAdviseSink::UpdateProgress(PyObject *self, PyObject *args)
{
    ITransferAdviseSink *pITAS = GetI(self);
    if (pITAS == NULL)
        return NULL;
    // @pyparm int|SizeCurrent||Bytes transferred so far
    // @pyparm int|SizeTotal||Total number of bytes
    // @pyparm int|FilesCurrent||Number of files processed already
    // @pyparm int|FilesTotal||Total number of files
    // @pyparm int|FoldersCurrent||Number of folders processed already
    // @pyparm int|FoldersTotal||Total number of folder
    ULONGLONG ullSizeCurrent, ullSizeTotal;
    int nFilesCurrent;
    int nFilesTotal;
    int nFoldersCurrent;
    int nFoldersTotal;
    if (!PyArg_ParseTuple(args, "KKiiii:UpdateProgress", &ullSizeCurrent, &ullSizeTotal, &nFilesCurrent, &nFilesTotal,
                          &nFoldersCurrent, &nFoldersTotal))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr =
        pITAS->UpdateProgress(ullSizeCurrent, ullSizeTotal, nFilesCurrent, nFilesTotal, nFoldersCurrent, nFoldersTotal);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pITAS, IID_ITransferAdviseSink);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyITransferAdviseSink|UpdateTransferState|Notifies client of current operation state
PyObject *PyITransferAdviseSink::UpdateTransferState(PyObject *self, PyObject *args)
{
    ITransferAdviseSink *pITAS = GetI(self);
    if (pITAS == NULL)
        return NULL;
    TRANSFER_ADVISE_STATE ts;
    // @pyparm int|State||A TRANSFER_ADVISE_STATE value (shellcon.TS_*)
    if (!PyArg_ParseTuple(args, "i:UpdateTransferState", &ts))
        return NULL;

    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pITAS->UpdateTransferState(ts);
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pITAS, IID_ITransferAdviseSink);
    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod int|PyITransferAdviseSink|ConfirmOverwrite|Asks user for permission to overwrite an existing item
PyObject *PyITransferAdviseSink::ConfirmOverwrite(PyObject *self, PyObject *args)
{
    ITransferAdviseSink *pITAS = GetI(self);
    if (pITAS == NULL)
        return NULL;
    // @pyparm <o PyIShellItem>|Source||The item that will replace existing item
    // @pyparm <o PyIShellItem>|DestParent||Folder into which item will be placed
    // @pyparm str|Name||New name for item, or None if item is to keep original name
    PyObject *obpsiSource;
    PyObject *obpsiDestParent;
    PyObject *obName;
    IShellItem *psiSource;
    IShellItem *psiDestParent;
    TmpWCHAR Name;
    if (!PyArg_ParseTuple(args, "OOO:ConfirmOverwrite", &obpsiSource, &obpsiDestParent, &obName))
        return NULL;
    if (!PyWinObject_AsWCHAR(obName, &Name, TRUE))
        return NULL;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obpsiSource, IID_IShellItem, (void **)&psiSource, FALSE))
        return NULL;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obpsiDestParent, IID_IShellItem, (void **)&psiDestParent, FALSE)) {
        PYCOM_RELEASE(psiSource);
        return NULL;
    }

    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pITAS->ConfirmOverwrite(psiSource, psiDestParent, Name);
    psiSource->Release();
    psiDestParent->Release();
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pITAS, IID_ITransferAdviseSink);
    return PyLong_FromLong(hr);
}

// @pymethod int|PyITransferAdviseSink|ConfirmEncryptionLoss|Notifies user when an item can't be encrypted at
// destination
PyObject *PyITransferAdviseSink::ConfirmEncryptionLoss(PyObject *self, PyObject *args)
{
    ITransferAdviseSink *pITAS = GetI(self);
    if (pITAS == NULL)
        return NULL;
    // @pyparm <o PyIShellItem>|Source||Item that failed to be encrypted
    PyObject *obpsiSource;
    IShellItem *psiSource;
    if (!PyArg_ParseTuple(args, "O:ConfirmEncryptionLoss", &obpsiSource))
        return NULL;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obpsiSource, IID_IShellItem, (void **)&psiSource, FALSE))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pITAS->ConfirmEncryptionLoss(psiSource);
    psiSource->Release();
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pITAS, IID_ITransferAdviseSink);
    return PyLong_FromLong(hr);
}

// @pymethod (int,str)|PyITransferAdviseSink|FileFailure|Notifies user of failure, and queries how to proceed
// @rdesc Returns the HRESULT and new file name if renaming resolved the failure
PyObject *PyITransferAdviseSink::FileFailure(PyObject *self, PyObject *args)
{
    ITransferAdviseSink *pITAS = GetI(self);
    if (pITAS == NULL)
        return NULL;
    // @pyparm <o PyIShellItem>|Item||The shell item that caused the failure
    // @pyparm str|ItemName||Name of item if different than above, can be None
    // @pyparm int|Error||HRESULT error code from operation
    PyObject *obItem, *obItemName;
    IShellItem *pItem;
    TmpWCHAR ItemName;
    HRESULT hrError;
    WCHAR Rename[MAX_PATH + 1] = {0};
    ULONG cchRename = MAX_PATH + 1;
    if (!PyArg_ParseTuple(args, "OOl:FileFailure", &obItem, &obItemName, &hrError))
        return NULL;
    if (!PyWinObject_AsWCHAR(obItemName, &ItemName, TRUE))
        return NULL;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obItem, IID_IShellItem, (void **)&pItem, FALSE))
        return NULL;

    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pITAS->FileFailure(pItem, ItemName, hrError, Rename, cchRename);
    pItem->Release();
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pITAS, IID_ITransferAdviseSink);
    return Py_BuildValue("lN", hr, PyWinObject_FromWCHAR(Rename));
}

// @pymethod int|PyITransferAdviseSink|SubStreamFailure|Notifies user of failure on a substream, and queries how to
// proceed
// @rdesc Returns COPYENGINE_S_* if operation is to continue, or COPYENGINE_E_* HRESULT if cancelled
PyObject *PyITransferAdviseSink::SubStreamFailure(PyObject *self, PyObject *args)
{
    ITransferAdviseSink *pITAS = GetI(self);
    if (pITAS == NULL)
        return NULL;
    // @pyparm <o PyIShellItem>|Item||The item whose stream couldn't be created
    // @pyparm str|StreamName||Name of the failed stream
    // @pyparm int|Error||HRESULT failure code from operation
    PyObject *obpsi;
    PyObject *obStreamName;
    IShellItem *psi;
    TmpWCHAR StreamName;
    HRESULT hrError;
    if (!PyArg_ParseTuple(args, "OOl:SubStreamFailure", &obpsi, &obStreamName, &hrError))
        return NULL;
    if (!PyWinObject_AsWCHAR(obStreamName, &StreamName, FALSE))
        return NULL;
    if (!PyCom_InterfaceFromPyInstanceOrObject(obpsi, IID_IShellItem, (void **)&psi, FALSE))
        return NULL;
    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pITAS->SubStreamFailure(psi, StreamName, hrError);
    psi->Release();
    PY_INTERFACE_POSTCALL;

    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pITAS, IID_ITransferAdviseSink);
    return PyLong_FromLong(hr);
}

// @pymethod int|PyITransferAdviseSink|PropertyFailure|Notifies user of failure to set an item's properties
// @rdesc Returns COPYENGINE_S_* to indicate that the failure was handled, or
//	COPYENGINE_E_USERCANCELLED to cancel pending operations
PyObject *PyITransferAdviseSink::PropertyFailure(PyObject *self, PyObject *args)
{
    ITransferAdviseSink *pITAS = GetI(self);
    if (pITAS == NULL)
        return NULL;
    // @pyparm <o PyIShellItem>|Item||The item whose property could not be set
    PROPERTYKEY key, *pkey = NULL;
    PyObject *obkey;
    // @pyparm <o PyPROPERTYKEY>|key||Identifies the property that caused the error, or None if all properties failed
    // @pyparm int|Error||HRESULT error code returned by the operation
    PyObject *obitem;
    IShellItem *pitem;
    HRESULT hrError;
    if (!PyArg_ParseTuple(args, "OOl:PropertyFailure", &obitem, &obkey, &hrError))
        return NULL;
    if (obkey != Py_None) {
        if (!PyWinObject_AsPROPERTYKEY(obkey, &key))
            return NULL;
        pkey = &key;
    }
    if (!PyCom_InterfaceFromPyInstanceOrObject(obitem, IID_IShellItem, (void **)&pitem, FALSE))
        return NULL;

    HRESULT hr;
    PY_INTERFACE_PRECALL;
    hr = pITAS->PropertyFailure(pitem, pkey, hrError);
    pitem->Release();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr, pITAS, IID_ITransferAdviseSink);
    return PyLong_FromLong(hr);
}

// @object PyITransferAdviseSink|Interface that receives notifications from <o PyITransferSource> or <o
// PyITransferDestination>
static struct PyMethodDef PyITransferAdviseSink_methods[] = {
    {"UpdateProgress", PyITransferAdviseSink::UpdateProgress,
     1},  // @pymeth UpdateProgress|Gives an estimate of amount of work completed
    {"UpdateTransferState", PyITransferAdviseSink::UpdateTransferState,
     1},  // @pymeth UpdateTransferState|Notifies client of current operation state
    {"ConfirmOverwrite", PyITransferAdviseSink::ConfirmOverwrite,
     1},  // @pymeth ConfirmOverwrite|Asks user for permission to overwrite an existing item
    {"ConfirmEncryptionLoss", PyITransferAdviseSink::ConfirmEncryptionLoss,
     1},  // @pymeth ConfirmEncryptionLoss|Notifies user when an item can't be encrypted at destination
    {"FileFailure", PyITransferAdviseSink::FileFailure,
     1},  // @pymeth FileFailure|Notifies user of failure, and queries how to proceed
    {"SubStreamFailure", PyITransferAdviseSink::SubStreamFailure,
     1},  // @pymeth SubStreamFailure|Notifies user of failure on a substream, and queries how to proceed
    {"PropertyFailure", PyITransferAdviseSink::PropertyFailure,
     1},  // @pymeth PropertyFailure|Notifies user of failure to set an item's properties
    {NULL}};

PyComTypeObject PyITransferAdviseSink::type("PyITransferAdviseSink", &PyIUnknown::type, sizeof(PyITransferAdviseSink),
                                            PyITransferAdviseSink_methods, GET_PYCOM_CTOR(PyITransferAdviseSink));
// ---------------------------------------------------
//
// Gateway Implementation
STDMETHODIMP PyGTransferAdviseSink::UpdateProgress(
    /* [in] */ ULONGLONG ullSizeCurrent,
    /* [in] */ ULONGLONG ullSizeTotal,
    /* [in] */ int nFilesCurrent,
    /* [in] */ int nFilesTotal,
    /* [in] */ int nFoldersCurrent,
    /* [in] */ int nFoldersTotal)
{
    PY_GATEWAY_METHOD;
    HRESULT hr = InvokeViaPolicy("UpdateProgress", NULL, "KKiiii", ullSizeCurrent, ullSizeTotal, nFilesCurrent,
                                 nFilesTotal, nFoldersCurrent, nFoldersTotal);
    return hr;
}

STDMETHODIMP PyGTransferAdviseSink::UpdateTransferState(
    /* [in] */ TRANSFER_ADVISE_STATE ts)
{
    PY_GATEWAY_METHOD;
    HRESULT hr = InvokeViaPolicy("UpdateTransferState", NULL, "i", ts);
    return hr;
}

STDMETHODIMP PyGTransferAdviseSink::ConfirmOverwrite(
    /* [in] */ IShellItem *psiSource,
    /* [in] */ IShellItem *psiDestParent,
    /* [in] */ LPCWSTR pszName)
{
    PY_GATEWAY_METHOD;
    PyObject *obpsiSource;
    PyObject *obpsiDestParent;
    PyObject *obpszName;
    obpsiSource = PyCom_PyObjectFromIUnknown(psiSource, IID_IShellItem, TRUE);
    obpsiDestParent = PyCom_PyObjectFromIUnknown(psiDestParent, IID_IShellItem, TRUE);
    obpszName = PyWinObject_FromWCHAR(pszName);
    HRESULT hr = InvokeViaPolicy("ConfirmOverwrite", NULL, "OOO", obpsiSource, obpsiDestParent, obpszName);
    Py_XDECREF(obpsiSource);
    Py_XDECREF(obpsiDestParent);
    Py_XDECREF(obpszName);
    return hr;
}

STDMETHODIMP PyGTransferAdviseSink::ConfirmEncryptionLoss(
    /* [in] */ IShellItem *psiSource)
{
    PY_GATEWAY_METHOD;
    PyObject *obpsiSource, *result;
    obpsiSource = PyCom_PyObjectFromIUnknown(psiSource, IID_IShellItem, TRUE);
    HRESULT hr = InvokeViaPolicy("ConfirmEncryptionLoss", &result, "O", obpsiSource);
    Py_XDECREF(obpsiSource);
    if (FAILED(hr))
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("ConfirmEncryptionLoss");
    else {
        hr = PyLong_AsLong(result);
        if (hr == -1 && PyErr_Occurred())
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("ConfirmEncryptionLoss");
    }
    return hr;
}

STDMETHODIMP PyGTransferAdviseSink::FileFailure(
    /* [in] */ IShellItem *psi,
    /* [in] */ LPCWSTR pszItem,
    /* [in] */ HRESULT hrError,
    /* [out] */ LPWSTR pszRename,
    /* [in] */ ULONG cchRename)
{
    PY_GATEWAY_METHOD;
    PyObject *obpsi;
    PyObject *obpszItem;
    obpsi = PyCom_PyObjectFromIUnknown(psi, IID_IShellItem, TRUE);
    obpszItem = PyWinObject_FromWCHAR(pszItem);
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("FileFailure", &result, "OOlk", obpsi, obpszItem, hrError, cchRename);
    Py_XDECREF(obpsi);
    Py_XDECREF(obpszItem);
    if (FAILED(hr))
        return hr;
    // Process the Python results, and convert back to the real params
    PyObject *obpszRename;
    if (!PyArg_Parse(result, "lO", hr, &obpszRename))
        hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("FileFailure");
    else if (pszRename) {
        ZeroMemory(pszRename, cchRename * sizeof(WCHAR));
        TmpWCHAR new_fname;
        DWORD new_fname_len;
        if (!PyWinObject_AsWCHAR(obpszRename, &new_fname, TRUE, &new_fname_len))
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("FileFailure");
        else if (new_fname) {
            if (new_fname_len + 1 > cchRename)
                hr = HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
            else
                wcsncpy(pszRename, new_fname, new_fname_len);
        }
    }
    Py_DECREF(result);
    return hr;
}

STDMETHODIMP PyGTransferAdviseSink::SubStreamFailure(
    /* [in] */ IShellItem *psi,
    /* [in] */ LPCWSTR pszStreamName,
    /* [in] */ HRESULT hrError)
{
    PY_GATEWAY_METHOD;
    PyObject *obpsi;
    PyObject *obpszStreamName;
    PyObject *result;
    obpsi = PyCom_PyObjectFromIUnknown(psi, IID_IShellItem, TRUE);
    obpszStreamName = PyWinObject_FromWCHAR(pszStreamName);
    HRESULT hr = InvokeViaPolicy("SubStreamFailure", &result, "OOl", obpsi, obpszStreamName, hrError);
    Py_XDECREF(obpsi);
    Py_XDECREF(obpszStreamName);
    if
        FAILED(hr)
    hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("SubStreamFailure");
    else
    {
        hr = PyLong_AsLong(result);
        if (hr == -1 && PyErr_Occurred())
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("SubStreamFailure");
    }
    return hr;
}

STDMETHODIMP PyGTransferAdviseSink::PropertyFailure(
    /* [in] */ IShellItem *psi,
    /* [in] */ const PROPERTYKEY *pkey,
    /* [in] */ HRESULT hrError)
{
    PY_GATEWAY_METHOD;
    PyObject *obkey;
    // Property key can be NULL to signify total failure of all properties, eg no property handler
    if (pkey)
        obkey = PyWinObject_FromPROPERTYKEY(*pkey);
    else {
        Py_INCREF(Py_None);
        obkey = Py_None;
    }
    if (obkey == NULL)
        return MAKE_PYCOM_GATEWAY_FAILURE_CODE("PropertyFailure");
    PyObject *obpsi, *result;
    obpsi = PyCom_PyObjectFromIUnknown(psi, IID_IShellItem, TRUE);
    HRESULT hr = InvokeViaPolicy("PropertyFailure", &result, "OOl", obpsi, obkey, hrError);
    Py_XDECREF(obpsi);
    Py_DECREF(obkey);
    if
        FAILED(hr)
    hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("PropertyFailure");
    else
    {
        hr = PyLong_AsLong(result);
        if (hr == -1 && PyErr_Occurred())
            hr = MAKE_PYCOM_GATEWAY_FAILURE_CODE("PropertyFailure");
    }

    return hr;
}