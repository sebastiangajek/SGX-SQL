/*
 * SgxVfsHandler.cpp
 *
 *  Created on: 04.03.2020
 *      Author: sgx
 */
#include <string.h>
#include <mutex>
#include <assert.h>
#include <random>
#include "sqlite3.h"

#include "../Enclave/Enclave_t.h"
#include "../Enclave/sqlite3.h"
#include "sgx_tprotected_fs.h"



// this function registers our custom VFS and return its name
std::string getSgxVfsName() {
    // a mutex protects the body of this function because we don't want to register the VFS twice
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);

    // check if the VFS is already registered, in this case we directly return
    static const char* vfsName = "sgx_vfs_handler";
    if (sqlite3_vfs_find(vfsName) != nullptr)
        return vfsName;

    // this is the structure that will store all the custom informations about an opened file
    // all the functions get in fact pointer to an sqlite3_file object
    // we give SQLite the size of this structure and SQLite will allocate it for us
    // 'xOpen' will have to call all the members' constructors (using placement-new), and 'xClose' will call all the destructors
    struct File : sqlite3_file {
        SGX_FILE* sgxData;         // pointer to the source stream
        int lockLevel;      // level of lock by SQLite ; goes from 0 (not locked) to 4 (exclusive lock)
    };

    // making sure that the 'sqlite3_file' structure is at offset 0 in the 'File' structure
    static_assert(offsetof(File, pMethods) == 0, "Wrong data alignment in custom SQLite3 VFS, lots of weird errors will happen during runtime");

    // structure which contains static functions that we are going to pass to SQLite
    // TODO: VC++2010 doesn't support lambda function treated as regular functions, or we would use this
    struct Functions {
        // opens a file by filling a sqlite3_file structure
        // the name of the file should be the offset in memory where to find a "std::shared_ptr<std::iostream>"
        // eg. you create a "std::shared_ptr<std::iostream>" whose memory location is 0x12345678
        //      you have to pass "12345678" as the file name
        // this function will make a copy of the shared_ptr and store it in the sqlite3_file
        static int xOpen(sqlite3_vfs*, const char* zName, sqlite3_file* fileBase, int flags, int *pOutFlags) {

            // filling a structure with a list of methods that will be used by SQLite3 for this particular file
            static sqlite3_io_methods methods;
            methods.iVersion = 1;
            methods.xClose = &xClose;
            methods.xRead = &xRead;
            methods.xWrite = &xWrite;
            methods.xTruncate = &xTruncate;
            methods.xSync = &xSync;
            methods.xFileSize = &xFileSize;
            methods.xLock = &xLock;
            methods.xUnlock = &xUnlock;
            methods.xCheckReservedLock = &xCheckReservedLock;
            methods.xFileControl = &xFileControl;
            methods.xSectorSize = &xSectorSize;
            methods.xDeviceCharacteristics = &xDeviceCharacteristics;
            fileBase->pMethods = &methods;
            return SQLITE_OK;
        }

        static int xClose(sqlite3_file* fileBase) {
            return SQLITE_OK;
        }

        static int xRead(sqlite3_file* fileBase, void* buffer, int quantity, sqlite3_int64 offset) {
            return SQLITE_OK;
        }

        static int xWrite(sqlite3_file* fileBase, const void* buffer, int quantity, sqlite3_int64 offset) {



        	return SQLITE_OK;
        }

        static int xTruncate(sqlite3_file* fileBase, sqlite3_int64 size) {
            return SQLITE_OK;
        }

        static int xSync(sqlite3_file* fileBase, int) {
        	return SQLITE_OK;
        }

        static int xFileSize(sqlite3_file* fileBase, sqlite3_int64* outputSize) {
        	return SQLITE_OK;
        }

        static int xLock(sqlite3_file* fileBase, int level) {
        	return SQLITE_OK;
        }

        static int xUnlock(sqlite3_file* fileBase, int level) {
        	return SQLITE_OK;
        }

        static int xCheckReservedLock(sqlite3_file* fileBase, int* pResOut) {
        	return SQLITE_OK;
        }

        static int xFileControl(sqlite3_file* fileBase, int op, void* pArg) {
        	return SQLITE_OK;
        }

        static int xSectorSize(sqlite3_file*) {
            // returns the size of a sector of the HDD,
            //   we just return a dummy value
            return 512;
        }

        static int xDeviceCharacteristics(sqlite3_file*) {
            return SQLITE_IOCAP_ATOMIC | SQLITE_IOCAP_SAFE_APPEND | SQLITE_IOCAP_SEQUENTIAL;
        }

        static int xDelete(sqlite3_vfs*, const char* zName, int syncDir) {
            return SQLITE_OK;
        }

        static int xAccess(sqlite3_vfs*, const char* zName, int flags, int* pResOut) {
            *pResOut = (strlen(zName) == sizeof(void*) * 2);
            return SQLITE_OK;
        }

        static int xFullPathname(sqlite3_vfs*, const char* zName, int nOut, char* zOut) {
            // this function turns a relative path into an absolute path
            // since our file names are just lexical_cast'ed pointers, we just strcpy
            // strcpy_s(zOut, nOut, zName);
            return SQLITE_OK;
        }

        static int xRandomness(sqlite3_vfs*, int nByte, char* zOut) {
            return SQLITE_OK;
        }

        static int xSleep(sqlite3_vfs*, int microseconds) {
            return SQLITE_OK;
        }

        static int xCurrentTime(sqlite3_vfs*, double* output) {
            // this function should return the number of days elapsed since
            //   "noon in Greenwich on November 24, 4714 B.C according to the proleptic Gregorian calendar"
            // I picked this constant from sqlite3.c which will make our life easier
            static const double unixEpoch = 2440587.5;

            //*output = unixEpoch + double(sgx_get_trusted_time(nullptr)) / (60.*60.*24.);
            return SQLITE_OK;
        }

        static int xCurrentTimeInt64(sqlite3_vfs*, sqlite3_int64* output) {
            // this function should return the number of milliseconds elapsed since
            //   "noon in Greenwich on November 24, 4714 B.C according to the proleptic Gregorian calendar"
            // I picked this constant from sqlite3.c which will make our life easier
            // note: I wonder if it is not hundredth of seconds instead
            static const sqlite3_int64 unixEpoch = 24405875 * sqlite3_int64(60*60*24*100);

            //*output = unixEpoch + sgx_get_trusted_time() * 1000;
            return SQLITE_OK;
        }

    };


    // creating the VFS structure
    // TODO: some functions are not implemented due to lack of documentation ; I'll have to read sqlite3.c to find out
    static sqlite3_vfs readStructure;
    memset(&readStructure, 0, sizeof(readStructure));
    readStructure.iVersion = 2;
    readStructure.szOsFile = sizeof(File);
    readStructure.mxPathname = 256;
    readStructure.zName = vfsName;
    readStructure.pAppData = nullptr;
    readStructure.xOpen = &Functions::xOpen;
    readStructure.xDelete = &Functions::xDelete;
    readStructure.xAccess = &Functions::xAccess;
    readStructure.xFullPathname = &Functions::xFullPathname;
    /*readStructure.xDlOpen = &Functions::xOpen;
    readStructure.xDlError = &Functions::xOpen;
    readStructure.xDlSym = &Functions::xOpen;
    readStructure.xDlClose = &Functions::xOpen;*/
    readStructure.xRandomness = &Functions::xRandomness;
    readStructure.xSleep = &Functions::xSleep;
    readStructure.xCurrentTime = &Functions::xCurrentTime;
    //readStructure.xGetLastError = &Functions::xOpen;
    readStructure.xCurrentTimeInt64 = &Functions::xCurrentTimeInt64;


    // the second parameter of this function tells if
    //   it should be made the default file system
    sqlite3_vfs_register(&readStructure, false);

    return vfsName;
}




