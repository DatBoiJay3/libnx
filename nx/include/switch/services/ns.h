/**
 * @file ns.h
 * @brief NS service IPC wrapper.
 * @author yellows8
 * @copyright libnx Authors
 */
#pragma once
#include "../types.h"
#include "../nacp.h"
#include "../services/fs.h"

typedef struct {
    NacpStruct nacp;
    u8 icon[0x20000];//JPEG
} NsApplicationControlData;

Result nsInitialize(void);
void nsExit(void);

Result nsListApplicationRecord(u8 *out, u64 offset);
Result nsGenerateApplicationRecordCount(u32 *out);
Result nsDeleteApplicationCompletely(u64 titleID);
Result nsIsAnyApplicationEntityRedundant(bool *hasRedundancy);
Result nsDeleteRedundantApplicationEntity();
Result nsPushApplicationRecord(u64 tid, u64 num, u8 *apprec);
Result nsIsSystemProgramInstalled(u32 *out, u64 tid);
Result nsIsGameCardInserted(u8 *out);
Result nsBeginInstallApplication(u64 tid, u32 unk, u8 storageId);
Result nsDeleteApplicationRecord(u64 num);
Result nsGetApplicationControlData(u8 flag, u64 titleID, NsApplicationControlData* buffer, size_t size, size_t* actual_size);
Result nsCleanupUnrecordedApplicationEntity(Handle hand);


/**
 * @brief Returns the total storage capacity (used + free) from content manager services.
 * @param storage_id Specified FsStorageId. (Must be FsStorageId_SdCard)
 * @param size Pointer to output the total storage size to.
 */
Result nsGetTotalSpaceSize(FsStorageId storage_id, u64 *size);

/**
 * @brief Returns the available storage capacity from content manager services.
 * @param storage_id Specified FsStorageId. (Must be FsStorageId_SdCard)
 * @param size Pointer to output the free storage size to.
 */
Result nsGetFreeSpaceSize(FsStorageId storage_id, u64 *size);

Result nsvmInitialize(void);
void nsvmExit(void);

Result nsvmNeedsUpdateVulnerability(bool *out);
Result nsvmGetSafeSystemVersion(u16 *out);
