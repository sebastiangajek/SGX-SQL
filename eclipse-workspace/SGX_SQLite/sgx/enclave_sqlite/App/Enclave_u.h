#ifndef ENCLAVE_U_H__
#define ENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */

#include "../ocall_types.h"
#include "sgx_tprotected_fs.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OCALL_PRINTLN_STRING_DEFINED__
#define OCALL_PRINTLN_STRING_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_println_string, (const char* str));
#endif
#ifndef OCALL_PRINT_STRING_DEFINED__
#define OCALL_PRINT_STRING_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* str));
#endif
#ifndef OCALL_PRINT_ERROR_DEFINED__
#define OCALL_PRINT_ERROR_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_error, (const char* str));
#endif
#ifndef OCALL_LSTAT_DEFINED__
#define OCALL_LSTAT_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_lstat, (const char* path, struct stat* buf, size_t size));
#endif
#ifndef OCALL_STAT_DEFINED__
#define OCALL_STAT_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_stat, (const char* path, struct stat* buf, size_t size));
#endif
#ifndef OCALL_FSTAT_DEFINED__
#define OCALL_FSTAT_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fstat, (int fd, struct stat* buf, size_t size));
#endif
#ifndef OCALL_FTRUNCATE_DEFINED__
#define OCALL_FTRUNCATE_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_ftruncate, (int fd, off_t length));
#endif
#ifndef OCALL_GETCWD_DEFINED__
#define OCALL_GETCWD_DEFINED__
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getcwd, (char* buf, size_t size));
#endif
#ifndef OCALL_GETPID_DEFINED__
#define OCALL_GETPID_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getpid, (void));
#endif
#ifndef OCALL_GETUID_DEFINED__
#define OCALL_GETUID_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getuid, (void));
#endif
#ifndef OCALL_GETENV_DEFINED__
#define OCALL_GETENV_DEFINED__
char* SGX_UBRIDGE(SGX_NOCONVENTION, ocall_getenv, (const char* name));
#endif
#ifndef OCALL_OPEN64_DEFINED__
#define OCALL_OPEN64_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_open64, (const char* filename, int flags, mode_t mode));
#endif
#ifndef OCALL_CLOSE_DEFINED__
#define OCALL_CLOSE_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_close, (int fd));
#endif
#ifndef OCALL_LSEEK64_DEFINED__
#define OCALL_LSEEK64_DEFINED__
off_t SGX_UBRIDGE(SGX_NOCONVENTION, ocall_lseek64, (int fd, off_t offset, int whence));
#endif
#ifndef OCALL_READ_DEFINED__
#define OCALL_READ_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_read, (int fd, void* buf, size_t count));
#endif
#ifndef OCALL_WRITE_DEFINED__
#define OCALL_WRITE_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_write, (int fd, const void* buf, size_t count));
#endif
#ifndef OCALL_FSYNC_DEFINED__
#define OCALL_FSYNC_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fsync, (int fd));
#endif
#ifndef OCALL_FCNTL_DEFINED__
#define OCALL_FCNTL_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fcntl, (int fd, int cmd, void* arg, size_t size));
#endif
#ifndef OCALL_UNLINK_DEFINED__
#define OCALL_UNLINK_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_unlink, (const char* pathname));
#endif
#ifndef SGX_OC_CPUIDEX_DEFINED__
#define SGX_OC_CPUIDEX_DEFINED__
void SGX_UBRIDGE(SGX_CDECL, sgx_oc_cpuidex, (int cpuinfo[4], int leaf, int subleaf));
#endif
#ifndef SGX_THREAD_WAIT_UNTRUSTED_EVENT_OCALL_DEFINED__
#define SGX_THREAD_WAIT_UNTRUSTED_EVENT_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_wait_untrusted_event_ocall, (const void* self));
#endif
#ifndef SGX_THREAD_SET_UNTRUSTED_EVENT_OCALL_DEFINED__
#define SGX_THREAD_SET_UNTRUSTED_EVENT_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_untrusted_event_ocall, (const void* waiter));
#endif
#ifndef SGX_THREAD_SETWAIT_UNTRUSTED_EVENTS_OCALL_DEFINED__
#define SGX_THREAD_SETWAIT_UNTRUSTED_EVENTS_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_setwait_untrusted_events_ocall, (const void* waiter, const void* self));
#endif
#ifndef SGX_THREAD_SET_MULTIPLE_UNTRUSTED_EVENTS_OCALL_DEFINED__
#define SGX_THREAD_SET_MULTIPLE_UNTRUSTED_EVENTS_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_multiple_untrusted_events_ocall, (const void** waiters, size_t total));
#endif
#ifndef U_SGXPROTECTEDFS_EXCLUSIVE_FILE_OPEN_DEFINED__
#define U_SGXPROTECTEDFS_EXCLUSIVE_FILE_OPEN_DEFINED__
void* SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_exclusive_file_open, (const char* filename, uint8_t read_only, int64_t* file_size, int32_t* error_code));
#endif
#ifndef U_SGXPROTECTEDFS_CHECK_IF_FILE_EXISTS_DEFINED__
#define U_SGXPROTECTEDFS_CHECK_IF_FILE_EXISTS_DEFINED__
uint8_t SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_check_if_file_exists, (const char* filename));
#endif
#ifndef U_SGXPROTECTEDFS_FREAD_NODE_DEFINED__
#define U_SGXPROTECTEDFS_FREAD_NODE_DEFINED__
int32_t SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_fread_node, (void* f, uint64_t node_number, uint8_t* buffer, uint32_t node_size));
#endif
#ifndef U_SGXPROTECTEDFS_FWRITE_NODE_DEFINED__
#define U_SGXPROTECTEDFS_FWRITE_NODE_DEFINED__
int32_t SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_fwrite_node, (void* f, uint64_t node_number, uint8_t* buffer, uint32_t node_size));
#endif
#ifndef U_SGXPROTECTEDFS_FCLOSE_DEFINED__
#define U_SGXPROTECTEDFS_FCLOSE_DEFINED__
int32_t SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_fclose, (void* f));
#endif
#ifndef U_SGXPROTECTEDFS_FFLUSH_DEFINED__
#define U_SGXPROTECTEDFS_FFLUSH_DEFINED__
uint8_t SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_fflush, (void* f));
#endif
#ifndef U_SGXPROTECTEDFS_REMOVE_DEFINED__
#define U_SGXPROTECTEDFS_REMOVE_DEFINED__
int32_t SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_remove, (const char* filename));
#endif
#ifndef U_SGXPROTECTEDFS_RECOVERY_FILE_OPEN_DEFINED__
#define U_SGXPROTECTEDFS_RECOVERY_FILE_OPEN_DEFINED__
void* SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_recovery_file_open, (const char* filename));
#endif
#ifndef U_SGXPROTECTEDFS_FWRITE_RECOVERY_NODE_DEFINED__
#define U_SGXPROTECTEDFS_FWRITE_RECOVERY_NODE_DEFINED__
uint8_t SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_fwrite_recovery_node, (void* f, uint8_t* data, uint32_t data_length));
#endif
#ifndef U_SGXPROTECTEDFS_DO_FILE_RECOVERY_DEFINED__
#define U_SGXPROTECTEDFS_DO_FILE_RECOVERY_DEFINED__
int32_t SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxprotectedfs_do_file_recovery, (const char* filename, const char* recovery_filename, uint32_t node_size));
#endif

sgx_status_t ecall_opendb(sgx_enclave_id_t eid, const char* dbname);
sgx_status_t ecall_execute_sql(sgx_enclave_id_t eid, const char* sql);
sgx_status_t ecall_closedb(sgx_enclave_id_t eid);
sgx_status_t ecall_fopen(sgx_enclave_id_t eid, SGX_FILE** retval, const char* filename, const char* mode);
sgx_status_t ecall_fwrite(sgx_enclave_id_t eid, size_t* retval, SGX_FILE* fp, char data[100]);
sgx_status_t ecall_fsize(sgx_enclave_id_t eid, uint64_t* retval, SGX_FILE* fp);
sgx_status_t ecall_fread(sgx_enclave_id_t eid, size_t* retval, SGX_FILE* fp, char* readData, uint64_t size);
sgx_status_t ecall_fclose(sgx_enclave_id_t eid, int32_t* retval, SGX_FILE* fp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif