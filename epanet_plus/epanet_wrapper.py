"""
This module contains a Python wrapper (incl. error handling) for EPANET and EPANET-MSX functions.
"""
import warnings
import numpy
import epanet
import Any 


class EpanetAPI():
    """
    Interface for EPANET and EPANET-MSX functions, incl. a proper error handling.

    Parameters
    ----------
    use_project : `bool`, optional
        If True, projects will be used when calling EPANET functions (default in EPANET >= 2.2).
        Note that this is incompatible with EPANET-MSX. Please set to False when using EPANET-MSX.

        The default is False.

    raise_on_error : `bool`, optional
        True if an exception should be raised in the case of an error/warning, False otherwise.

        The default is True.
    warn_on_error : `bool`, optional
        True if a warning should be generated in the case of an error/warning, False otherwise.

        The default is False.
    ignore_error_codes : `list[int]`, optional
        List of error codes that should be ignored -- i.e., no exception or warning
        will be generated.

        The default is an empty list.
    """
    def __init__(self, use_project: bool = False, raise_exception_on_error: bool = True,
                 warn_on_error: bool = False, ignore_error_codes: list[int] = []):
        if not isinstance(use_project, bool):
            raise TypeError("'use_project' must be an instance of 'bool' " +
                            f"but not of '{type(use_project)}'")
        if not isinstance(raise_exception_on_error, bool):
            raise TypeError("'raise_exception_on_error' must be an instance of 'bool' " +
                            f"but not of '{type(raise_exception_on_error)}'")
        if not isinstance(warn_on_error, bool):
            raise TypeError("'warn_on_error' must be an instance of 'bool' " +
                            f"but not of type '{type(warn_on_error)}'")
        if not isinstance(ignore_error_codes, list):
            raise TypeError("'ignore_error_codes' must be an instance of 'list[int]' " +
                            f"but not of '{type(ignore_error_codes)}'")
        else:
            if any(not isinstance(item, int) for item in ignore_error_codes):
                raise TypeError("All items in 'ignore_error_codes' must be of type 'int'")

        if raise_exception_on_error is True and warn_on_error is True:
            raise ValueError("'raise_exception_on_error' and 'warn_on_error' can not be both True")

        self._use_project = use_project
        self._ph = None
        self._raise_on_error = raise_exception_on_error
        self._warn_on_error = warn_on_error
        self._ignore_error_codes = ignore_error_codes
        self._last_error_code = 0
        self._last_error_desc = None

    def set_error_handling(self, raise_exception_on_error: bool, warn_on_error: bool,
                           ignore_error_codes: list[int] = []) -> None:
        """
        Specifies the behavior in the case of an error/warning --
        i.e. should an exception or warning be raised or not?

        Parameters
        ----------
        raise_exception_on_error : `bool`
            True if an exception should be raised, False otherwise.
        warn_on_error : `bool`
            True if a warning should be generated, False otherwise.
        ignore_error_codes : `list[int]`
            List of error codes that should be ignored -- i.e., no exception or
            warning will be generated.
        """
        self._raise_on_error = raise_exception_on_error
        self._warn_on_error = warn_on_error
        self._ignore_error_codes = ignore_error_codes

    def get_last_error_desc(self) -> str:
        """
        Returns the description of the last EPANET-(MSX) error/warning (if any).

        Returns
        -------
        `str`
            Description of the last error/warning. None, if there was no error/warning.
        """
        return self._last_error_desc

    def get_last_error_code(self) -> int:
        """
        Returns the code of the last EPANET-(MSX) error/warnning (if any).

        Refer to the `EPANET documentation <http://wateranalytics.org/EPANET/group___warning_codes.html>`_
        for a list of all possible warning codes and their meanings.

        Returns
        -------
        `int`
            Code of the last error/warning. 0, if there was no error/warning.
        """
        return self._last_error_code

    def was_last_func_successful(self) -> bool:
        """
        Checks if the last EPANET call was successful or not.

        Parameters
        ----------
        `bool`
            True if the last EPANET call returned an error/warning, False otherwise.
        """
        return self._last_error_desc is None

    def _reset_error(self) -> None:
        self._last_error_code = 0
        self._last_error_desc = None

    def _process_result(self, ret: tuple, msx_call: bool = False) -> Any:
        ret_other = None
        if len(ret) == 1:
            errcode = ret[0]
        else:
            errcode, *ret_other = ret

        if errcode != 0:
            self._last_error_code = errcode
            if msx_call is False:
                self._last_error_desc = self.geterror(errcode)
            else:
                self._last_error_desc = self.MSXgeterror(errcode)

            if self._last_error_code not in self._ignore_error_codes:
                if self._warn_on_error:
                    warnings.warn(self._last_error_desc, RuntimeWarning)
                if self._raise_on_error:
                    raise RuntimeError(self._last_error_desc)

        if ret_other is not None and len(ret_other) == 1:
            return ret_other[0]
        else:
            return ret_other

    @property
    def use_project(self) -> bool:
        """
        Returns whether EPANET projects are used or not.

        Returns
        -------
        `bool`
            True, if EPANET projects are used, False otherwise.
        """
        return self._use_project

    @property
    def ph(self) -> int:
        """
        Returns a pointer (memory address) to the project structure.

        Returns
        -------
        `int`
            Pointer to project structure -- please do not change or access the memory location!
        """
        return self._ph

    def openfrombuffer(self, inpBuffer: str, inpFile: str, rptFile: str, outFile: str) -> int:
        """
        EN_openfrombuffer -- extension of EPANET and part of EPANET-PLUS

        Parameters
        ----------
        inpBuffer : `str`
        inpFile : `str`
        rptFile : `str`
        outFile : `str`

        Returns
        -------
        int 
            Error code returned by ENopenfrombuffer / EN_openfrombuffer.
            The underlying C function returns a tuple containing a single
            integer (the error code), which `_process_result` unwraps and
            returns as a plain int.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENopenfrombuffer(inpBuffer, inpFile, rptFile,
                                                                outFile))
        else:
            return self._process_result(epanet.EN_openfrombuffer(self._ph, inpBuffer, inpFile,
                                                                 rptFile, outFile))

    def createproject(self) -> int:
        """
        EN_createproject

        Returns
        -------
        int 
            The project handle created by EN_createproject.
            The underlying C function returns a tuple (errcode, handle),
            which `_process_result` unwraps and returns only the handle.
        """
        if self._use_project is False:
            raise ValueError("Can not create project because of use_project=False")
        else:
            self._ph = self._process_result(epanet.EN_createproject())

    def deleteproject(self) -> None:
        """
        EN_deleteproject

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Raises RuntimeError on failure.
        """
        if self._use_project is False:
            raise ValueError("Can not delete project because of use_project=False")
        else:
            if self._ph is not None:
                res = self._process_result(epanet.EN_deleteproject(self._ph))
                self._ph = None

                return res

    def init(self, rptFile: str, outFile: str, unitsType: int, headLossType: int) -> None:
        """
        EN_init

        Parameters
        ----------
        rptFile : `str`
        outFile : `str`
        unitsType : `int`
        headLossType : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENinit(rptFile, outFile, unitsType, headLossType))
        else:
            return self._process_result(epanet.EN_init(self._ph, rptFile, outFile, unitsType,
                                                       headLossType))

    def open(self, inpFile: str, rptFile: str, outFile: str)-> None:
        """
        EN_open

        Parameters
        ----------
        inpFile : `str`
        rptFile : `str`
        outFile : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENopen(inpFile, rptFile, outFile))
        else:
            return self._process_result(epanet.EN_open(self._ph, inpFile, rptFile, outFile))

    def openX(self, inpFile: str, rptFile: str, outFile: str) -> None:
        """
        EN_openX

        Parameters
        ----------
        inpFile : `str`
        rptFile : `str`
        outFile : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENopenX(inpFile, rptFile, outFile))
        else:
            return self._process_result(epanet.EN_openX(self._ph, inpFile, rptFile, outFile))

    def gettitle(self) -> list[str]:
        """
        EN_gettitle

        Returns
        -------
        list[str]
            A list containing the three title lines of the EPANET project. 
            The underlying C function returns a tuple (errcode, line1, line2, line3), 
            which `_process_result` unwraps and returns as a list of three strings.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgettitle())
        else:
            return self._process_result(epanet.EN_gettitle(self._ph))

    def settitle(self, line1: str, line2: str, line3: str) -> None:
        """
        EN_settitle

        Parameters
        ----------
        line1: str
        line2: str
        line3: str

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsettitle(line1, line2, line3))
        else:
            return self._process_result(epanet.EN_settitle(self._ph, line1, line2, line3))

    def getcomment(self, obj: int, index: int) -> str:
        """
        EN_getcomment

        Parameters
        ----------
        obj : `int`
        index : `int`

        Returns
        -------
        str
            The comment string associated with the given object and index. 
            The underlying C function returns a tuple (errcode, comment), 
            which `_process_results` unwraps and returns as a plain string. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcomment(obj, index))
        else:
            return self._process_result(epanet.EN_getcomment(self._ph, obj, index))

    def setcomment(self, obj: int, index: int, comment: str) -> None:
        """
        EN_setcomment

        Parameters
        ----------
        obj : `int`
        index : `int`
        comment : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetcomment(obj, index, comment))
        else:
            return self._process_result(epanet.EN_setcomment(self._ph, obj, index, comment))

    def getcount(self, obj: int) -> int:
        """
        EN_getcount

        Parameters
        ----------
        obj : `int`

        Returns
        -------
        int 
            The number of the objects of the given type. The underlying C 
            function returns a tuple (errcode, count), which `_process_result`
            unwraps and returns as a plain integer
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcount(obj))
        else:
            return self._process_result(epanet.EN_getcount(self._ph, obj))

    def saveinpfile(self, filename: str) -> None:
        """
        EN_saveinpfile

        Parameters
        ----------
        filename : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsaveinpfile(filename))
        else:
            return self._process_result(epanet.EN_saveinpfile(self._ph, filename))

    def close(self) -> None:
        """
        EN_close

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENclose())
        else:
            if self._ph is not None:
                return self._process_result(epanet.EN_close(self._ph))

    def solveH(self) -> None:
        """
        EN_solveH

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsolveH())
        else:
            return self._process_result(epanet.EN_solveH(self._ph))

    def usehydfile(self, filename: str) -> None:
        """
        EN_usehydfile

        Parameters
        ---------- 
        filename : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENusehydfile(filename))
        else:
            return self._process_result(epanet.EN_usehydfile(filename))

    def openH(self) -> None:
        """
        EN_openH

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENopenH())
        else:
            return self._process_result(epanet.EN_openH(self._ph))

    def initH(self, initFlag: int) -> None:
        """
        EN_initH

        Parameters
        ----------
        initFlag : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENinitH(initFlag))
        else:
            return self._process_result(epanet.EN_initH(self._ph, initFlag))

    def runH(self) -> int:
        """
        EN_runH

        Returns
        -------
        int 
            The current simulation time (in seconds). The underlying C 
            function returns a tuple (errcode, currentTime), which 
            `_process_result` unwraps and returns as a plain integer.  
        """
        if self._use_project is False:
            return self._process_result(epanet.ENrunH())
        else:
            return self._process_result(epanet.EN_runH(self._ph))

    def nextH(self) -> int:
        """
        EN_nextH

        Returns
        -------
        int
            The next hydraulic time step (in seconds). The underlying C 
            function returns a tuple (errcode, tStep), which `_process_result`
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENnextH())
        else:
            return self._process_result(epanet.EN_nextH(self._ph))

    def saveH(self) -> None:
        """
        EN_saveH

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsaveH())
        else:
            return self._process_result(epanet.EN_saveH(self._ph))

    def savehydfile(self, filename) -> None:
        """
        EN_savehydfile

        Parameters
        ----------
        filename : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsavehydfile(filename))
        else:
            return self._process_result(epanet.EN_savehydfile(self._ph, filename))

    def closeH(self) -> None:
        """
        EN_closeH

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENcloseH())
        else:
            return self._process_result(epanet.EN_closeH(self._ph))

    def solveQ(self) -> None:
        """
        EN_solveQ

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsolveQ())
        else:
            return self._process_result(epanet.EN_solveQ(self._ph))

    def openQ(self) -> None:
        """
        EN_openQ

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENopenQ())
        else:
            return self._process_result(epanet.EN_openQ(self._ph))

    def initQ(self, save_flag: int) -> None:
        """
        EN_initQ

        Parameters
        ----------
        save_flag : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENinitQ(save_flag))
        else:
            return self._process_result(epanet.EN_initQ(self._ph, save_flag))

    def runQ(self) -> int:
        """
        EN_runQ

        Returns
        -------
        int 
            The current water quality simulation time (in seconds). The 
            underlying C funtion returns a tuple (errcode, currentTime), 
            which `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENrunQ())
        else:
            return self._process_result(epanet.EN_runQ(self._ph))

    def nextQ(self) -> int:
        """
        EN_nextQ

        Returns
        -------
        int 
            The next water quality simulation time (in seconds). The 
            underlying C funtion returns a tuple (errcode, currentTime), 
            which `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENnextQ())
        else:
            return self._process_result(epanet.EN_nextQ(self._ph))

    def stepQ(self) -> int:
        """
        EN_stepQ

        Returns
        -------
        int 
            The remaining water quality simulation time (in seconds). The 
            underlying C funtion returns a tuple (errcode, currentTime), 
            which `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENstepQ())
        else:
            return self._process_result(epanet.EN_stepQ(self._ph))

    def closeQ(self) -> None:
        """
        EN_closeQ

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENcloseQ())
        else:
            return self._process_result(epanet.EN_closeQ(self._ph))

    def writeline(self, line: str) -> None:
        """
        EN_writeline

        Parameters
        ----------
        line : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENwriteline(line))
        else:
            return self._process_result(epanet.EN_writeline(self._ph, line))

    def report(self) -> None:
        """
        EN_report

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENreport())
        else:
            return self._process_result(epanet.EN_report(self._ph))

    def copyreport(self) -> None:
        """
        EN_copyreport

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENcopyreport())
        else:
            return self._process_result(epanet.EN_copyreport(self._ph))

    def clearreport(self) -> None:
        """
        EN_clearreport

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENclearreport())
        else:
            return self._process_result(epanet.EN_clearreport(self._ph))

    def resetreport(self) -> None:
        """
        EN_resetreport

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENresetreport())
        else:
            return self._process_result(epanet.EN_resetreport(self._ph))

    def setreport(self, format_desc: str) -> None:
        """
        EN_setreport

        Parameters
        ----------
        format_desc : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetreport(format_desc))
        else:
            return self._process_result(epanet.EN_setreport(self._ph, format_desc))

    def setstatusreport(self, level: int) -> None:
        """
        EN_setstatusreport

        Parameters
        ----------
        level : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetstatusreport(level))
        else:
            return self._process_result(epanet.EN_setstatusreport(self._ph, level))

    def getversion(self) -> int:
        """
        EN_getversion

        Returns
        -------
        int 
            The EPANET version number. The underlying C function returns a 
            tuple (errcode, version), which `_process_result` unwraps and 
            returns as a plain integer. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetversion())
        else:
            return self._process_result(epanet.EN_getversion())

    def geterror(self, error_code: int) -> str:
        """
        EN_geterror

        Parameters
        ----------
        error_code : `int`

        Returns
        -------
        str 
            The descriptive error message associated with the given error
            code. The underlying C function returns a tuple (errcode, errmsg).
            If retrieving the message fails, a RuntimeError is raised. 
        """
        if self._use_project is False:
            err, err_msg = epanet.ENgeterror(error_code)
        else:
            err, err_msg = epanet.EN_geterror(error_code)

        if err != 0:
            raise RuntimeError("Failed to get error message")

        return err_msg

    def getstatistic(self, stat_type: int) -> float:
        """
        EN_getstatistic

        Parameters
        ----------
        stat_type : `int`

        Returns
        -------
        float
            The requested project statistic. The underlying C function
            returns a tuple (errcode, value), which `_process_result` 
            unwraps and returns as a plain float. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetstatistic(stat_type))
        else:
            return self._process_result(epanet.EN_getstatistic(self._ph, stat_type))

    def getresultindex(self, result_type: int, index: int) -> int:
        """
        EN_getresultindex

        Parameters
        ----------
        result_type : `int`
        index : `int`

        Returns
        -------
        int
            The index of the requested result variable. The underlying C 
            function returns a tuple (errcode, value), which `process_result`
            unwraps and returns as a plain integer.  
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetresultindex(result_type, index))
        else:
            return self._process_result(epanet.EN_getresultindex(self._ph, result_type, index))

    def getoption(self, option: int) -> float:
        """
        EN_getoption

        Parameters
        ----------
        option : `int`

        Returns
        -------
        float 
            The value of the specfied analysis option. The underlying C 
            function returns a tuple (errcode, value), which `_process_result`
            unwraps and returns as a plain float. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetoption(option))
        else:
            return self._process_result(epanet.EN_getoption(self._ph, option))

    def setoption(self, option: int, value: float)-> None:
        """
        EN_setoption

        Parameters
        ----------
        option : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetoption(option, value))
        else:
            return self._process_result(epanet.EN_setoption(self._ph, option, value))

    def getflowunits(self) -> int:
        """
        EN_getflowunits

        Returns
        -------
        int 
            The flow units used in the project. The underlying C function 
            returns a tuple (errcode, units), which `_process_results` unwraps
            and returns as a plain integer. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetflowunits())
        else:
            return self._process_result(epanet.EN_getflowunits(self._ph))

    def setflowunits(self, units: int) -> None:
        """
        EN_setflowunits

        Parameters
        ----------
        units : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetflowunits(units))
        else:
            return self._process_result(epanet.EN_setflowunits(self._ph, units))

    def gettimeparam(self, param: int) -> int:
        """
        EN_gettimeparam

        Parameters
        ----------
        param : `int`

        Returns
        -------
        int
            The requested time parameter (in seconds). The underlying C 
            function returns a tuple (errcode, value), which `_process_result` 
            unwraps and retruns as a plain integer. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgettimeparam(param))
        else:
            return self._process_result(epanet.EN_gettimeparam(self._ph, param))

    def settimeparam(self, param: int, value: int) -> None:
        """
        EN_settimeparam

        Parameters
        ----------
        param : `int`
        value : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsettimeparam(param, value))
        else:
            return self._process_result(epanet.EN_settimeparam(self._ph, param, value))

    def getqualinfo(self)-> list:
        """
        EN_getqualinfo

        Returns
        -------
        list
            A list containing: [qualType, chemName, chemUnits, traceNode]. 
            The underlying C function returns a tuple 
            (errcode, qualType, chemName, chemUnits, traceNode), which
            `_process_result` unwraps and returns as a list of these values. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetqualinfo())
        else:
            return self._process_result(epanet.EN_getqualinfo(self._ph))

    def getqualtype(self) -> list:
        """
        EN_getqualtype

        Returns
        -------
        list
            A list containing: [qualType, traceNode]. 
            The underlying C function returns a tuple 
            (errdcode, qualType, traceNode), which `_process_results` unwraps 
            and returns a list of these values.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetqualtype())
        else:
            return self._process_result(epanet.EN_getqualtype(self._ph))

    def setqualtype(self, qual_type: int, chem_name: str, chem_units: str, trace_node_id: str) -> None:
        """
        EN_setqualtype

        Parameters
        ----------
        qual_type : `int`
        chem_name : `str`
        chem_units : `str`
        trace_node_id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetqualtype(qual_type, chem_name, chem_units,
                                                             trace_node_id))
        else:
            return self._process_result(epanet.EN_setqualtype(self._ph, qual_type, chem_name,
                                                              chem_units, trace_node_id))

    def addnode(self, node_id: str, node_type: int) -> int:
        """
        EN_addnode

        Parameters
        ----------
        node_id : `str`
        node_type : `int`

        Returns
        -------
        int
            The index of the newly added node. The underlying C function
            returns a tupel (errcode, index), which `_process_result` unwraps
            and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENaddnode(node_id, node_type))
        else:
            return self._process_result(epanet.EN_addnode(self._ph, node_id, node_type))

    def deletenode(self, index: int, action_code: int) -> None:
        """
        EN_deletenode

        Parameters
        ----------
        index : `int`
        action_code : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENdeletenode(index, action_code))
        else:
            return self._process_result(epanet.EN_deletenode(self._ph, index, action_code))

    def getnodeindex(self, node_id: str) -> int:
        """
        EN_getnodeindex

        Parameters
        ----------
        node_id : `str`

        Returns
        -------
        int
            The index of the node with the given ID. The underlying C 
            function returns a tuple (errcode, index), which 
            `_process_result` unwraps and returns as a plain integer.  
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetnodeindex(node_id))
        else:
            return self._process_result(epanet.EN_getnodeindex(self._ph, node_id))

    def getnodeid(self, index: int) -> str:
        """
        EN_getnodeid

        Parameters
        ----------
        index : `int`

        Returns
        -------
        str
            The ID of the node at the given index. The underlying C function 
            returns a tuple (errcode, id), which `_process_result` 
            unwraps and returns as a plain string.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetnodeid(index))
        else:
            return self._process_result(epanet.EN_getnodeid(self._ph, index))

    def setnodeid(self, index: int, new_id: str) -> None:
        """
        EN_setnodeid

        Parameters
        ----------
        index : `int`
        new_id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetnodeid(index, new_id))
        else:
            return self._process_result(epanet.EN_setnodeid(self._ph, index, new_id))

    def getnodetype(self, index: int) -> int:
        """
        EN_getnodetype

        Parameters
        ----------
        index : `int`

        Returns
        -------
        int
            The type of the node at the given index. The underlying C 
            function returns a tuple (errcode, nodeType), which 
            `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetnodetype(index))
        else:
            return self._process_result(epanet.EN_getnodetype(self._ph, index))

    def getnodevalue(self, index: int, node_property: int) -> float:
        """
        EN_getnodevalue

        Parameters
        ----------
        index : `int`
        node_property : `int`

        Returns
        -------
        float
            The value of the specified node property. The underlying C 
            function returns a tuple (errcode, value), which 
            `_process_result` unwraps and returns as a plain float.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetnodevalue(index, node_property))
        else:
            return self._process_result(epanet.EN_getnodevalue(self._ph, index, node_property))

    def setnodevalue(self, index: int, node_property: int, value: float) -> None:
        """
        EN_setnodevalue

        Parameters
        ----------
        index : `int`
        node_property : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetnodevalue(index, node_property, value))
        else:
            return self._process_result(epanet.EN_setnodevalue(self._ph, index, node_property,
                                                               value))

    def setnodevalues(self, node_property: int, values: list[float]) -> None:
        """
        EN_setnodevalues

        Parameters
        ----------
        node_property : `int`
        values : `list[float]`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetnodevalues(node_property, values))
        else:
            return self._process_result(epanet.EN_setnodevalues(self._ph, node_property, values))

    def setjuncdata(self, index: int, elev: float, dmnd: float, dmnd_pat: str) -> None:
        """
        EN_setjuncdata

        Parameters
        ----------
        index : `int`
        elev : `float`
        dmnd : `float`
        dmdn_pat : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetjuncdata(index, elev, dmnd, dmnd_pat))
        else:
            return self._process_result(epanet.EN_setjuncdata(self._ph, index, elev, dmnd,
                                                              dmnd_pat))

    def settankdata(self, index: int, elev: float, initlvl: float, minlvl: float, maxlvl: float,
                    diam: float, minvol: float, volcurve: str) -> None:
        """
        EN_settankdata

        Parameters
        ----------
        index : `int`
        elev : `float`
        initlvl : `float`
        minlvl : `float`
        maxlvl : `float`
        diam : `float`
        minvol : `float`
        volcurve : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsettankdata(index, elev, initlvl, minlvl, maxlvl,
                                                             diam, minvol, volcurve))
        else:
            return self._process_result(epanet.EN_settankdata(self._ph, index, elev, initlvl,
                                                              minlvl, maxlvl, diam, minvol,
                                                              volcurve))

    def getcoord(self, index: int) -> list:
        """
        EN_getcoord

        Parameters
        ----------
        index : `int`

        Returns
        -------
        list
            A list containing the x- and y-coordinates of the node: [x, y]. 
            The underlying C function returns a tuple (errcode, x, y), 
            which `_process_result` unwraps and returns as a list of two floats. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcoord(index))
        else:
            return self._process_result(epanet.EN_getcoord(self._ph, index))

    def setcoord(self, index: int, x: float, y: float) -> None:
        """
        EN_setcoord

        Parameters
        ----------
        index : `int`
        x : `float`
        y : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetcoord(index, x, y))
        else:
            return self._process_result(epanet.EN_setcoord(self._ph, index, x, y))

    def getdemandmodel(self) -> list:
        """
        EN_getdemandmodel

        Returns
        -------
        list
            A list containing the demand model parameters:
            [type, pmin, preq, pexp].
            The underlying C function returns a tuple 
            (errcode, type, pmin, preq, pexp), which `_process_result` 
            unwraps and returns as a list of these values.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetdemandmodel())
        else:
            return self._process_result(epanet.EN_getdemandmodel(self._ph))

    def setdemandmodel(self, demand_type: int, pmin: float, preq: float, pexp: float) -> None:
        """
        EN_setdemandmodel

        Parameters
        ----------
        demand_type : `int`
        pmin : `float`
        preq : `float`
        pexp : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetdemandmodel(demand_type, pmin, preq, pexp))
        else:
            return self._process_result(epanet.EN_setdemandmodel(self._ph, demand_type,
                                                                 pmin, preq, pexp))

    def adddemand(self, node_index: int, base_demand: float, demand_pattern: str, demand_name: str) -> None:
        """
        EN_adddemand

        node_index : `int`
        base_demand : `float`
        demand_pattern : `str`
        demand_name : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENadddemand(node_index, base_demand, demand_pattern,
                                                           demand_name))
        else:
            return self._process_result(epanet.EN_adddemand(self._ph, node_index, base_demand,
                                                            demand_pattern, demand_name))

    def deletedemand(self, node_index: int, demand_index: int) -> None:
        """
        EN_deletedemand

        Parameters
        ----------
        node_index : `int`
        demand_index : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENdeletedemand(node_index, demand_index))
        else:
            return self._process_result(epanet.EN_deletedemand(self._ph, node_index, demand_index))

    def getdemandindex(self, node_index: int, demand_name: str) -> int:
        """
        EN_getdemandindex

        Parameters
        ----------
        node_index : `int`
        demand_name : `str`

        Returns
        -------
        int
            The index of the demand with the given name at the specified node. 
            The underlying C function returns a tuple (errcode, demandIndex), 
            which `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetdemandindex(node_index, demand_name))
        else:
            return self._process_result(epanet.EN_getdemandindex(self._ph, node_index, demand_name))

    def getnumdemands(self, node_index: int) -> int:
        """
        EN_getnumdemands

        Parameters
        ----------
        node_index : `int`

        Returns
        -------
        int
            The number of demands defined for the specified node. The 
            underlying C function returns a tuple (errcode, numDemands), 
            which `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetnumdemands(node_index))
        else:
            return self._process_result(epanet.EN_getnumdemands(self._ph, node_index))

    def getbasedemand(self, node_index: int, demand_index: int) -> float:
        """
        EN_getbasedemand

        Parameters
        ----------
        node_index : `int`
        demand_index : `int`

        Returns
        -------
        float
            The base demand value for the specified demand at the given node.
            The underlying C function returns a tuple (errcode, baseDemand), 
            which `_process_result` unwraps and returns as a plain float.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetbasedemand(node_index, demand_index))
        else:
            return self._process_result(epanet.EN_getbasedemand(self._ph, node_index, demand_index))

    def setbasedemand(self, node_index: int, demand_index: int, base_demand: float) -> None:
        """
        EN_setbasedemand

        Parameters
        ----------
        node_index : `int`
        demand_index : `int`
        base_demand : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetbasedemand(node_index, demand_index,
                                                               base_demand))
        else:
            return self._process_result(epanet.EN_setbasedemand(self._ph, node_index, demand_index,
                                                                base_demand))

    def getdemandpattern(self, node_index: int, demand_index: int) -> int:
        """
        EN_getdemandpattern

        Parameters
        ----------
        node_index : `int`
        demand_index : `int`

        Returns
        -------
        int
            The index of the demand pattern assigned to the specified demand.
            The underlying C function returns a tuple (errcode, patIndex), 
            which `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetdemandpattern(node_index, demand_index))
        else:
            return self._process_result(epanet.EN_getdemandpattern(self._ph, node_index,
                                                                   demand_index))

    def setdemandpattern(self, node_index: int, demand_index: int, pat_index: int) -> None:
        """
        EN_setdemandpattern

        Parameters
        ----------
        node_index : `int`
        demand_index : `int`
        pat_index : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetdemandpattern(node_index, demand_index,
                                                                  pat_index))
        else:
            return self._process_result(epanet.EN_setdemandpattern(self._ph, node_index,
                                                                   demand_index, pat_index))

    def getdemandname(self, node_index: int, demand_index: int) -> str:
        """
        EN_getdemandname

        Parameters
        ----------
        node_index : `int`
        demand_index : `int`

        Returns
        -------
        str
            The name of the specified demand. The underlying C function 
            returns a tuple (errcode, demandName), which `_process_result` 
            unwraps and returns as a plain string.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetdemandname(node_index, demand_index))
        else:
            return self._process_result(epanet.EN_getdemandname(self._ph, node_index, demand_index))

    def setdemandname(self, node_index: int, demand_index: int, demand_name: str) -> None:
        """
        EN_setdemandname

        Parameters
        ----------
        node_index : `int`
        demand_index : `int`
        demand_name : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetdemandname(node_index, demand_index,
                                                               demand_name))
        else:
            return self._process_result(epanet.EN_setdemandname(self._ph, node_index, demand_index,
                                                                demand_name))

    def addlink(self, id: str, link_type: int, from_node: str, to_node: str) -> int:
        """
        EN_addlink

        Parameters
        ----------
        id : `str`
        link_type : `int`
        from_node : `str`
        to_node : `str`

        Returns
        -------
        int
            The index of the newly added link. The underlying C function 
            returns a tuple (errcode, index), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENaddlink(id, link_type, from_node, to_node))
        else:
            return self._process_result(epanet.EN_addlink(self._ph, id, link_type, from_node,
                                                          to_node))

    def deletelink(self, index: int, action_code: int) -> None:
        """
        EN_deletelink

        Parameters
        ----------
        index : `int`
        action_code : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENdeletelink(index, action_code))
        else:
            return self._process_result(epanet.EN_deletelink(self._ph, index, action_code))

    def getlinkindex(self, link_id: str) -> int:
        """
        EN_getlinkindex

        Parameters
        ----------
        link_id : `str`

        Returns
        -------
        int
            The index of the link with the given ID. The underlying C 
            function returns a tuple (errcode, index), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetlinkindex(link_id))
        else:
            return self._process_result(epanet.EN_getlinkindex(self._ph, link_id))

    def getlinkid(self, index: int) -> str:
        """
        EN_getlinkid

        Parameters
        ----------
        index : `int`

        Returns
        -------
        str
            The ID of the link at the given index. The underlying C function 
            returns a tuple (errcode, id), which `_process_result` unwraps 
            and returns as a plain string.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetlinkid(index))
        else:
            return self._process_result(epanet.EN_getlinkid(self._ph, index))

    def setlinkid(self, index: int, new_id: str) -> None:
        """
        EN_setlinkid

        Parameters
        ----------
        index : `int`
        new_id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetlinkid(index, new_id))
        else:
            return self._process_result(epanet.EN_setlinkid(self._ph, index, new_id))

    def getlinktype(self, index: int) -> int:
        """
        EN_getlinktype

        Parameters
        ----------
        index : `int`

        Returns
        -------
        int
            The type of the link at the given index. The underlying C 
            function returns a tuple (errcode, linkType), which 
            `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetlinktype(index))
        else:
            return self._process_result(epanet.EN_getlinktype(self._ph, index))

    def setlinktype(self, index: int, link_type: int, action_code: int) -> int:
        """
        EN_setlinktype

        Parameters
        ----------
        index : `int`
        link_type : `int`
        action_code : `int`

        Returns
        -------
        int
            The (possibly updated) link index. The underlying C function 
            returns a tuple (errcode, input_index), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetlinktype(index, link_type, action_code))
        else:
            return self._process_result(epanet.EN_setlinktype(self._ph, index, link_type,
                                                              action_code))

    def getlinknodes(self, index: int) -> list:
        """
        EN_getlinknodes

        Parameters
        ----------
        index : `int`

        Returns
        -------
        list
            A list containing the indices of the upstream and downstream nodes
            of the link: [node1, node2]. 
            The underlying C function returns a tuple (errcode, node1, node2), 
            which `_process_result` unwraps and returns as a list of two integers.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetlinknodes(index))
        else:
            return self._process_result(epanet.EN_getlinknodes(self._ph, index))

    def setlinknodes(self, index: int, node1: int, node2: int) -> None:
        """
        EN_setlinknodes

        Parameters
        ----------
        index : `int`
        node1 : `int`
        node2 : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetlinknodes(index, node1, node2))
        else:
            return self._process_result(epanet.EN_setlinknodes(self._ph, index, node1, node2))

    def getlinkvalue(self, index: int, property: int) -> float:
        """
        EN_getlinkvalue

        Parameters
        ----------
        index : `int`
        property : `int`

        Returns
        -------
        float
            The value of the specified link property. The underlying C 
            function returns a tuple (errcode, value), which `_process_result` 
            unwraps and returns as a plain float.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetlinkvalue(index, property))
        else:
            return self._process_result(epanet.EN_getlinkvalue(self._ph, index, property))

    def setlinkvalue(self, index: int, property: int, value: float) -> None:
        """
        EN_setlinkvalue

        Parameters
        ----------
        index : `int`
        property : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetlinkvalue(index, property, value))
        else:
            return self._process_result(epanet.EN_setlinkvalue(self._ph, index, property, value))

    def setlinkvalues(self, property: int, values: list[float]) -> int:
        """
        EN_setlinkvalues

        Parameters
        ----------
        property : `int`
        values : `list[float]`

        Returns
        -------
        int
            The index of the first link for which the update failed. 
            The underlying C function returns a tuple (errcode, badIndex), which 
            `_process_result` unwraps and returns as a plain integer.
            A return value of 0 indicates that all updates succeeded. 

        
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetlinkvalues(property, values))
        else:
            return self._process_result(epanet.EN_setlinkvalues(self._ph, property, values))

    def setpipedata(self, index: int, length: float, diam: float, rough: float, mloss: float) -> None:
        """
        EN_setpipedata

        Parameters
        ----------
        index : `int`
        length : `float`
        diam : `float`
        rough : `float`
        mloss : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetpipedata(index, length, diam, rough, mloss))
        else:
            return self._process_result(epanet.EN_setpipedata(self._ph, index, length, diam, rough,
                                                              mloss))

    def getvertexcount(self, index: int) -> int:
        """
        EN_getvertexcount

        Parameters
        ----------
        index : `int`

        Returns
        -------
        int
            The number of vertices associated with the link. The underlying 
            C function returns a tuple (errcode, count), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetvertexcount(index))
        else:
            return self._process_result(epanet.EN_getvertexcount(self._ph, index))

    def getvertex(self, index: int, vertex: int) -> list:
        """
        EN_getvertex

        Parameters
        ----------
        index : `int`
        vertex : `int`

        Returns
        -------
        list
            A list [x, y] containing the coordinates of the specified 
            vertex. The underlying C function returns a tuple (errcode, x, y), 
            which `_process_result` unwraps and returns as a list of two floats.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetvertex(index, vertex))
        else:
            return self._process_result(epanet.EN_getvertex(self._ph, index, vertex))

    def setvertices(self, index: int, x: list[float], y: list[float], count: int) -> None:
        """
        EN_setvertices

        Parameters
        ----------
        index : `int`
        x : `list[float]`
        y : `list[float]`
        count : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetvertices(index, x, y, count))
        else:
            return self._process_result(epanet.EN_setvertices(self._ph, index, x, y, count))

    def getpumptype(self, link_index: int) -> int:
        """
        EN_getpumptype

        Parameters
        ----------
        link_index : `int`

        Returns
        -------
        int
            The pump type of the specified link. The underlying C function 
            returns a tuple (errcode, pumpType), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetpumptype(link_index))
        else:
            return self._process_result(epanet.EN_getpumptype(self._ph, link_index))

    def getheadcurveindex(self, link_index: int) -> int:
        """
        EN_getheadcurveindex

        Parameters
        ----------
        link_index : `int`

        Returns
        -------
        int
            The index of the head curve assigned to the pump. The underlying 
            C function returns a tuple (errcode, curveIndex), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetheadcurveindex(link_index))
        else:
            return self._process_result(epanet.EN_getheadcurveindex(self._ph, link_index))

    def setheadcurveindex(self, link_index: int, curve_index: int) -> None:
        """
        EN_setheadcurveindex

        Parameters
        ----------
        link_index : `int`
        curve_index : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetheadcurveindex(link_index, curve_index))
        else:
            return self._process_result(epanet.EN_setheadcurveindex(self._ph, link_index,
                                                                    curve_index))

    def addpattern(self, id: str) -> None:
        """
        EN_addpattern

        Parameters
        ----------
        id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENaddpattern(id))
        else:
            return self._process_result(epanet.EN_addpattern(self._ph, id))

    def deletepattern(self, index: int) -> None:
        """
        EN_deletepattern

        Parameters
        ----------
        index : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENdeletepattern(index))
        else:
            return self._process_result(epanet.EN_deletepattern(self._ph, index))

    def getpatternindex(self, pattern_id: str) -> int:
        """
        EN_getpatternindex

        Parameters
        ----------
        pattern_id : `str`

        Returns
        -------
        int
            The index of the pattern with the given ID. The underlying C 
            function returns a tuple (errcode, index), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetpatternindex(pattern_id))
        else:
            return self._process_result(epanet.EN_getpatternindex(self._ph, pattern_id))

    def getpatternid(self, index: int) -> str:
        """
        EN_getpatternid

        Parameters
        ----------
        index : `int`

        Returns
        -------
        str
            The ID of the pattern at the given index. The underlying C 
            function returns a tuple (errcode, id), which `_process_result` 
            unwraps and returns as a plain string.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetpatternid(index))
        else:
            return self._process_result(epanet.EN_getpatternid(self._ph, index))

    def setpatternid(self, index: int, id: str) -> None:
        """
        EN_setpatternid

        Parameters
        ----------
        index : `int`
        id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetpatternid(index, id))
        else:
            return self._process_result(epanet.EN_setpatternid(self._ph, index, id))

    def getpatternlen(self, index: int) -> int:
        """
        EN_getpatternlen

        Parameters
        ----------
        index : `int`

        Returns
        -------
        int
            The number of periods in the specified pattern. The underlying 
            C function returns a tuple (errcode, length), which 
            `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetpatternlen(index))
        else:
            return self._process_result(epanet.EN_getpatternlen(self._ph, index))

    def getpatternvalue(self, index: int, period: int) -> float:
        """
        EN_getpatternvalue

        Parameters
        ----------
        index : `int`
        period : `int`

        Returns
        -------
        float
            The multiplier value for the specified pattern period. The underlying 
            C function returns a tuple (errcode, value), which `_process_result` 
            unwraps and returns as a plain float.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetpatternvalue(index, period))
        else:
            return self._process_result(epanet.EN_getpatternvalue(self._ph, index, period))

    def setpatternvalue(self, index: int, period: int, value: float) -> None:
        """
        EN_setpatternvalue

        Parameters
        ----------
        index : `int`
        period : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetpatternvalue(index, period, value))
        else:
            return self._process_result(epanet.EN_setpatternvalue(self._ph, index, period, value))

    def getaveragepatternvalue(self, index: int) -> float:
        """
        EN_getaveragepatternvalue

        Parameters
        ----------
        index : `int`

        Returns
        -------
        float 
            The average multiplier value of the specified pattern. The underlying C 
            function returns a tuple (errcode, value), which `_process_result` 
            unwraps and returns as a plain float.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetaveragepatternvalue(index))
        else:
            return self._process_result(epanet.EN_getaveragepatternvalue(self._ph, index))

    def setpattern(self, index: int, values: list[float], len: int) -> None:
        """
        EN_setpattern

        Parameters
        ----------
        index : `int`
        values : `list[float]`
        len : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetpattern(index, values, len))
        else:
            return self._process_result(epanet.EN_setpattern(self._ph, index, values, len))

    def addcurve(self, id: str) -> None:
        """
        EN_addcurve

        Parameters
        ----------
        id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENaddcurve(id))
        else:
            return self._process_result(epanet.EN_addcurve(self._ph, id))

    def deletecurve(self, index: int) -> None:
        """
        EN_deletecurve

        Parameters
        ----------
        index : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENdeletecurve(index))
        else:
            return self._process_result(epanet.EN_deletecurve(self._ph, index))

    def getcurveindex(self, id: str) -> int:
        """
        EN_getcurveindex

        Parameters
        ----------
        id : `str`

        Returns
        -------
        int
            The index of the curve with the given ID. The underlying C 
            function returns a tuple (errcode, idnex), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcurveindex(id))
        else:
            return self._process_result(epanet.EN_getcurveindex(self._ph, id))

    def getcurveid(self, index: int) -> str:
        """
        EN_getcurveid

        Parameters
        ----------
        index : `int`

        Returns
        -------
        str
            The ID of the curve at the given index. The underlying C 
            function returns a tuple (errcode, id), which `_process_result` 
            unwraps and returns as a plain string.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcurveid(index))
        else:
            return self._process_result(epanet.EN_getcurveid(self._ph, index))

    def setcurveid(self, index: int, id: str) -> None:
        """
        EN_setcurveid

        Parameters
        ----------
        index : `int`
        id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetcurveid(index, id))
        else:
            return self._process_result(epanet.EN_setcurveid(self._ph, index, id))

    def getcurvelen(self, index: int) -> int:
        """
        EN_getcurvelen

        Parameters
        ----------
        index : `int`

        Returns
        -------
        int
            The number of points in the specified curve. The underlying C 
            function returns a tuple (errcode, value), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcurvelen(index))
        else:
            return self._process_result(epanet.EN_getcurvelen(self._ph, index))

    def getcurvetype(self, index: int) -> int:
        """
        EN_getcurvetype

        Parameters
        ----------
        index : `int`
        
        Returns
        -------
        int
            The type of the curve at the given index. The underlying C 
            function returns a tuple (errcode, type), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcurvetype(index))
        else:
            return self._process_result(epanet.EN_getcurvetype(self._ph, index))

    def getcurvevalue(self, curve_index: int, point_index: int) -> list:
        """
        EN_getcurvevalue

        Parameters
        ----------
        curve_index : `int`
        point_index : `int`

        Returns
        -------
        list
            A list [x, y] containing the coordinates of the specified curve 
            point. The underlying C function returns (errcode, x, y), which 
            `_process_result` unwraps and returns as a list of two floats.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcurvevalue(curve_index, point_index))
        else:
            return self._process_result(epanet.EN_getcurvevalue(self._ph, curve_index, point_index))

    def setcurvevalue(self, curve_index: int, point_index: int, x: float, y: float) -> None:
        """
        EN_setcurvevalue

        Parameters
        ----------
        curve_index : `int`
        point_index : `int`
        x : `float`
        y : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetcurvevalue(curve_index, point_index, x, y))
        else:
            return self._process_result(epanet.EN_setcurvevalue(self._ph, curve_index, point_index,
                                                                x, y))

    def getcurve(self, index: int) -> list:
        """
        EN_getcurve

        Parameters
        ----------
        index : `int`

        Returns
        -------
            A list [x_values, y_values] containing the curve's point
            coordinates. The underlying C function returns
            (errcode, xValuesList, yValuesList), which `_process_result`
            unwraps and returns as a list of two lists of floats.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcurve(index))
        else:
            return self._process_result(epanet.EN_getcurve(self._ph, index))

    def setcurve(self, index: int, x_values: list[float], y_values: list[float], n_points: int) -> None:
        """
        EN_setcurve

        Parameters
        ----------
        index : `int`
        x_values : `list[float]`
        y_values : `list[float]`
        n_points : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetcurve(index, x_values, y_values, n_points))
        else:
            return self._process_result(epanet.EN_setcurve(self._ph, index, x_values, y_values,
                                                           n_points))

    def addcontrol(self, type: int, link_index: int, setting: float, node_index: int, level: float) -> int:
        """
        EN_addcontrol

        Parameters
        ----------
        type : `int`
        link_index : `int`
        setting : `float`
        node_index . `int`
        level : `float`

        Returns
        -------
        int
            The index of the newly added control. The underlying C function
            returns a tuple (errcode, index), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENaddcontrol(type, link_index, setting, node_index,
                                                            level))
        else:
            return self._process_result(epanet.EN_addcontrol(self._ph, type, link_index, setting,
                                                             node_index, level))

    def deletecontrol(self, index: int) -> None:
        """
        EN_deletecontrol

        Parameters
        ----------
        index : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENdeletecontrol(index))
        else:
            return self._process_result(epanet.EN_deletecontrol(self._ph, index))

    def getcontrol(self, index: int) -> list:
        """
        EN_getcontrol

        Parameters
        ----------
        index : `int`

        Returns
        -------
        list 
            A list containing the properties of the specified control. The 
            underlying C function returns a tuple 
            (errcode, type, linkIndex, setting, nodeIndex, level), which
            `_process_result` unwraps and returns as a list of these values.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcontrol(index))
        else:
            return self._process_result(epanet.EN_getcontrol(self._ph, index))

    def setcontrol(self, index: int, type: int, link_index: int, setting: float, node_index: int,
                   level: float) -> None:
        """
        EN_setcontrol

        Parameters
        ----------
        index : `int`
        type : `int`
        link_index : `int`
        setting : `float`
        node_index : `int`
        level : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetcontrol(index, type, link_index, setting,
                                                            node_index, level))
        else:
            return self._process_result(epanet.EN_setcontrol(self._ph, index, type, link_index,
                                                             setting, node_index, level))

    def addrule(self, rule: str) -> None:
        """
        EN_addrule

        Parameters
        ----------
        rule : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENaddrule(rule))
        else:
            return self._process_result(epanet.EN_addrule(self._ph, rule))

    def deleterule(self, index: int) -> None:
        """
        EN_deleterule

        Parameters
        ----------
        index : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENdeleterule(index))
        else:
            return self._process_result(epanet.EN_deleterule(self._ph, index))

    def getrule(self, index: int) -> list:
        """
        EN_getrule

        Parameters
        ----------
        index : `int`

        Returns
        -------
        list
            A list describing the rule structure. 
            The underlying C function returns a tuple 
            (errcode, nPremises, nThenActions, nElseActions, priority), which 
            `_process_result` unwraps and returns as a list of these values.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetrule(index))
        else:
            return self._process_result(epanet.EN_getrule(self._ph, index))

    def getruleid(self, index: int) -> str:
        """
        EN_getruleID

        Parameters
        ----------
        index : `int`

        Returns
        -------
        str
            The ID of the rule at the given index. The underlying C 
            function returns a tuple (errcode, id), which `_process_result` 
            unwraps and returns as a plain string.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetruleID(index))
        else:
            return self._process_result(epanet.EN_getruleID(self._ph, index))

    def getpremise(self, rule_index: int, premise_index: int) -> list:
        """
        EN_getpremise

        Parameters
        ----------
        rule_index : `int`
        premise_index : `int`

        Returns
        -------
        list
            A list describing the premise. The underlying C function 
            returns a tuple 
            (errcode, logop, object, objIndex, variable, relop, status, value), 
            which `_process_result` unwraps and returns as a list. 
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetpremise(rule_index, premise_index))
        else:
            return self._process_result(epanet.EN_getpremise(self._ph, rule_index, premise_index))

    def setpremise(self, rule_index: int, premise_index: int, logop: int, object: int,
                   obj_index: int, variable: int, relop: int, status: int, value: float) -> None:
        """
        EN_setpremise

        Parameters
        ----------
        rule_index : `int`
        premise_index : `int`
        logop : `int`
        object : `int`
        obj_index : `int`
        variable : `int`
        relop : `int`
        status : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetpremise(rule_index, premise_index, logop,
                                                            object, obj_index, variable, relop,
                                                            status, value))
        else:
            return self._process_result(epanet.EN_setpremise(self._ph, rule_index, premise_index,
                                                             logop, object, obj_index, variable,
                                                             relop, status, value))

    def setpremiseindex(self, rule_index: int, premise_index: int, obj_index: int) -> None:
        """
        EN_setpremiseindex

        Parameters
        ----------
        rule_index : `int`
        premise_index : `int`
        obj_index : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetpremiseindex(rule_index, premise_index,
                                                                 obj_index))
        else:
            return self._process_result(epanet.EN_setpremiseindex(self._ph, rule_index,
                                                                  premise_index, obj_index))

    def setpremisestatus(self, rule_index: int, premise_index: int, status: int) -> None:
        """
        EN_setpremisestatus

        Parameters
        ----------
        rule_index : `int`
        premise_index : `int`
        status : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetpremisestatus(rule_index, premise_index,
                                                                  status))
        else:
            return self._process_result(epanet.EN_setpremisestatus(self._ph, rule_index,
                                                                   premise_index, status))

    def setpremisevalue(self, rule_index: int, premise_index: int, value: float) -> None:
        """
        EN_setpremisevalue

        Parameters
        ----------
        rule_index : `int`
        premise_index : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetpremisevalue(rule_index, premise_index, value))
        else:
            return self._process_result(epanet.EN_setpremisevalue(self._ph, rule_index, premise_index, value))

    def getthenaction(self, rule_index: int, action_index: int) -> list:
        """
        EN_getthenaction

        Parameters
        ----------
        rule_index : `int`
        action_index : `int`

        Returns
        -------
        list
            A list containing the properties of a THEN-action. 
            The underlying C function returns a tuple 
            (errcode, linkIndex, status, setting),  
            which `_process_result` unwraps and returns as a list.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetthenaction(rule_index, action_index))
        else:
            return self._process_result(epanet.EN_getthenaction(self._ph, rule_index, action_index))

    def setthenaction(self, rule_index: int, action_index: int, link_index: int, status: int,
                      setting: float) -> None:
        """
        EN_setthenaction

        Parameters
        ----------
        rule_index : `int`
        action_index : `int`
        link_index : `int`
        status : `int`
        setting : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetthenaction(rule_index, action_index, link_index,
                                                               status, setting))
        else:
            return self._process_result(epanet.EN_setthenaction(self._ph, rule_index, action_index,
                                                                link_index, status, setting))

    def getelseaction(self, rule_index: int, action_index: int) -> list:
        """
        EN_getelseaction

        Parameters
        ----------
        rule_index : `int`
        action_index : `int`

        Returns
        -------
        list
            A list containing the properties of an ELSE-action. 
            The underlying C function returns a tuple 
            (errcode, linkIndex, status, setting),
            which `_process_result` unwraps and returns as a list.

        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetelseaction(rule_index, action_index))
        else:
            return self._process_result(epanet.EN_getelseaction(self._ph, rule_index, action_index))

    def setelseaction(self, rule_index: int, action_index: int, link_index: int, status: int,
                      setting: float) -> None:
        """
        EN_setelseaction

        Parameters
        ----------
        rule_index : `int`
        action_index : `int`
        link_index : `int`
        status : `int`
        setting : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetelseaction(rule_index, action_index, link_index,
                                                               status, setting))
        else:
            return self._process_result(epanet.EN_setelseaction(self._ph, rule_index, action_index,
                                                                link_index, status, setting))

    def setrulepriority(self, index: int, priority: float) -> None:
        """
        EN_setrulepriority

        Parameters
        ----------
        index : `int`
        priority : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetrulepriority(index, priority))
        else:
            return self._process_result(epanet.EN_setrulepriority(self._ph, index, priority))

    def gettag(self, obj_type: int, obj_idx: int) -> str:
        """
        EN_gettag

        Parameters
        ----------
        obj_type : `int`
        obj_idx : `int`

        Returns
        -------
        str
            The tag assigned to the object. The underlying C function 
            returns a tuple (errcode, tag), which `_process_result` 
            unwraps and returns as a plain string.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgettag(obj_type, obj_idx))
        else:
            return self._process_result(epanet.EN_gettag(self._ph, obj_type, obj_idx))

    def settag(self, obj_type: int, obj_idx: int, tag: str) -> None:
        """
        EN_settag

        Parameters
        ----------
        obj_type : `int`
        obj_idx : `int`
        tag : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsettag(obj_type, obj_idx, tag))
        else:
            return self._process_result(epanet.EN_settag(self._ph, obj_type, obj_idx, tag))

    def timetonextevent(self) -> list:
        """
        EN_timetonextevent

        Returns
        -------
        list
            A list containing information about when the next hydraulic 
            time step occurs. The underlying C function returns a tuple
            (errcode, eventType, duration, elemIndex), which 
            `_process_result` unwraps and returns as a list.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENtimetonextevent())
        else:
            return self._process_result(epanet.EN_timetonextevent(self._ph))

    def getnodevalues(self, property: int) -> list[float]:
        """
        EN_getnodevalues

        Parameters
        ----------
        property : `int`

        Returns
        -------
        `list[float]`
            A list of node property values. The underlying C function 
            returns a tuple (errcode, valuesList), which `_process_result`
            unwraps and returns as a plain list of floats.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetnodevalues(property))
        else:
            return self._process_result(epanet.EN_getnodevalues(self._ph, property))
        
    def getnodevalues_numpy(self, property: int) -> numpy.ndarray:
        """
        EN_getnodevalues (NumPy compatible)

        Parameters
        ----------
        property : `int`

        Returns
        -------
        `numpy.ndarray`
            A NumPy array of node property values. The underlying C 
            function returns a tuple (errcode, array), which 
            `_process_result` unwraps and returns as a NumPy array.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetnodevalues_NPY(property))
        else:
            return self._process_result(epanet.EN_getnodevalues_NPY(self._ph, property))

    def getlinkvalues(self, property: int) -> list[float]:
        """
        EN_getlinkvalues

        Parameters
        ----------
        property : `int`

        Returns
        -------
        `list[float]`
            A list of link property values. The underlying C function 
            returns a tuple (errcode, valuesList), which `_process_result` 
            unwraps and returns as a plain list of floats.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetlinkvalues(property))
        else:
            return self._process_result(epanet.EN_getlinkvalues(self._ph, property))
        
    def getlinkvalues_numpy(self, property: int) ->  numpy.ndarray:
        """
        EN_getlinkvalues (NumPy compatible)

        Parameters
        ----------
        property : `int`

        Returns
        -------
        `numpy.ndarray`
            A NumPy array of link property values. The underlying C 
            function returns a tuple (errcode, array), which `_process_result` 
            unwraps and returns as a NumPy array.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetlinkvalues_NPY(property))
        else:
            return self._process_result(epanet.EN_getlinkvalues_NPY(self._ph, property))

    def setvertex(self, link_idx: int, vertex_idx: int, x: float, y: float) -> None:
        """
        EN_setvertex

        Parameters
        ----------
        link_idx : `int`
        vertex_idx : `int`
        x : `float`
        y : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetvertex(link_idx, vertex_idx, x, y))
        else:
            return self._process_result(epanet.EN_setvertex(self._ph, link_idx, vertex_idx, x, y))

    def loadpatternfile(self, filename: str, id: str) -> None:
        """
        EN_loadpatternfile

        Parameters
        ----------
        filename : `str`
        id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENloadpatternfile(filename, id))
        else:
            return self._process_result(epanet.EN_loadpatternfile(self._ph, filename, id))

    def setcurvetype(self, curve_idx: int, curve_type: int) -> None:
        """
        EN_setcurvetype

        Parameters
        ----------
        curve_idx : `int`
        curve_type : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetcurvetype(curve_idx, curve_type))
        else:
            return self._process_result(epanet.EN_setcurvetype(self._ph, curve_idx, curve_type))

    def getcontrolenabled(self, control_idx: int) -> int:
        """
        EN_getcontrolenabled: Gets the enabled status of a simple control.

        Parameters
        ----------
        control_idx : `int`

        Returns
        -------
        int
            1 if the control is enabled, 0 if disabled. The underlying C 
            function returns a tuple (errcode, enabled), which 
            `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetcontrolenabled(control_idx))
        else:
            return self._process_result(epanet.EN_getcontrolenabled(self._ph, control_idx))

    def setcontrolenabled(self, control_idx: int, enabled: int) -> None:
        """
        EN_setcontrolenabled

        Parameters
        ----------
        control_idx : `int`
        enabled : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetcontrolenabled(control_idx, enabled))
        else:
            return self._process_result(epanet.EN_setcontrolenabled(self._ph, control_idx, enabled))

    def getruleenabled(self, rule_idx: int) -> int:
        """
        EN_getruleenabled: Gets the enabled status of a rule-based control.

        Parameters
        ----------
        rule_idx : `int`

        Returns
        -------
        int
            1 if the rule is enabled, 0 if disabled. The underlying C 
            function returns a tuple (errcode, enabled), which 
            `_process_result` unwraps and returns as a plain integer.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENgetruleenabled(rule_idx))
        else:
            return self._process_result(epanet.EN_getruleenabled(self._ph, rule_idx))

    def setruleenabled(self, rule_idx: int, enabled: int) -> None:
        """
        EN_setruleenabled

        Parameters
        ----------
        rule_idx : `int`
        enabled : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        if self._use_project is False:
            return self._process_result(epanet.ENsetruleenabled(rule_idx, enabled))
        else:
            return self._process_result(epanet.EN_setruleenabled(self._ph, rule_idx, enabled))

    def MSXENopen(self, inp_file: str, rpt_file: str, out_file: str) -> None:
        """
        MSXENopen: pass-thru to open the EPANET toolkit system

        Parameters
        ----------
        inp_file : `str`
            name of the EPANET input file
        rpt_file : `str`
            name of the EPANET report file
        out_file : `str`
            name of the EPANET output/binary file

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXENopen(inp_file, rpt_file, out_file), msx_call=True)

    def MSXopen(self, fname: str) -> None:
        """
        MSXopen: opens the EPANET-MSX toolkit system.

        Parameters
        ----------
        fname : `str`
            name of an MSX input file 

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXopen(fname), msx_call=True)

    def MSXsolveH(self) -> None:
        """
        MSXsolveH: Runs the hydraulic solver for MSX.

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsolveH(), msx_call=True)

    def MSXusehydfile(self, fname: str) -> None:
        """
        MSXusehydfile: registers a hydraulics solution file with the MSX system.

        Parameters
        ----------
        fname : `str`
            A hydraulic file 

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXusehydfile(fname), msx_call=True)

    def MSXsolveQ(self) -> None:
        """
        MSXsolveQ: Runs the water-quality solver for MSX.

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration. 
        """
        return self._process_result(epanet.MSXsolveQ(), msx_call=True)

    def MSXinit(self, save_flag: int) -> None:
        """
        MSXinit: Initializes an MSX water quality analsis. 

        Parameters
        ----------
        save_flag : `int`
            Flag indicating whether MSX should save intermediate results.
        
        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXinit(save_flag), msx_call=True)

    def MSXstep(self) -> list:
        """
        MSXstep: Advances the MSX water‑quality simulation by one time step.

        Returns
        -------
        list
            A list containing the current time (seconds) and the time remaining
            until the next quality step (seconds). The underlying C 
            function returns a tuple (errcode, t, tleft), which 
            `_process_result` unwraps and returns as a list.
        """
        return self._process_result(epanet.MSXstep(), msx_call=True)

    def MSXsaveoutfile(self, fname: str) -> None:
        """
        MSXsaveoutfile: Saves all results of the WQ simulation.

        Parameters
        ----------
        fname : `str`
            Output file to write MSX results to.

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsaveoutfile(fname), msx_call=True)

    def MSXsavemsxfile(self, fname: str) -> None:
        """
        MSXsavemsxfile

        Parameters
        ----------
        fname : `str`
            File name to save the current MSX model. 

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsavemsxfile(fname), msx_call=True)

    def MSXreport(self) -> None:
        """
        MSXreport:  Generates the MSX report file defined earlier via MSXENopen().

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXreport(), msx_call=True)

    def MSXclose(self) -> None:
        """
        MSXclose: Closes the EPANET-MSX toolkit system. 

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXclose(), msx_call=True)

    def MSXENclose(self) -> None:
        """
        MSXENclose: pass-thru to close the EPANET toolkit system

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.

        """
        return self._process_result(epanet.MSXENclose(), msx_call=True)

    def MSXgetindex(self, item_type: int, id: str) -> int:
        """
        MSXgetindex

        Parameters
        ----------
        item_type : `int`
        id : `str`

        Returns
        -------
        int
            The index of the MSX item. The underlying C function 
            returns a tuple (errcode, index), which `_process_result` 
            unwraps and returns as a plain integer.
        """
        return self._process_result(epanet.MSXgetindex(item_type, id), msx_call=True)

    def MSXgetIDlen(self, item_type: int, index: int) -> int:
        """
        MSXgetIDlen

        Parameters
        ----------
        item_type : `int`
        index : `int`

        Returns
        -------
        int
            Maximum number of characters available in the object's ID. 
            The underlying C function returns a tuple (errcode, length), 
            which `_process_result` unwraps and returns as a plain integer.
        """
        return self._process_result(epanet.MSXgetIDlen(item_type, index), msx_call=True)

    def MSXgetID(self, item_type: int, index: int) -> str:
        """
        MSXgetID

        Parameters
        ----------
        item_type : `int`
        index : `int`

        Returns
        -------
        str
            The ID/name of the specified MSX object. The underlying C 
            function returns a tuple (errcode, id), which 
            `_process_result` unwraps and returns as a plain string.
        """
        return self._process_result(epanet.MSXgetID(item_type, index), msx_call=True)

    def MSXgetcount(self, item_type: int) -> int:
        """
        MSXgetcount

        Parameters
        ----------
        item_type : `int`

        Returns
        -------
        int
            Number of objects of the given type. The underlying C 
            function returns a tuple (errcode, count), which 
            `_process_result` unwraps and returns as a plain integer.
        """
        return self._process_result(epanet.MSXgetcount(item_type), msx_call=True)

    def MSXgetspecies(self, index: int) -> list:
        """
        MSXgetspecies

        Parameters
        ----------
        index : `int`

        Returns
        -------
        list
            A list containing the attributes of a chemical species.
            The underlying C function returns a tuple 
            (errcode, type, units, aTol, rTol), which 
            `_process_result` unwraps and returns as a list.
        """
        return self._process_result(epanet.MSXgetspecies(index), msx_call=True)

    def MSXgetconstant(self, index: int) -> float:
        """
        MSXgetconstant

        Parameters
        ----------
        index : `int`

        Returns
        -------
        float
            The value of the reaction constant. The underlying C 
            function returns a tuple (errcode, value), which 
            `_process_result` unwraps and returns as a plain float.
        """
        return self._process_result(epanet.MSXgetconstant(index), msx_call=True)

    def MSXgetparameter(self, item_type: int, index: int, param: int) -> float:
        """
        MSXgetparameter

        Parameters
        ----------
        item_type : `int`
        index : `int`
        param : `int`

        Returns
        -------
        float
            The value of the requested MSX parameter. The underlying C 
            function returns a tuple (errcode, value), which 
            `_process_result` unwraps and returns as a plain float.
        """
        return self._process_result(epanet.MSXgetparameter(item_type, index, param), msx_call=True)

    def MSXgetsource(self, node: int, species: int) -> list:
        """
        MSXgetsource

        Parameters
        ----------
        node : `int`
        species : `int`

        Returns
        -------
        list
            A list containing information about the source term. 
            The underlying C function returns a tuple 
            (errcode, type, level, pat), which 
            `_process_result` unwraps and returns as a list.
        """
        return self._process_result(epanet.MSXgetsource(node, species), msx_call=True)

    def MSXgetpatternlen(self, pat: int) -> int:
        """
        MSXgetpatternlen

        Parameters
        ----------
        pat : `int`

        Returns
        -------
        int
            Number of periods in the MSX pattern. The underlying C 
            function returns a tuple (errcode, length), which 
            `_process_result` unwraps and returns as a plain integer.
        """
        return self._process_result(epanet.MSXgetpatternlen(pat), msx_call=True)

    def MSXgetpatternvalue(self, pat: int, period: int) -> float:
        """
        MSXgetpatternvalue

        Parameters
        ----------
        pat : `int`
        period : `int`

        Returns
        -------
        float
            The multiplier value for the given pattern period. The 
            underlying C function returns a tuple (errcode, value),
            which _process_result` unwraps and returns as a plain float.
        """
        return self._process_result(epanet.MSXgetpatternvalue(pat, period), msx_call=True)

    def MSXgetinitqual(self, item_type: int, index: int, species: int) -> float:
        """
        MSXgetinitqual

        Parameters
        ----------
        item_type : `int`
        index : `int`
        species : `int`

        Returns
        -------
        float
            Initial concentration of the species at the given object. 
            The underlying C function returns a tuple (errcode, value), 
            which `_process_result` unwraps and returns as a plain float.
        """
        return self._process_result(epanet.MSXgetinitqual(item_type, index, species), msx_call=True)

    def MSXgetqual(self, item_type: int, index: int, species: int) -> float:
        """
        MSXgetqual

        Parameters
        ----------
        item_type : `int`
        index : `int`
        species : `int`

        Returns
        -------
        float
            Current concentration of the species at the given object.
            The underlying C function returns a tuple (errcode, value), 
            which `_process_result` unwraps and returns as a plain float.
        """
        return self._process_result(epanet.MSXgetqual(item_type, index, species), msx_call=True)

    def MSXgeterror(self, err_code: int) -> str:
        """
        MSXgeterror

        Parameters
        ----------
        err_code : `int`

        Returns
        -------
        str
            The error message corresponding to the given error code
            If MSXgeterror itself fails, a RuntimeError is raised.
        """
        err, msg = epanet.MSXgeterror(err_code)
        if err != 0:
            raise RuntimeError("Failed to get error message")
        else:
            return msg

    def MSXsetconstant(self, index: int, value: float) -> None:
        """
        MSXsetconstant

        Parameters
        ----------
        index : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsetconstant(index, value))

    def MSXsetparameter(self, item_type: int, index: int, param: int, value: float) -> None:
        """
        MSXsetparameter

        Parameters
        ----------
        item_type : `int`
        index : `int`
        param : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsetparameter(item_type, index, param, value),
                                    msx_call=True)

    def MSXsetinitqual(self, item_type: int, index: int, species: int, value: float) -> None:
        """
        MSXsetinitqual

        Parameters
        ----------
        item_type : `int`
        index : `int`
        species : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsetinitqual(item_type, index, species, value),
                                    msx_call=True)

    def MSXsetsource(self, node: int, species: int, item_type: int, level: float, pat: int) -> None:
        """
        MSXsetsource

        Parameters
        ----------
        node : `int`
        species : `int`
        item_type : `int`
        level : `float`
        pat : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsetsource(node, species, item_type, level, pat),
                                    msx_call=True)

    def MSXsetpatternvalue(self, pat: int, period: int, value: float) -> None:
        """
        MSXsetpatternvalue

        Parameters
        ----------
        pat : `int`
        period : `int`
        value : `float`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsetpatternvalue(pat, period, value), msx_call=True)

    def MSXsetpattern(self, pat: int, mult: list[float], len: int) -> None:
        """
        MSXsetpattern

        Parameters
        ----------
        pat : `int`
        mult : `list[float]`
        len : `int`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXsetpattern(pat, mult, len), msx_call=True)

    def MSXaddpattern(self, id: str) -> None:
        """
        MSXaddpattern

        Parameters
        ----------
        id : `str`

        Returns
        -------
        None
            The underlying C function returns a tuple containing only the
            error code (errcode,), which `_process_result` unwraps and
            returns as None. Errors trigger warnings or exceptions depending 
            on configuration.
        """
        return self._process_result(epanet.MSXaddpattern(id), msx_call=True)
