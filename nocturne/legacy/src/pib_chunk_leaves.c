#include "pib_chunk_leaves.h"
#include <string.h>

/* 001DEA60: LHU 12(A0) in the JR RA delay slot. Native semantic lead is
 * mdlEffect.mdlPibGetChunkCount, NOT pibChunk_t.GetSize (which returns 8). */
uint32_t mdlPibGetChunkCount(const void *header)
{
    uint16_t count;
    memcpy(&count, (const uint8_t *)header + 12, sizeof count);
    return count;
}
/* 001DEAE8: candidate is A0+8; compare its complete word with 0000FFFF.
 * The native version updates a managed data-position argument instead. */
void *mdlPibGetFirstChunkItem(void *chunk)
{
    uint8_t *candidate = (uint8_t *)chunk + 8;
    uint32_t marker;
    memcpy(&marker, candidate, sizeof marker);
    return marker == UINT32_C(0x0000ffff) ? NULL : candidate;
}
/* 001DEB00: read unsigned stride at +4, then inspect the complete target word.
 * A zero stride is observable and returns the same backed item unless sentinel.
 * Stride validity is a caller backing contract, not an extra original check. */
void *mdlPibGetNextChunkItem(void *item)
{
    uint32_t stride, marker;
    memcpy(&stride, (const uint8_t *)item + 4, sizeof stride);
    uint8_t *candidate = (uint8_t *)item + stride;
    memcpy(&marker, candidate, sizeof marker);
    return marker == UINT32_C(0x0000ffff) ? NULL : candidate;
}

static const uint8_t *resolve_original(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolvePibAddress(address);
#else
    return (const uint8_t *)(uintptr_t)address;
#endif
}
/* 001DEA68: optional PIB; actual count getter; advance before each group test.
 * Every traversed record must have readable words +0/+4, and each effective
 * address must be backed without 32-bit address wrap. The final exhausted-loop
 * advance is computed but not dereferenced. Return is the first matching group.
 * Original low32 group comparison is unsigned bit equality, not a clamp. */
void *mdlPibGetChunk(const void *handle,int32_t group)
{
    uint32_t model_address,pib_address,stride;
    memcpy(&model_address,(const uint8_t *)handle+12,sizeof model_address);
    const uint8_t *model=resolve_original(model_address);
    memcpy(&pib_address,model+0xa4,sizeof pib_address);
    if(pib_address==0)return NULL;
    const uint8_t *record=resolve_original(pib_address);
    uint32_t remaining=mdlPibGetChunkCount(record);
    memcpy(&stride,record+4,sizeof stride);
    for(;;) {
        uintptr_t next=(uintptr_t)record+stride;
        if(remaining==0)return NULL;
        --remaining;
        record=(const uint8_t *)next;
        uint32_t candidate;
        memcpy(&candidate,record,sizeof candidate);
        if(candidate==(uint32_t)group)return (void *)record;
        memcpy(&stride,record+4,sizeof stride);
    }
}
