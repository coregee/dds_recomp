#ifndef NOCTURNE_BATTLE_RENDERER_INDEXED_CACHE_H
#define NOCTURNE_BATTLE_RENDERER_INDEXED_CACHE_H
#include <stdint.h>
/* Explicit chosen external state, not observations or an installed-PS2 claim.
 * profile1 follows pinned PCSX2 flags-only DXLTG; profile2 follows direct EE
 * defined fields/invalidation with explicit choices for undefined TagLo bits.
 * Ordinary flat RAM accesses
 * bypass this cache: they neither refill lines nor infer tags from RAM. */
#define NOCTURNE_INDEXED_CACHE_PCSX2_FLAGS_ONLY 1u
#define NOCTURNE_INDEXED_CACHE_EE_DEFINED_FIELDS 2u
#define NOCTURNE_INDEXED_CACHE_OK 0u
#define NOCTURNE_INDEXED_CACHE_INVALID 1u
#define NOCTURNE_INDEXED_CACHE_UNSUPPORTED 2u
#define NOCTURNE_INDEXED_CACHE_STALE 3u
typedef struct NocturneIndexedCacheLine {
 uint32_t physical_page,flags,physical_backed,reserved;
 uint8_t data[64];
} NocturneIndexedCacheLine;
typedef struct NocturneIndexedCacheConfig {
 /* EE profile's undefined TagLo bits are explicit chosen external state,
  * never claimed physical hardware output. Only mask0xF87 may be set. */
 uint32_t version,profile,physical_ram_base,physical_ram_bytes,taglo,taglo_undefined_bits,reserved[2];
 /* line index = set*2+way; set=(EA>>6)&63; indexed way=EA&1. */
 NocturneIndexedCacheLine lines[128];
} NocturneIndexedCacheConfig;
typedef struct NocturneIndexedCacheState {
 NocturneIndexedCacheConfig current;
 uint64_t generation;
} NocturneIndexedCacheState;
typedef struct NocturneIndexedCachePreview {
 uint32_t version,pc,operation,address;
 uint64_t generation;
 uint32_t line_index,has_line,taglo_before,taglo_after;
 NocturneIndexedCacheLine before,after;
 uint32_t writeback,writeback_address,writeback_bytes,reserved;
 uint8_t writeback_data[64];
} NocturneIndexedCachePreview;
_Static_assert(sizeof(NocturneIndexedCacheLine)==80,"indexed line80");
_Static_assert(sizeof(NocturneIndexedCacheConfig)==10272,"indexed config10272");
_Static_assert(sizeof(NocturneIndexedCacheState)==10280,"indexed state10280");
_Static_assert(sizeof(NocturneIndexedCachePreview)==280,"indexed preview280");
uint32_t nocturneIndexedCacheInit(NocturneIndexedCacheState *,const NocturneIndexedCacheConfig *);
uint32_t nocturneIndexedCachePreview(const NocturneIndexedCacheState *,uint32_t pc,uint32_t operation,uint32_t address,NocturneIndexedCachePreview *);
/* Pure state commit. Caller must preflight optional physical64B writeback and
 * all its own receipts before commit, then publish that exact effect once.
 * No CPU/FPR/VU, Status, primitive counter or guest RAM writes occur here. */
uint32_t nocturneIndexedCacheCommit(NocturneIndexedCacheState *,const NocturneIndexedCachePreview *);
uint32_t nocturneIndexedCacheReadTagLo(const NocturneIndexedCacheState *,uint32_t *);
#endif
