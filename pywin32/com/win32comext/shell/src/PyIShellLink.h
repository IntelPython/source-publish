// This file declares the IShellLink Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyIShellLink : public PyIUnknown {
   public:
    MAKE_PYCOM_CTOR(PyIShellLink);
    static IShellLink *GetI(PyObject *self);
    static PyComTypeObject type;

    // The Python methods
    static PyObject *GetPath(PyObject *self, PyObject *args);
    static PyObject *GetIDList(PyObject *self, PyObject *args);
    static PyObject *SetIDList(PyObject *self, PyObject *args);
    static PyObject *GetDescription(PyObject *self, PyObject *args);
    static PyObject *SetDescription(PyObject *self, PyObject *args);
    static PyObject *GetWorkingDirectory(PyObject *self, PyObject *args);
    static PyObject *SetWorkingDirectory(PyObject *self, PyObject *args);
    static PyObject *GetArguments(PyObject *self, PyObject *args);
    static PyObject *SetArguments(PyObject *self, PyObject *args);
    static PyObject *GetHotkey(PyObject *self, PyObject *args);
    static PyObject *SetHotkey(PyObject *self, PyObject *args);
    static PyObject *GetShowCmd(PyObject *self, PyObject *args);
    static PyObject *SetShowCmd(PyObject *self, PyObject *args);
    static PyObject *GetIconLocation(PyObject *self, PyObject *args);
    static PyObject *SetIconLocation(PyObject *self, PyObject *args);
    static PyObject *SetRelativePath(PyObject *self, PyObject *args);
    static PyObject *Resolve(PyObject *self, PyObject *args);
    static PyObject *SetPath(PyObject *self, PyObject *args);

   protected:
    PyIShellLink(IUnknown *pdisp);
    ~PyIShellLink();
};
// ---------------------------------------------------
//
// Gateway Declaration
/***
class PyGShellLink : public PyGatewayBase, public IShellLink
{
protected:
    PyGShellLink(PyObject *instance) : PyGatewayBase(instance) { ; }
    PYGATEWAY_MAKE_SUPPORT(PyGShellLink, IShellLink, IID_IShellLink, PyGatewayBase)



    // IShellLink
    STDMETHOD(GetPath)(
        LPSTR pszFile,
        int cchMaxPath,
        WIN32_FIND_DATAA * pfd,
        DWORD fFlags);

    STDMETHOD(GetIDList)(
        LPITEMIDLIST * ppidl);

    STDMETHOD(SetIDList)(
        LPCITEMIDLIST pidl);

    STDMETHOD(GetDescription)(
        LPSTR pszName,
        int cchMaxName);

    STDMETHOD(SetDescription)(
        LPCSTR pszName);

    STDMETHOD(GetWorkingDirectory)(
        LPSTR pszDir,
        int cchMaxPath);

    STDMETHOD(SetWorkingDirectory)(
        LPCSTR pszDir);

    STDMETHOD(GetArguments)(
        LPSTR pszArgs,
        int cchMaxPath);

    STDMETHOD(SetArguments)(
        LPCSTR pszArgs);

    STDMETHOD(GetHotkey)(
        WORD * pwHotkey);

    STDMETHOD(SetHotkey)(
        WORD wHotkey);

    STDMETHOD(GetShowCmd)(
        int * piShowCmd);

    STDMETHOD(SetShowCmd)(
        int iShowCmd);

    STDMETHOD(GetIconLocation)(
        LPSTR pszIconPath,
        int cchIconPath,
        int * piIcon);

    STDMETHOD(SetIconLocation)(
        LPCSTR pszIconPath,
        int iIcon);

    STDMETHOD(SetRelativePath)(
        LPCSTR pszPathRel,
        DWORD dwReserved);

    STDMETHOD(Resolve)(
        HWND hwnd,
        DWORD fFlags);

    STDMETHOD(SetPath)(
        LPCSTR pszFile);

};
****/