#ifndef NOCTURNE_IOP_RPC_LAYOUT_H
#define NOCTURNE_IOP_RPC_LAYOUT_H
#include <stdint.h>
#include <stddef.h>
/* Original IOP wire/data layouts. Addresses remain 32-bit guest values, so
 * these definitions are also usable by a 64-bit analysis host. Corroborated
 * against original copy/consumer instructions and pinned sifrpc-common.h.
 * A call packet core is 56 bytes; the observed transport slot is 64 bytes. */
typedef struct {
 uint32_t size_word,destination,command,option;
} NocturneIopRpcCommandHeader;
typedef struct {
 NocturneIopRpcCommandHeader header;
 uint32_t rec_id,pkt_addr,rpc_id,client,rpc_number,send_size;
 uint32_t recvbuf,recv_size,rmode,server;
} NocturneIopRpcCallPacket;
typedef struct {
 uint32_t sid,func,buf,size,cfunc,cbuf,size2;
 uint32_t client,pkt_addr,rpc_number,recvbuf,rsize,rmode,rid;
 uint32_t link,next,base;
} NocturneIopRpcServer;
typedef struct {
 uint32_t thread_id,active,link,start,end,next;
} NocturneIopRpcQueue;
typedef struct {
 uint32_t pkt_addr,rpc_id,sema_id,mode,command,buf,cbuf;
 uint32_t end_function,end_param,server;
} NocturneIopRpcClient;
_Static_assert(sizeof(NocturneIopRpcCallPacket)==56,"IOP call core");
_Static_assert(offsetof(NocturneIopRpcCallPacket,rpc_number)==0x20,"RPC operation");
_Static_assert(offsetof(NocturneIopRpcCallPacket,send_size)==0x24,"RPC send size");
_Static_assert(sizeof(NocturneIopRpcServer)==68,"IOP server core");
_Static_assert(offsetof(NocturneIopRpcServer,client)==0x1c,"RPC client");
_Static_assert(offsetof(NocturneIopRpcServer,rpc_number)==0x24,"Server operation");
_Static_assert(offsetof(NocturneIopRpcServer,next)==0x3c,"Pending request link");
_Static_assert(offsetof(NocturneIopRpcServer,base)==0x40,"RPC queue");
_Static_assert(sizeof(NocturneIopRpcQueue)==24,"IOP RPC queue");
_Static_assert(sizeof(NocturneIopRpcClient)==40,"IOP RPC client core");
#endif
