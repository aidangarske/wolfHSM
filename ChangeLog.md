# wolfHSM Release v1.5.0 (August 21, 2026)

Due to NDA restrictions, access to the Infineon, ST Micro, TI, and Renesas ports is limited. Please contact [support@wolfssl.com](mailto:support@wolfssl.com) for access.

## New Feature Additions
* Added non-blocking request/response client APIs for SHA, RNG, AES, RSA, ECC, and CMAC operations in https://github.com/wolfSSL/wolfHSM/pull/337, https://github.com/wolfSSL/wolfHSM/pull/344, https://github.com/wolfSSL/wolfHSM/pull/347, https://github.com/wolfSSL/wolfHSM/pull/351, https://github.com/wolfSSL/wolfHSM/pull/368, and https://github.com/wolfSSL/wolfHSM/pull/381
* Added ML-KEM (FIPS 203) support for key generation, encapsulation, and decapsulation with DMA variants in https://github.com/wolfSSL/wolfHSM/pull/336
* Added LMS and XMSS stateful hash-based signature support in https://github.com/wolfSSL/wolfHSM/pull/352
* Added SHA-3 support with blocking wolfCrypt and non-blocking native APIs in https://github.com/wolfSSL/wolfHSM/pull/384
* Added DMA support for AES-ECB, AES-CBC, and AES-CTR and reworked AES-GCM DMA handling in https://github.com/wolfSSL/wolfHSM/pull/282
* Added authentication manager with user login, per-user permissions, and NVM-backed credential storage in https://github.com/wolfSSL/wolfHSM/pull/270, https://github.com/wolfSSL/wolfHSM/pull/290, https://github.com/wolfSSL/wolfHSM/pull/382, and https://github.com/wolfSSL/wolfHSM/pull/386
* Added client response timeout support with optional expiration callback in https://github.com/wolfSSL/wolfHSM/pull/278
* Added STM32H5 TrustZone port with non-secure callable bridge transport in https://github.com/wolfSSL/wolfHSM/pull/348
* Added per-client wolfCrypt device IDs enabling multiple clients in a single process in https://github.com/wolfSSL/wolfHSM/pull/406
* Added client API to select hardware or software crypto processing at runtime in https://github.com/wolfSSL/wolfHSM/pull/281
* Added hardware-only key support allowing server operations to reference keys held in hardware in https://github.com/wolfSSL/wolfHSM/pull/409
* Added public key export for cached asymmetric keys, including returning the public key from cached key generation in https://github.com/wolfSSL/wolfHSM/pull/346 and https://github.com/wolfSSL/wolfHSM/pull/458
* Added cache-only shared secrets keeping ECDH and X25519 outputs server-resident in https://github.com/wolfSSL/wolfHSM/pull/372
* Added client API to generate and cache a random key on the server in https://github.com/wolfSSL/wolfHSM/pull/437
* Added multi-root CA certificate chain verification in https://github.com/wolfSSL/wolfHSM/pull/350
* Added trusted certificate cache and certificate verification callbacks in https://github.com/wolfSSL/wolfHSM/pull/353
* Added wolfBoot image verification to the image manager in https://github.com/wolfSSL/wolfHSM/pull/339
* Added global SHE key support enabling SHE key slots to be shared across all clients in https://github.com/wolfSSL/wolfHSM/pull/478
* Added SHE GET_ID command and key wrap interoperability with SHE keys in https://github.com/wolfSSL/wolfHSM/pull/450 and https://github.com/wolfSSL/wolfHSM/pull/413
* Added support for running the server without NVM using the key cache only in https://github.com/wolfSSL/wolfHSM/pull/392
* Added CRC integrity checking to the NVM flash backend in https://github.com/wolfSSL/wolfHSM/pull/503
* Added support for dynamically linking libwolfssl in https://github.com/wolfSSL/wolfHSM/pull/349

## Bug Fixes
* Bounded peer-controlled lengths in client and server transport receive paths in https://github.com/wolfSSL/wolfHSM/pull/388, https://github.com/wolfSSL/wolfHSM/pull/389, and https://github.com/wolfSSL/wolfHSM/pull/410
* Validated server-reported lengths and payload sizes in client crypto response handlers in https://github.com/wolfSSL/wolfHSM/pull/361, https://github.com/wolfSSL/wolfHSM/pull/366, https://github.com/wolfSSL/wolfHSM/pull/367, https://github.com/wolfSSL/wolfHSM/pull/373, https://github.com/wolfSSL/wolfHSM/pull/374, https://github.com/wolfSSL/wolfHSM/pull/375, https://github.com/wolfSSL/wolfHSM/pull/376, https://github.com/wolfSSL/wolfHSM/pull/463, https://github.com/wolfSSL/wolfHSM/pull/465, https://github.com/wolfSSL/wolfHSM/pull/467, https://github.com/wolfSSL/wolfHSM/pull/473, and https://github.com/wolfSSL/wolfHSM/pull/474
* Bounded AES, LMS, XMSS, and ML-KEM DMA response frames in the crypto client in https://github.com/wolfSSL/wolfHSM/pull/475 and https://github.com/wolfSSL/wolfHSM/pull/476
* Added request and response size validation to server request handlers, keystore, and crypto request translation in https://github.com/wolfSSL/wolfHSM/pull/299, https://github.com/wolfSSL/wolfHSM/pull/302, and https://github.com/wolfSSL/wolfHSM/pull/466
* Fixed key wrap request and response bounds, metadata trailer translation, and a data unwrap bug in https://github.com/wolfSSL/wolfHSM/pull/323, https://github.com/wolfSSL/wolfHSM/pull/359, https://github.com/wolfSSL/wolfHSM/pull/472, https://github.com/wolfSSL/wolfHSM/pull/494, and https://github.com/wolfSSL/wolfHSM/pull/510
* Added bounds checks to SHE client requests and responses and bounded SHE server key loads in https://github.com/wolfSSL/wolfHSM/pull/334, https://github.com/wolfSSL/wolfHSM/pull/457, and https://github.com/wolfSSL/wolfHSM/pull/495
* Fixed certificate handlers to validate inputs, check response lengths, capture verification results, and stop transmitting unwritten response bytes in https://github.com/wolfSSL/wolfHSM/pull/317, https://github.com/wolfSSL/wolfHSM/pull/365, https://github.com/wolfSSL/wolfHSM/pull/390, https://github.com/wolfSSL/wolfHSM/pull/426, and https://github.com/wolfSSL/wolfHSM/pull/459
* Fixed certificate verify message padding differences between clients and servers with different ABIs in https://github.com/wolfSSL/wolfHSM/pull/507
* Fixed client DMA address translation and a use-after-free in key, NVM, and certificate DMA operations in https://github.com/wolfSSL/wolfHSM/pull/403 and https://github.com/wolfSSL/wolfHSM/pull/408
* Fixed integer overflow in the DMA allow list boundary check, improved server DMA validation, and ensured DMA post-operation callbacks run on error paths in https://github.com/wolfSSL/wolfHSM/pull/298, https://github.com/wolfSSL/wolfHSM/pull/329, https://github.com/wolfSSL/wolfHSM/pull/324, and https://github.com/wolfSSL/wolfHSM/pull/340
* Fixed integer underflow in AES-GCM unwrap size calculations, missing AES context free on set-key failure, and AES-CTR bounds checking in https://github.com/wolfSSL/wolfHSM/pull/296, https://github.com/wolfSSL/wolfHSM/pull/306, https://github.com/wolfSSL/wolfHSM/pull/307, and https://github.com/wolfSSL/wolfHSM/pull/379
* Fixed overflow-prone bounds checks in NVM read handlers and 32-bit size_t overflow in AES and SHE size checks in https://github.com/wolfSSL/wolfHSM/pull/319 and https://github.com/wolfSSL/wolfHSM/pull/487
* Fixed SHE server secure boot chunk sizing, master ECU key metadata, constant-time comparison, and stack buffer zeroization in https://github.com/wolfSSL/wolfHSM/pull/293, https://github.com/wolfSSL/wolfHSM/pull/294, https://github.com/wolfSSL/wolfHSM/pull/310, https://github.com/wolfSSL/wolfHSM/pull/325, https://github.com/wolfSSL/wolfHSM/pull/326, and https://github.com/wolfSSL/wolfHSM/pull/332
* Fixed metadata label leak in key export error responses and stripped server-only flags from client metadata when caching random keys in https://github.com/wolfSSL/wolfHSM/pull/316 and https://github.com/wolfSSL/wolfHSM/pull/496
* Fixed NVM destroy batches aborting on absent IDs, NULL metadata handling in the checked add path, and committed state for keys read back from NVM in https://github.com/wolfSSL/wolfHSM/pull/461, https://github.com/wolfSSL/wolfHSM/pull/462, and https://github.com/wolfSSL/wolfHSM/pull/401
* Improved NVM locking across the crypto layer to prevent races on shared key caches in https://github.com/wolfSSL/wolfHSM/pull/438
* Fixed authentication manager to log out users on disconnect, enforce caller identity, refresh stale session permissions, and zeroize request messages in https://github.com/wolfSSL/wolfHSM/pull/383, https://github.com/wolfSSL/wolfHSM/pull/480, https://github.com/wolfSSL/wolfHSM/pull/481, and https://github.com/wolfSSL/wolfHSM/pull/432
* Guarded against clients connecting with aliased client IDs in https://github.com/wolfSSL/wolfHSM/pull/362
* Fixed SHA client response struct initialization, block-transfer error propagation, and SHA-512 finalize error overwrite in https://github.com/wolfSSL/wolfHSM/pull/308, https://github.com/wolfSSL/wolfHSM/pull/309, and https://github.com/wolfSSL/wolfHSM/pull/311
* Restored SHA-3 client state when the server cannot offload the operation in https://github.com/wolfSSL/wolfHSM/pull/455
* Fixed ML-DSA cache import buffer sizing, verify-only cache size checks, and compatibility with updated wolfCrypt APIs in https://github.com/wolfSSL/wolfHSM/pull/397, https://github.com/wolfSSL/wolfHSM/pull/452, and https://github.com/wolfSSL/wolfHSM/pull/301
* Fixed config path copy bounds, shared memory create TOCTOU, VERIFY_ACERT DMA error propagation, and KDF and AES-GCM response output bounds in https://github.com/wolfSSL/wolfHSM/pull/425
* Improved POSIX transport file permissions and descriptor handling, bounded shared memory mapping by the shared object size, and required peer certificates for TLS transport server mode in https://github.com/wolfSSL/wolfHSM/pull/322, https://github.com/wolfSSL/wolfHSM/pull/479, and https://github.com/wolfSSL/wolfHSM/pull/363
* Fixed off-by-one in constant-time zero compare, uint16 truncation, void pointer arithmetic, and transposed arguments in flash unit reads in https://github.com/wolfSSL/wolfHSM/pull/304, https://github.com/wolfSSL/wolfHSM/pull/314, https://github.com/wolfSSL/wolfHSM/pull/431, and https://github.com/wolfSSL/wolfHSM/pull/295

## Enhancements and Optimizations
* Overhauled the documentation and added user management invariants in https://github.com/wolfSSL/wolfHSM/pull/387 and https://github.com/wolfSSL/wolfHSM/pull/405
* Added CONTRIBUTING.md covering the contributor agreement and PR process in https://github.com/wolfSSL/wolfHSM/pull/509
* Added LMS, XMSS, ML-DSA, SHA-3, and HMAC-SHA3 benchmark modules and single round-trip ML-KEM timing in https://github.com/wolfSSL/wolfHSM/pull/454, https://github.com/wolfSSL/wolfHSM/pull/488, https://github.com/wolfSSL/wolfHSM/pull/499, https://github.com/wolfSSL/wolfHSM/pull/501, and https://github.com/wolfSSL/wolfHSM/pull/504
* Fixed SHA-2 benchmarks being skipped in non-DMA builds and reduced benchmark memory usage in https://github.com/wolfSSL/wolfHSM/pull/497, https://github.com/wolfSSL/wolfHSM/pull/456, and https://github.com/wolfSSL/wolfHSM/pull/514
* Reduced CI runtime with concurrency limits, ccache, draft PR filtering, and reorganized workflow matrices in https://github.com/wolfSSL/wolfHSM/pull/482, https://github.com/wolfSSL/wolfHSM/pull/483, https://github.com/wolfSSL/wolfHSM/pull/484, https://github.com/wolfSSL/wolfHSM/pull/485, and https://github.com/wolfSSL/wolfHSM/pull/489
* Added 32-bit CI job and automated coverage comparison in https://github.com/wolfSSL/wolfHSM/pull/491 and https://github.com/wolfSSL/wolfHSM/pull/490
* Migrated to the wc_MlDsaKey wolfCrypt API removing legacy Dilithium naming in https://github.com/wolfSSL/wolfHSM/pull/377
* Added ECC_MAKE_PUB and ECC_CHECK_PUB crypto callback support in https://github.com/wolfSSL/wolfHSM/pull/451
* Increased default key cache sizes for SHE, RSA, and ML-DSA use cases in https://github.com/wolfSSL/wolfHSM/pull/400 and https://github.com/wolfSSL/wolfHSM/pull/402
* Added test coverage for SHE loadable keys and secure boot, key usage policies, wrapped key restrictions, permission escalation, and DMA allow list boundaries in https://github.com/wolfSSL/wolfHSM/pull/335, https://github.com/wolfSSL/wolfHSM/pull/430, https://github.com/wolfSSL/wolfHSM/pull/380, https://github.com/wolfSSL/wolfHSM/pull/424, https://github.com/wolfSSL/wolfHSM/pull/470, and https://github.com/wolfSSL/wolfHSM/pull/500

# wolfHSM Release v1.4.0 (February 16, 2026)

Due to NDA restrictions, access to the Infineon, ST Micro, TI, and Renesas ports is limited. Please contact [support@wolfssl.com](mailto:support@wolfssl.com) for access.

## New Feature Additions
* Added TLS transport for authentication between client and server peers in https://github.com/wolfSSL/wolfHSM/pull/227
* Added global keystore enabling cryptographic keys to be shared across multiple clients with automatic cache routing in https://github.com/wolfSSL/wolfHSM/pull/224
* Added key usage policy flags (encrypt, decrypt, sign, verify, wrap, derive) set by clients and enforced by the server in https://github.com/wolfSSL/wolfHSM/pull/233
* Added server thread safety with NVM locking abstraction, enabling multiple server contexts to safely share NVM and global keystore resources in https://github.com/wolfSSL/wolfHSM/pull/275
* Added logging framework with callback-based backend, ring buffer, and POSIX file log engines in https://github.com/wolfSSL/wolfHSM/pull/253
* Added NVM object flag enforcement including non-destroyable flag and key revocation support in https://github.com/wolfSSL/wolfHSM/pull/263
* Added ED25519 signature scheme support with DMA in https://github.com/wolfSSL/wolfHSM/pull/254
* Added NIST SP 800-108 CMAC KDF support in https://github.com/wolfSSL/wolfHSM/pull/228
* Added generic data wrap/unwrap for server-side data wrapping in https://github.com/wolfSSL/wolfHSM/pull/226

## Bug Fixes
* Fixed potential DMA buffer handling errors where request buffer sizes were overwritten by server responses in https://github.com/wolfSSL/wolfHSM/pull/284
* Fixed potential buffer overflow in key cache by capping label size and corrected variable name logic error in `wh_Client_CommInfoResponse` in https://github.com/wolfSSL/wolfHSM/pull/234
* Fixed CMAC DMA message struct padding, alignment bugs in SHE code, and test key cache leaks in https://github.com/wolfSSL/wolfHSM/pull/285
* Fixed ECDH without DERIVE flag with `WOLF_CRYPTOCB_ONLY_ECC` in https://github.com/wolfSSL/wolfHSM/pull/251
* Fixed compilation with `NO_AES` defined and removed extra printfs in https://github.com/wolfSSL/wolfHSM/pull/260
* Fixed wrong `#endif` placement in `wh_client_crypto.c` and `#include` order in `nvm_flash_log.h` in https://github.com/wolfSSL/wolfHSM/pull/243
* Fixed SHE NVM metadata struct initialization so flags are set to 0 in https://github.com/wolfSSL/wolfHSM/pull/273
* Added NULL checks to message translation functions and additional input sanitization to server request handlers in https://github.com/wolfSSL/wolfHSM/pull/236 and https://github.com/wolfSSL/wolfHSM/pull/240

## Enhancements and Optimizations
* Refactored CMAC to use client-held state instead of persisting state on the server, and deprecated the cancellation API in https://github.com/wolfSSL/wolfHSM/pull/279
* Refactored debug macros to replace all printf usage with `WOLFHSM_CFG_PRINTF`-based wrappers in https://github.com/wolfSSL/wolfHSM/pull/207
* Expanded static memory DMA offset feature to CMAC, SHA-224, SHA-384, SHA-512, and ML-DSA in https://github.com/wolfSSL/wolfHSM/pull/191
* Changed wrap object size argument from input-only to in/out in https://github.com/wolfSSL/wolfHSM/pull/241
* Added scan-build static analysis GitHub Action in https://github.com/wolfSSL/wolfHSM/pull/195
* Added ECDSA cross-validation test with software implementation in https://github.com/wolfSSL/wolfHSM/pull/277

# wolfHSM Release v1.3.0 (October 24, 2025)

Due to NDA restrictions, access to the Infineon, ST Micro, TI, and Renesas ports is limited. Please contact [support@wolfssl.com](mailto:support@wolfssl.com) for access.

## New Feature Additions
* Introduced key wrap client/server APIs with demos and tests in https://github.com/wolfSSL/wolfHSM/pull/157 and https://github.com/wolfSSL/wolfHSM/pull/185
* Added HKDF key derivation with cached-key reuse support in https://github.com/wolfSSL/wolfHSM/pull/204 and https://github.com/wolfSSL/wolfHSM/pull/211
* Added image manager module for authenticated firmware handling in https://github.com/wolfSSL/wolfHSM/pull/129
* Added non-exportable object support and basic NVM access controls in https://github.com/wolfSSL/wolfHSM/pull/147
* Added flash-log based NVM backend for large write granularities in https://github.com/wolfSSL/wolfHSM/pull/179
* Added SHA-224/384/512 crypto support across client and server in https://github.com/wolfSSL/wolfHSM/pull/144
* Expanded DMA coverage to AES-GCM, RNG seeding, and shared-memory offset transfers in https://github.com/wolfSSL/wolfHSM/pull/158, https://github.com/wolfSSL/wolfHSM/pull/213, and https://github.com/wolfSSL/wolfHSM/commit/36862ce7e6829c3f996345cad880fdfe516d751f

## Bug Fixes
* Enforced NVM object boundaries during reads in https://github.com/wolfSSL/wolfHSM/pull/182
* Prevented stale data reads from erased flash pages in https://github.com/wolfSSL/wolfHSM/pull/181
* Corrected NVM flash state handling when recovery is required in https://github.com/wolfSSL/wolfHSM/pull/175
* Fixed AES-CTR temporary buffer sizing in https://github.com/wolfSSL/wolfHSM/pull/183
* Restored AES-GCM DMA post-write callbacks and optional output handling in https://github.com/wolfSSL/wolfHSM/pull/215 and https://github.com/wolfSSL/wolfHSM/pull/221
* Fixed POSIX TCP socket error handling in https://github.com/wolfSSL/wolfHSM/pull/203

## Enhancements and Optimizations
* Added GitHub Action based code coverage reporting in https://github.com/wolfSSL/wolfHSM/pull/201
* Added clang-format and clang-tidy automation in https://github.com/wolfSSL/wolfHSM/pull/176 and https://github.com/wolfSSL/wolfHSM/pull/167
* Added ASAN configuration to example builds and CI workflows in https://github.com/wolfSSL/wolfHSM/pull/218
* Improved benchmark tooling and shared memory transport configurability in https://github.com/wolfSSL/wolfHSM/pull/158

# wolfHSM Release v1.2.0 (June 27, 2025)

Due to NDA restrictions, access to the Infineon, ST Micro, and Renesas ports is limited. Please contact [support@wolfssl.com](mailto:support@wolfssl.com) for access.

## New Feature Additions
* Basic X509 certificate support in https://github.com/wolfSSL/wolfHSM/pull/96
* DMA support for CMAC in https://github.com/wolfSSL/wolfHSM/pull/97
* attribute certificate support in https://github.com/wolfSSL/wolfHSM/pull/101
* Add benchmark framework in https://github.com/wolfSSL/wolfHSM/pull/107
* client/server-only builds + relocate examples in https://github.com/wolfSSL/wolfHSM/pull/122

## Bug Fixes
* Fix flashunit program in https://github.com/wolfSSL/wolfHSM/pull/104
* Keycache test fixes in https://github.com/wolfSSL/wolfHSM/pull/125

## Enhancements and Optimizations
* Refactor DMA API to be generic across all address sizes in https://github.com/wolfSSL/wolfHSM/pull/102
* Remove whPacket union in https://github.com/wolfSSL/wolfHSM/pull/103
* set RNG on curve25519 keys to support blinding in https://github.com/wolfSSL/wolfHSM/pull/109
* new x509 API: verify and cache pubKey in https://github.com/wolfSSL/wolfHSM/pull/110
* Add hierarchical makefiles in https://github.com/wolfSSL/wolfHSM/pull/124

# wolfHSM Release v1.1.0 (January 23, 2025)
Due to NDA restrictions, access to the Infineon and ST Micro ports is limited. Please contact support@wolfssl.com for access.

## New Feature Additions
* Added support for ML-DSA (PR#84 and PR#86)
* Added support for DMA-based keystore operations (PR#85)

## Bug Fixes
* Fixes memory error in ECC verify (PR#81)
* Removes unused argument warnings on 32 bit targets (PR#82)
* Fixes memory leak in SHE test (PR#88)

## Enhancements and Optimizations
* Improved handling of Curve25519 DER encoded keys using new wolfCrypt APIs (PR#83)


# wolfHSM Release v1.0.1 (October 21, 2024)
Bug-fix release. Due to NDA restrictions, access to the Infineon and ST Micro ports is limited. Please contact support@wolfssl.com for access.

## New Feature Additions
* Initial release of whnvmtool to pre-build NVM images (PR#77)

## Bug Fixes
* Corrected FreshenKey server function to load keys from NVM when not in cache (PR#78)

## Enhancements and Optimizations
* Updated RSA key handling to support private-only and public-only keys (PR#76)


# wolfHSM Release v1.0.0 (October 17, 2024)
Initial release after internal and early evaluator testing. Due to NDA restrictions, access to the Infineon and ST Micro ports is limited. Please contact support@wolfssl.com for access.

## New Feature Additions
* POSIX simulator and test environment
* Memory fencing and cache controls for memory transport
* Support for Aurix Tricore TC3xx and ST SPC58NN
* DMA support for SHA2 and NVM objects
* Cancellation for CMAC
* Support NO_MALLOC and STATIC_MEMORY
* SHE+ interface

## Enhancements and Optimizations
* Reduction in static server memory requirements
* Hardware offload for AURIX and ST C3 modules
