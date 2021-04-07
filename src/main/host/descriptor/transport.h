/*
 * The Shadow Simulator
 * Copyright (c) 2010-2011, Rob Jansen
 * See LICENSE for licensing information
 */

#ifndef SHD_TRANSPORT_H_
#define SHD_TRANSPORT_H_

#include <glib.h>
#include <netinet/in.h>

#include "main/core/support/definitions.h"
#include "main/host/descriptor/descriptor.h"
#include "main/host/syscall_types.h"
#include "main/utility/utility.h"

typedef struct _Transport Transport;
typedef struct _TransportFunctionTable TransportFunctionTable;

typedef gssize (*TransportSendFunc)(Transport* transport, PluginVirtualPtr buffer, gsize nBytes,
                                    in_addr_t ip, in_port_t port);
typedef gssize (*TransportReceiveFunc)(Transport* transport, PluginVirtualPtr buffer, gsize nBytes,
                                       in_addr_t* ip, in_port_t* port);

struct _TransportFunctionTable {
    DescriptorCloseFunc close;
    DescriptorFreeFunc free;
    TransportSendFunc send;
    TransportReceiveFunc receive;
    MAGIC_DECLARE;
};

struct _Transport {
    LegacyDescriptor super;
    TransportFunctionTable* vtable;

    MAGIC_DECLARE;
};

void transport_init(Transport* transport, TransportFunctionTable* vtable,
                    LegacyDescriptorType type);

gssize transport_sendUserData(Transport* transport, PluginVirtualPtr buffer, gsize nBytes,
                              in_addr_t ip, in_port_t port);
gssize transport_receiveUserData(Transport* transport, PluginVirtualPtr buffer, gsize nBytes,
                                 in_addr_t* ip, in_port_t* port);

#endif /* SHD_TRANSPORT_H_ */
