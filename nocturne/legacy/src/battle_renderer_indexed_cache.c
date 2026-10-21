/* Source-derived CACHE-instruction value profile. Primary: PCSX2 Cache.cpp
 * b4d6e2aa7b9069162fa0e7cbc45ae95fc2566f39 (GPL-3.0+), explicit flags-only
 * DXLTG and indexed64x2 organization. Profile2 uses Sony EE Instruction Set
 * Manual v6 pp299/301/303 defined fields, with no physical timing claim.
 * No host cache/OS/emulator calls. */
#include "battle_renderer_indexed_cache.h"
#include <string.h>
static int config_valid(const NocturneIndexedCacheConfig *c)
{
 if(!c||c->version!=1u||(c->profile!=NOCTURNE_INDEXED_CACHE_PCSX2_FLAGS_ONLY&&c->profile!=NOCTURNE_INDEXED_CACHE_EE_DEFINED_FIELDS))return 0;
 if(c->reserved[0]||c->reserved[1]||(c->taglo_undefined_bits&~0xf87u))return 0;
 if(c->profile==NOCTURNE_INDEXED_CACHE_PCSX2_FLAGS_ONLY&&c->taglo_undefined_bits)return 0;
 if((c->physical_ram_base&63u)||(c->physical_ram_bytes&63u)||!c->physical_ram_bytes)return 0;
 if((uint64_t)c->physical_ram_base+c->physical_ram_bytes>UINT64_C(0x20000000))return 0;
 for(uint32_t i=0;i<128u;i++){
  const NocturneIndexedCacheLine *l=&c->lines[i];
  if((l->physical_page&4095u)||l->physical_page>=0x20000000u||(l->flags&~0x7ffu)||l->physical_backed>1u||l->reserved)return 0;
  if(c->profile==NOCTURNE_INDEXED_CACHE_EE_DEFINED_FIELDS&&(l->flags&~0x78u))return 0;
  if(l->physical_backed){
   uint32_t address=l->physical_page|((i>>1)<<6);
   if(address<c->physical_ram_base||(uint64_t)address+64u>(uint64_t)c->physical_ram_base+c->physical_ram_bytes)return 0;
  }
 }
 if(c->profile==NOCTURNE_INDEXED_CACHE_EE_DEFINED_FIELDS){
  for(uint32_t i=0;i<128u;i+=2u)
   if((c->lines[i].flags&0x20u)&&(c->lines[i+1u].flags&0x20u)&&c->lines[i].physical_page==c->lines[i+1u].physical_page)return 0;
 }
 return 1;
}
uint32_t nocturneIndexedCacheInit(NocturneIndexedCacheState *s,const NocturneIndexedCacheConfig *c)
{
 NocturneIndexedCacheState next;
 if(!s||!config_valid(c))return NOCTURNE_INDEXED_CACHE_INVALID;
 memset(&next,0,sizeof(next));next.current=*c;*s=next;return NOCTURNE_INDEXED_CACHE_OK;
}
static int physical(uint32_t address,uint32_t *out)
{
 if(address<0x20000000u){*out=address;return 1;}
 if(address>=0x80000000u&&address<0xc0000000u){*out=address&0x1fffffffu;return 1;}
 return 0; /* No invented TLB/MMIO or scratchpad translation. */
}
uint32_t nocturneIndexedCachePreview(const NocturneIndexedCacheState *s,uint32_t pc,uint32_t op,uint32_t address,NocturneIndexedCachePreview *out)
{
 NocturneIndexedCachePreview p;uint32_t index=((address>>6)&63u)*2u+(address&1u);
 if(!s||!out||!config_valid(&s->current)||s->generation==UINT64_MAX)return NOCTURNE_INDEXED_CACHE_INVALID;
 if(op!=0x10u&&op!=0x16u&&op!=0x18u)return NOCTURNE_INDEXED_CACHE_UNSUPPORTED;
 memset(&p,0,sizeof(p));p.version=1;p.pc=pc;p.operation=op;p.address=address;p.generation=s->generation;
 p.taglo_before=s->current.taglo;p.taglo_after=p.taglo_before;
 if(op==0x18u){
  uint32_t pa;
  if(!physical(address,&pa))return NOCTURNE_INDEXED_CACHE_UNSUPPORTED;
  if(s->current.profile==NOCTURNE_INDEXED_CACHE_EE_DEFINED_FIELDS){
   if(address>=0xa0000000u)return NOCTURNE_INDEXED_CACHE_UNSUPPORTED;
   if(pa<s->current.physical_ram_base||(uint64_t)pa>=(uint64_t)s->current.physical_ram_base+s->current.physical_ram_bytes)return NOCTURNE_INDEXED_CACHE_UNSUPPORTED;
  }
  index=((address>>6)&63u)*2u;
  if(!((s->current.lines[index].flags&0x20u)&&s->current.lines[index].physical_page==(pa&0xfffff000u))){
   ++index;
   if(!((s->current.lines[index].flags&0x20u)&&s->current.lines[index].physical_page==(pa&0xfffff000u))){*out=p;return NOCTURNE_INDEXED_CACHE_OK;}
  }
 }
 p.line_index=index;p.has_line=1;p.before=s->current.lines[index];p.after=p.before;
 if((op==0x10u&&s->current.profile==NOCTURNE_INDEXED_CACHE_PCSX2_FLAGS_ONLY)||op==0x18u){
  if((p.before.flags&0x60u)==0x60u){
   if(!p.before.physical_backed&&s->current.profile==NOCTURNE_INDEXED_CACHE_EE_DEFINED_FIELDS)return NOCTURNE_INDEXED_CACHE_UNSUPPORTED;
   if(p.before.physical_backed){
    p.writeback=1;p.writeback_address=p.before.physical_page|((index>>1)<<6);p.writeback_bytes=64;
    memcpy(p.writeback_data,p.before.data,64);
   }
   /* Invalid physical backing drops the data but still clears dirty, as in
    * pinned writeBackIfNeeded; it does not fabricate a RAM destination. */
   p.after.flags&=~0x40u;
  }
 }
 if(op==0x10u){
  if(s->current.profile==NOCTURNE_INDEXED_CACHE_PCSX2_FLAGS_ONLY)p.taglo_after=p.after.flags&0x7ffu;
  else p.taglo_after=p.after.physical_page|(p.after.flags&0x78u)|s->current.taglo_undefined_bits;
 }else if(s->current.profile==NOCTURNE_INDEXED_CACHE_PCSX2_FLAGS_ONLY){
  memset(&p.after,0,sizeof(p.after));p.after.flags=p.before.flags&0x10u;
 }else p.after.flags&=~0x68u; /* Direct EE CACHE contract: clear L/V/D only. */
 *out=p;return NOCTURNE_INDEXED_CACHE_OK;
}
uint32_t nocturneIndexedCacheCommit(NocturneIndexedCacheState *s,const NocturneIndexedCachePreview *p)
{
 NocturneIndexedCachePreview expected;uint32_t result;
 if(!s||!p)return NOCTURNE_INDEXED_CACHE_INVALID;
 if(p->generation!=s->generation)return NOCTURNE_INDEXED_CACHE_STALE;
 result=nocturneIndexedCachePreview(s,p->pc,p->operation,p->address,&expected);
 if(result!=NOCTURNE_INDEXED_CACHE_OK)return result;
 if(memcmp(&expected,p,sizeof(expected)))return NOCTURNE_INDEXED_CACHE_INVALID;
 if(p->has_line)s->current.lines[p->line_index]=p->after;
 s->current.taglo=p->taglo_after;++s->generation;return NOCTURNE_INDEXED_CACHE_OK;
}
uint32_t nocturneIndexedCacheReadTagLo(const NocturneIndexedCacheState *s,uint32_t *out)
{
 if(!s||!out||!config_valid(&s->current))return NOCTURNE_INDEXED_CACHE_INVALID;
 *out=s->current.taglo;return NOCTURNE_INDEXED_CACHE_OK;
}
