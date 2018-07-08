/**
 * @file es.h
 * @brief ETicket service IPC wrapper.
 * @author Rei
 * @copyright libnx Authors
 */
#pragma once
#include "../types.h"
#include "../services/sm.h"

Result esInitialize(void);
void esExit(void);

Result esImportTicket(u8 *ticket, size_t tikSize, u8 *cert, size_t certSize);
Result esImportCertSet(u8 *set, size_t setSize);