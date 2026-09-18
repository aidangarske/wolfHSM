/*
 * Copyright (C) 2026 wolfSSL Inc.
 *
 * This file is part of wolfHSM.
 *
 * wolfHSM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * wolfHSM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with wolfHSM.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * test-refactor/client-server/wh_test_she_uid.c
 *
 * Client-side conformance checks for a server's SHE UID storage, aimed at
 * integrators who back the UID with fuses, OTP or NVM through the
 * whServerSheGetUidCb / whServerSheSetUidCb callbacks. Everything here is
 * observed over the wire, so the test makes no assumption about the UID value
 * or about which storage the server uses, and it can be pointed at a real
 * target running the integrator's port.
 *
 * The test never provisions a UID: it reports SKIPPED against a server that has
 * none, so it cannot consume the one-shot CMD_SET_UID that whTest_She needs.
 */

#include "wolfhsm/wh_settings.h"

#if defined(WOLFHSM_CFG_SHE_EXTENSION) && !defined(WOLFHSM_CFG_NO_CRYPTO) && \
    defined(WOLFHSM_CFG_ENABLE_CLIENT)

#include <stdint.h>
#include <string.h>

#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/wolfcrypt/types.h"

#include "wolfhsm/wh_common.h"
#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_utils.h"
#include "wolfhsm/wh_client.h"
#include "wolfhsm/wh_client_she.h"
#include "wolfhsm/wh_she_common.h"

#include "wh_test_common.h"
#include "wh_test_list.h"

#ifndef TEST_ADMIN_USERNAME
#define TEST_ADMIN_USERNAME "admin"
#endif
#ifndef TEST_ADMIN_PIN
#define TEST_ADMIN_PIN "1234"
#endif

/* Two distinct challenges, so a MAC that ignores the challenge is visible */
static const uint8_t s_challengeOne[WH_SHE_KEY_SZ] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

static const uint8_t s_challengeTwo[WH_SHE_KEY_SZ] = {
    0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78,
    0x87, 0x96, 0xA5, 0xB4, 0xC3, 0xD2, 0xE1, 0xF0};

/* UID this test offers to CMD_SET_UID. A provisioned server must refuse it. */
static const uint8_t s_rogueUid[WH_SHE_UID_SZ] = {
    0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A,
    0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};

/* One CMD_GET_ID round trip, returning the raw SHE return code. */
static int _GetId(whClientContext* client, const uint8_t* challenge,
                  uint8_t* uid, uint8_t* sreg, uint8_t* mac)
{
    uint8_t chal[WH_SHE_KEY_SZ];

    memcpy(chal, challenge, sizeof(chal));
    memset(uid, 0, WH_SHE_UID_SZ);
    memset(mac, 0, WH_SHE_KEY_SZ);
    *sreg = 0;

    return wh_Client_SheGetId(client, chal, sizeof(chal), uid, sreg, mac);
}

/*
 * The reported UID must not be all zeros. That is what the server writes when
 * a getter fails, and the SHE spec reads an all-zero UID in M1 as the wildcard,
 * so a getter that returns success without filling the buffer would silently
 * turn every key update into a wildcard update.
 */
static int _whTest_SheUidReported(whClientContext* client, uint8_t* refUid)
{
    uint8_t sreg;
    uint8_t mac[WH_SHE_KEY_SZ];

    WH_TEST_ASSERT_RETURN(_GetId(client, s_challengeOne, refUid, &sreg, mac) ==
                          WH_SHE_ERC_NO_ERROR);
    WH_TEST_ASSERT_RETURN(wh_Utils_memeqzero(refUid, WH_SHE_UID_SZ) == 0);

    WH_TEST_PRINT("SHE UID: reported by GET_ID SUCCESS\n");
    return WH_ERROR_OK;
}

/*
 * The getter must be idempotent: repeated reads return the same UID, and the
 * UID must not depend on the challenge. The MAC, by contrast, must change with
 * the challenge, which is what makes GET_ID a freshness proof rather than a
 * replayable constant.
 */
static int _whTest_SheUidStable(whClientContext* client, const uint8_t* refUid)
{
    uint8_t uid[WH_SHE_UID_SZ];
    uint8_t sregSame;
    uint8_t sregOther;
    uint8_t macFirst[WH_SHE_KEY_SZ];
    uint8_t macSame[WH_SHE_KEY_SZ];
    uint8_t macOther[WH_SHE_KEY_SZ];

    /* Same challenge twice: UID, SREG and MAC are all reproducible. */
    WH_TEST_ASSERT_RETURN(_GetId(client, s_challengeOne, uid, &sregSame,
                                 macFirst) == WH_SHE_ERC_NO_ERROR);
    WH_TEST_ASSERT_RETURN(memcmp(uid, refUid, WH_SHE_UID_SZ) == 0);

    WH_TEST_ASSERT_RETURN(_GetId(client, s_challengeOne, uid, &sregSame,
                                 macSame) == WH_SHE_ERC_NO_ERROR);
    WH_TEST_ASSERT_RETURN(memcmp(uid, refUid, WH_SHE_UID_SZ) == 0);
    WH_TEST_ASSERT_RETURN(memcmp(macSame, macFirst, WH_SHE_KEY_SZ) == 0);

    /* Different challenge: same UID and SREG, different MAC. */
    WH_TEST_ASSERT_RETURN(_GetId(client, s_challengeTwo, uid, &sregOther,
                                 macOther) == WH_SHE_ERC_NO_ERROR);
    WH_TEST_ASSERT_RETURN(memcmp(uid, refUid, WH_SHE_UID_SZ) == 0);
    WH_TEST_ASSERT_RETURN(sregOther == sregSame);
    WH_TEST_ASSERT_RETURN(memcmp(macOther, macFirst, WH_SHE_KEY_SZ) != 0);

    WH_TEST_PRINT("SHE UID: stable across reads SUCCESS\n");
    return WH_ERROR_OK;
}

/*
 * A provisioned UID is immutable. Whether the server keeps it in context, in a
 * writable store, or in fuses, a second CMD_SET_UID must be refused, and the
 * UID GET_ID reports afterwards must be untouched. A setter that overwrites a
 * fused or already-provisioned UID fails here.
 */
static int _whTest_SheUidImmutable(whClientContext* client,
                                   const uint8_t*   refUid)
{
    uint8_t uid[WH_SHE_UID_SZ];
    uint8_t sreg;
    uint8_t mac[WH_SHE_KEY_SZ];
    uint8_t rogue[WH_SHE_UID_SZ];
    int     rc;

    memcpy(rogue, s_rogueUid, sizeof(rogue));
    WH_TEST_ASSERT_RETURN(memcmp(rogue, refUid, WH_SHE_UID_SZ) != 0);

    /* SEQUENCE_ERROR from an already-provisioned store, WRITE_PROTECTED from a
     * read-only one. Anything else, success above all, is a defect. */
    rc = wh_Client_SheSetUid(client, rogue, sizeof(rogue));
    WH_TEST_ASSERT_RETURN(rc == WH_SHE_ERC_SEQUENCE_ERROR ||
                          rc == WH_SHE_ERC_WRITE_PROTECTED);

    WH_TEST_ASSERT_RETURN(_GetId(client, s_challengeOne, uid, &sreg, mac) ==
                          WH_SHE_ERC_NO_ERROR);
    WH_TEST_ASSERT_RETURN(memcmp(uid, refUid, WH_SHE_UID_SZ) == 0);

    WH_TEST_PRINT("SHE UID: immutable once provisioned SUCCESS\n");
    return WH_ERROR_OK;
}

/*
 * CMD_GET_STATUS is answered without consulting the UID store, and both
 * commands report the same status register. A server whose status path has
 * been wired through the UID store shows up as a mismatch or an error here.
 */
static int _whTest_SheUidStatus(whClientContext* client)
{
    uint8_t uid[WH_SHE_UID_SZ];
    uint8_t mac[WH_SHE_KEY_SZ];
    uint8_t getIdSreg;
    uint8_t statusSreg;

    WH_TEST_ASSERT_RETURN(wh_Client_SheGetStatus(client, &statusSreg) ==
                          WH_SHE_ERC_NO_ERROR);
    WH_TEST_ASSERT_RETURN(_GetId(client, s_challengeOne, uid, &getIdSreg,
                                 mac) == WH_SHE_ERC_NO_ERROR);
    WH_TEST_ASSERT_RETURN(getIdSreg == statusSreg);

    WH_TEST_PRINT("SHE UID: status agrees with GET_ID SUCCESS\n");
    return WH_ERROR_OK;
}

/*
 * Client-side SHE UID storage conformance. Runs against any server that has a
 * UID provisioned; reports SKIPPED against one that does not.
 */
int whTest_SheUidClient(whClientContext* client)
{
    uint8_t refUid[WH_SHE_UID_SZ];
    uint8_t sreg;
    uint8_t mac[WH_SHE_KEY_SZ];
    int     rc;
#ifdef WOLFHSM_CFG_ENABLE_AUTHENTICATION
    int authRc;
#endif

    if (client == NULL) {
        return WH_ERROR_BADARGS;
    }

#ifdef WOLFHSM_CFG_ENABLE_AUTHENTICATION
    WH_TEST_RETURN_ON_FAIL(wh_Client_AuthLogin(
        client, WH_AUTH_METHOD_PIN, TEST_ADMIN_USERNAME, TEST_ADMIN_PIN,
        strlen(TEST_ADMIN_PIN), &authRc, NULL));
#endif /* WOLFHSM_CFG_ENABLE_AUTHENTICATION */

    /* Probe before committing to the checks. GET_ID is exempt from the
     * secure-boot gate, so a provisioned UID is all it needs. */
    rc = _GetId(client, s_challengeOne, refUid, &sreg, mac);

    if (rc == WH_SHE_ERC_SEQUENCE_ERROR) {
        WH_TEST_PRINT("SHE UID: no UID provisioned on this server, skipping\n");
        return WH_TEST_SKIPPED;
    }
    if (rc == WH_SHE_ERC_MEMORY_FAILURE) {
        /* The server's UID getter reported a backend failure. A getter that
         * does not handle the NULL out buffer the state gate probes with
         * surfaces exactly this way. */
        WH_ERROR_PRINT("SHE UID: the server's UID store reported a failure\n");
        return WH_ERROR_ABORTED;
    }
    WH_TEST_ASSERT_RETURN(rc == WH_SHE_ERC_NO_ERROR);

    WH_TEST_RETURN_ON_FAIL(_whTest_SheUidReported(client, refUid));
    WH_TEST_RETURN_ON_FAIL(_whTest_SheUidStable(client, refUid));
    WH_TEST_RETURN_ON_FAIL(_whTest_SheUidImmutable(client, refUid));
    WH_TEST_RETURN_ON_FAIL(_whTest_SheUidStatus(client));

    WH_TEST_PRINT("SHE UID client conformance SUCCESS\n");
    return WH_ERROR_OK;
}

#endif /* WOLFHSM_CFG_SHE_EXTENSION && !WOLFHSM_CFG_NO_CRYPTO &&
        * WOLFHSM_CFG_ENABLE_CLIENT */
