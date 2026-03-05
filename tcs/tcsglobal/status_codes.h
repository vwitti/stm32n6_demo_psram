/********************************************************************************
* @file		status_codes.h
* @brief	Status Definitionen.
*******************************************************************************/
#ifndef TCSGLOBAL_STATUS_CODES_H_
#define TCSGLOBAL_STATUS_CODES_H_

// macros to check for success/failure

/******************************************************************************/
/**
 * @brief		This function determines if the given status value 
 * 					<t teStatus> belongs to the unsuccessfull status values, 
 * 					(which are all negative values).
 * 
 * @param		x	status to test \n
 * 						Typ:	teStatus
 * @return	returns TRUE is <p Status> is failed or 
 * 					FALSE if <p Status> is success
 **/
#define PSTATUS_ERR(x)	((x) < 0)


/******************************************************************************/
/**
 * @brief		this function determines if the given status value 
 * 					<t teStatus> belongs to the successfull status values, 
 * 					(which are all positiv values).
 * 
 * @param		x	status to test \n
 * 						Typ: teStatus
 * @return	returns TRUE is <p Status> is a success or 
 * 					FALSE if <p Status> failed
 **/
#define PSTATUS_OK(x)		((x) >= 0)


/******************************************************************************/
/**
 * @brief		failure codes must be below zero.
 **/
//@xref <f FAILED> <f SUCCEEDED>
typedef enum
{
    //
    // <p Success codes>
    //
    eStSuccess              =    0, ///<  000 call was successful
#if 0
	eStPending              =    1, ///<  001 no error, call is pending and will call callback
    eStContinue             =    2, ///<  002 Continue Process
		eStSuspend              =    3, ///<  003 Suspend current process
		eStFinished             =    4, ///<  004 Process has finished (with success)
		eStFileNoError          =  600, ///<  600 No FileApi Error
    //
    // <p Interrupt Service Routines>
    //
    eStCantRegisterIsr      = -100, ///< -100/0xFF9C OS cannot register an interrupt service routine
    eStCantUnregisterIsr    = -101, ///< -101/0xFF9B OS cannot unregister an interrupt service routine
    eStUnexpException       = -102, ///< -102/0xFF9A Unexpected exception occured
#endif
    //
    // <p Other general purpose error codes>
    //
    eStInvalidHandle        = -200, ///< -200/0xFF38 invalid handle for operation
    eStInvalidData          = -201, ///< -200/0xFF38 invalid data for operation    
    eStNotFound             = -202, ///< -202/0xFF36 something was not found
    eStNotConnected         = -203, ///< -203/0xFF35 No connection established
    eStWrongVersion         = -204, ///< -204/0xFF34 some version information does not match
    eStWrongState           = -205, ///< -205/0xFF33 requested operation is not permitted in current state, or state is not as expected
    eStWrongParameter       = -206, ///< -206/0xFF32 a given parameter is invalid
    eStWrongParameter1      = -207, ///< -207/0xFF31 the given parameter 1 is invalid
    eStWrongParameter2      = -208, ///< -208/0xFF30 the given parameter 2 is invalid
    eStWrongParameter3      = -209, ///< -209/0xFF2F the given parameter 3 is invalid
    eStWrongParameter4      = -210, ///< -210/0xFF2E the given parameter 4 is invalid
    eStInitializationError  = -211, ///< -211/0xFF2D an initialisation sequence fails
    eStNotSupported         = -212, ///< -212/0xFF2C the requested function/operation is not supported
    eStGeneralError         = -213, ///< -213/0xFF2B operation failed with unspecified error
    eStWrongCrc             = -214, ///< -214/0xFF2A CRC is invalid
    eStUnknownCommand       = -215, ///< -215/0xFF29 command is unknown
    eStResourceBusy         = -216, ///< -216/0xFF28 the resource is currently busy
    eStNoResource           = -217, ///< -217/0xFF27 the requested resource is already in use or not available
    eStOutOfMemory          = -218, ///< -218/0xFF26 unsufficient memory
    eStTimeout              = -219, ///< -219/0xFF25 timeout occured
    eStAssertionFailed      = -220, ///< -220/0xFF24 Assertion failed
    eStUpdateFailed         = -221, ///< -221/0xFF23 Update failed
    eStNotCreated           = -222, ///< -222/0xFF22 Something has not been created
    eStNoAccess             = -223, ///< -223/0xFF21 No access to resource
    eStMsgNotSend           = -224, ///< -224/0xFF20 Message has not been sent
    eStAlignment            = -225, ///< -225/0xFF1F Improper Memory alignment
    eStFull                 = -226, ///< -226/0xFF1E Something was already full
    eStNotOwner             = -227, ///< -227/0xFF1D Not owner of a resource
    eStCantStart            = -228, ///< -228/0xFF1C Something was not started
    eStCantStop             = -229, ///< -229/0xFF1B Something could not be stopped
    eStWrongParameter5      = -230, ///< -230/0xFF1A the given parameter 5 is invalid
    eStWrongParameter6      = -231, ///< -231/0xFF19 the given parameter 6 is invalid
    eStWrongParameter7      = -232, ///< -232/0xFF18 the given parameter 7 is invalid
    eStWrongParameter8      = -233, ///< -233/0xFF17 the given parameter 8 is invalid
    eStLowerLimit           = -234, ///< -234/0xFF16 value of the given parameter is lower than lower limit
    eStUpperLimit           = -235, ///< -235/0xFF15 value of the given parameter is higher than upper limit
    eStEmpty				= -236, ///< -236/0xFF14 Something is empty
    eStSizeTooSmall			= -237, ///< -237/0xFF13 a resource is not big enough
    eStInUse				= -238, ///< -238/0xFF12 something is already in use
    eStWrongType			= -239, ///< -239/0xFF11 something does not have the expected type
	eStSizeTooLarge			= -240, ///< -240/0xFF10 a resource is too big
	eStNullPointer          = -241, ///< -241/0xFF0F a null pointer has been passed
#if 0
    //                                          
    // <p Device and Ioctl Status Codes>
    //
    eStDevWrongState        = -300, ///< -300/0xFED4 Current driver state does not support this function
    eStDevBusy              = -301, ///< -301/0xFED3 The device is busy
    eStDevRxOverrun         = -302, ///< -302/0xFED2 Overrun condition in device Rx Path
//    eStDevOpCancelled       = -303, ///< -303/0xFED1 Asynchronous I/O operation was manually cancelled
//    eStDevMediumChanged     = -304, ///< -304/0xFED0 Medium was changed, e.g. MMC card
    eStDevWrongConfig       = -305, ///< -305/0xFECF Configuration for the driver is wrong
    eStDevNoData            = -306, ///< -306/0xFECE No Data is available
    eStDevIOError           = -307, ///< -307/0xFECD General Device IO Error
//    eStDevOpFinished        = -308, ///< -308/0xFECC The operation has been finished
    eStDevCanNotOpen        = -309, ///< -309/0xFECB Can not open the device
    eStDevIsClosed          = -310, ///< -310/0xFECA Device is closed
    eStDevCantWrite         = -311, ///< -311/0xFEC9 Can't write to device
    eStDevCanNotClose       = -312, ///< -312/0xFEC8 Can not close the device
    eStDevCantRead          = -313, ///< -313/0xFEC7 Can not read the device
#endif
    //
    // <p Hardware related Status Codes>
    //
    eStHwDevCantReceive     = -400, ///< -400/0xFE70 Cannot receive data from device
	eStHwDevCantErase       = -401, ///< -401/0xFE6F Cannot erase data from device
	eStHwDevCantProgram     = -402, ///< -402/0xFE6E Cannot program data to device
#if 0
    eStHwNotFound           = -401, ///< -401/0xFE6F e.g. a driver could not identify/find its hardware
    eStHwNotAvailable       = -402, ///< -402/0xFE6E e.g. a driver request hardware already used by a diffrent driver
    eStHwMmuNotInit         = -403, ///< -403/0xFE6D MMU and Caches not initialized correct
    eStHwInvalidBaudrate    = -404, ///< -404/0xFE6C invalid Baudrate Setting
    eStHwRamFailure         = -405, ///< -405/0xFE6B SDRAM could not initialized
    eStHwPowerFail          = -406, ///< -406/0xFE6A PowerFail occured
    eStHwIncompatible       = -407, ///< -407/0xFE69 Incompatible Hardware detected
    eStHwInvalidParam       = -408, ///< -408/0xFE68 Invalid Parameter for Hardware Init detected
    eStHwNoAccess           = -409, ///< -409/0xFE67 No access to HW ressource
    eStHwThresholdExceeded  = -410, ///< -410/0xFE69 HW threshold has been exceeded
#endif
    //
    // <p Codes regarding file I/O>
    //
    eStFileNotFound         = -601, ///< -601/0xFDA7 File was not found
    eStFileProtected        = -602, ///< -602/0xFDA6 File was protected 
    eStFileCantOpen         = -603, ///< -603/0xFDA5 File could not opened
    eStFileCantRead         = -604, ///< -604/0xFDA4 File could not read
    eStFileCantWrite        = -605, ///< -605/0xFDA3 File could not write
    eStFileTooLarge         = -606, ///< -606/0xFDA2 File too large
    eStFileInvalidFormat    = -607, ///< -607/0xFDA1 File Format is Invalid
    eStFileNoLock           = -608, ///< -608/0xFDA0 File is not locked
    eStFileCantClose        = -609, ///< -609/0xFD9F File could not closed
    eStFileFormatDisk       = -610, ///< -610/0xFD9E File cannot format disk
    eStFileCantCopy         = -611, ///< -611/0xFD9D Cant copy file
    eStFileCantDelete       = -612, ///< -612/0xFD9C Cant delete file
    eStFileCantSetPos       = -613, ///< -613/0xFD9B Cant set position in file
    eStFileReference        = -614, ///< -614/0xFD9A File is still referenced
    eStFileOpenDisk         = -615, ///< -615/0xFD99 Can't open disk / No Valid Disk Present
    eStFileFileExists       = -616, ///< -616/0xFD98 Exclusive access requested but file already exists
    eStFileNoResource       = -617, ///< -617/0xFD97 No file descriptors or user tasks available (too many files open or tasks accessing FS
    eStFileNoSpace          = -618, ///< -618/0xFD96 Volume is full
    eStFileEofReached       = -619, ///< -619/0xFD95  End of file reached
    eStFileUnkownError      = -620, ///< -620/0xFD94 unkown FileApi error code
    eStFileOtherError       = -621, ///< -621/0xFD93 other file system error (but no further specifiation)
    eStFileInternalError    = -622, ///< -622/0xFD93 file system internal error
    eStDriveInvalid         = -623, ///< -623/0xFD92 invalid drive
    eStSourceFileCantOpen   = -624, ///< -624/0xFD91 Source file could not be opened
    eStDestFileCantOpen     = -625, ///< -625/0xFD90 Destination file could not be opened
    eStFileNotIdentical     = -626, ///< -626/0xFD8F Compared files are not identical
#if 0
    //
    // <p Codes regarding operating System>
    //	
    eStOSCantStartTask      = -700,
    //
    // Last Entry
    //
    eStLast                 = -9999 ///< Last entry, used for range checks
#endif
} teStatus;

#endif //TCSGLOBAL_STATUS_CODES_H_
