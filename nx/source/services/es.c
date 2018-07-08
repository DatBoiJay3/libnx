#include "types.h"
#include "result.h"
#include "arm/atomics.h"
#include "kernel/ipc.h"
#include "kernel/detect.h"
#include "services/sm.h"
#include "services/es.h"

static Service g_esAppManSrv;
static u64 g_esRefCnt;

Result esInitialize(void)
{
    Result rc=0;

    atomicIncrement64(&g_esRefCnt);

    if (serviceIsActive(&g_esAppManSrv))
        return 0;

    rc = smGetService(&g_esAppManSrv, "es");
    
    if (R_FAILED(rc)) serviceClose(&g_esAppManSrv);

    return rc;
}

void esExit(void)
{
    if (atomicDecrement64(&g_esRefCnt) == 0) {
        serviceClose(&g_esAppManSrv);
        if(!kernelAbove300()) return;
    }
}

Result esImportTicket(u8 *ticket, size_t tikSize, u8 *cert, size_t certSize) {
    IpcCommand c;
    ipcInitialize(&c);
    ipcAddSendBuffer(&c, ticket, tikSize, 0);
    ipcAddSendBuffer(&c, cert, certSize, 0);

    struct {
        u64 magic;
        u64 cmd_id;
    } *raw;

    raw = ipcPrepareHeader(&c, sizeof(*raw));

    raw->magic = SFCI_MAGIC;
    raw->cmd_id = 1;

    Result rc = serviceIpcDispatch(&g_esAppManSrv);

    if (R_SUCCEEDED(rc)) {
        IpcParsedCommand r;
        ipcParse(&r);

        struct {
            u64 magic;
            u64 result;
        } *resp = r.Raw;

        rc = resp->result;
    }

    return rc;
}

Result esImportCertSet(u8 *set, size_t setSize) {
    IpcCommand c;
    ipcInitialize(&c);
    ipcAddSendBuffer(&c, set, setSize, 0);

    struct {
        u64 magic;
        u64 cmd_id;
    } *raw;

    raw = ipcPrepareHeader(&c, sizeof(*raw));

    raw->magic = SFCI_MAGIC;
    raw->cmd_id = 2;

    Result rc = serviceIpcDispatch(&g_esAppManSrv);

    if (R_SUCCEEDED(rc)) {
        IpcParsedCommand r;
        ipcParse(&r);

        struct {
            u64 magic;
            u64 result;
        } *resp = r.Raw;

        rc = resp->result;
    }

    return rc;
}