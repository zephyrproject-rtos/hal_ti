/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "includes.h"

#include "common.h"
#include "eloop.h"
#include "l2_packet.h"
#include "drv_ti_internal.h"




struct l2_packet_data {
	char ifname[17];
	u8 own_addr[ETH_ALEN];
	void (*rx_callback)(void *ctx, const u8 *src_addr,
			    const u8 *buf, size_t len);
	void *rx_callback_ctx;
	int l2_hdr; /* whether to include layer 2 (Ethernet) header data
		     * buffers */
	int fd;

	// ti driver specific
	ti_driver_ifData_t *pDrv; //pointer to driver data ctx
};


int l2_packet_get_own_addr(struct l2_packet_data *l2, u8 *addr)
{
	os_memcpy(addr, l2->own_addr, ETH_ALEN);
	return 0;
}


int l2_packet_send(struct l2_packet_data *l2, const u8 *dst_addr, u16 proto,
		   const u8 *buf, size_t len)
{
    int ret;

	if (l2 == NULL)
		return -1;

	if (l2->l2_hdr)
	    return -1;

	ret = ti_driver_send_l2_data(l2->pDrv, dst_addr, proto, buf, len);


	if (0 == ret)
	{
	    ret = len; // return the number of bytes sent
	}

	return ret;
}

// TODO: for now, receive path is not implemented. Receive is performed via the wpa_supplicant_event() called
// by the driver.
// Future: In order to send packets to supplicant via this socket, our cc33xx driver should save the l2 struct in its
// context (or a linked list of structs per protocol), and forward the relevant packet according to the protocol.
#if 0
static void l2_packet_receive(int sock, void *eloop_ctx, void *sock_ctx)
{
	struct l2_packet_data *l2 = eloop_ctx;
	u8 buf[2300];
	int res;

	/* TODO: receive frame (e.g., recv() using sock */
	buf[0] = 0;
	res = 0;

	l2->rx_callback(l2->rx_callback_ctx, NULL /* TODO: src addr */,
			buf, res);
}
#endif

struct l2_packet_data * l2_packet_init(
	const char *ifname, const u8 *own_addr, unsigned short protocol,
	void (*rx_callback)(void *ctx, const u8 *src_addr,
			    const u8 *buf, size_t len),
	void *rx_callback_ctx, int l2_hdr)
{
	struct l2_packet_data *l2;
	ti_driver_ifData_t *pDrv;

	if (l2_hdr)
	{
	    wpa_printf(MSG_DEBUG, "%s: Raw Packet not supported in cc33xx",__func__);
	    ASSERT_GENERAL(FALSE);
	    return NULL;
	}
	pDrv = drv_getDriverData(ifname);

	if (!pDrv)
	    return NULL;


    l2 = os_zalloc(sizeof(struct l2_packet_data));

	if (l2 == NULL)
		return NULL;

	os_strlcpy(l2->ifname, ifname, sizeof(l2->ifname));
	l2->rx_callback = rx_callback;
	l2->rx_callback_ctx = rx_callback_ctx;
	l2->l2_hdr = l2_hdr;

	os_memcpy(l2->own_addr, own_addr, ETH_ALEN);
	l2->pDrv = pDrv;

	// TODO: for now, receive path is not implemented. Receive is performed via the wpa_supplicant_event() called
	// by the driver.
	// Future: In order to send packets to supplicant via this socket, our cc33xx driver should save the l2 struct in its
	// context (or a linked list of structs per protocol), and forward the relevant packet according to the protocol.

#if 0
	/*
	 * TODO: open connection for receiving frames
	 */
	l2->fd = -1;
	if (l2->fd >= 0)
		eloop_register_read_sock(l2->fd, l2_packet_receive, l2, NULL);
#endif

	return l2;// TI - cc33xx compilation
}


struct l2_packet_data * l2_packet_init_bridge(
	const char *br_ifname, const char *ifname, const u8 *own_addr,
	unsigned short protocol,
	void (*rx_callback)(void *ctx, const u8 *src_addr,
			    const u8 *buf, size_t len),
	void *rx_callback_ctx, int l2_hdr)
{
	return l2_packet_init(br_ifname, own_addr, protocol, rx_callback,
			      rx_callback_ctx, l2_hdr);
}


void l2_packet_deinit(struct l2_packet_data *l2)
{
	if (l2 == NULL)
		return;

#if 0
	if (l2->fd >= 0) {
		eloop_unregister_read_sock(l2->fd);
		/* TODO: close connection */
	}
#endif
		
	os_free(l2);
}


int l2_packet_get_ip_addr(struct l2_packet_data *l2, char *buf, size_t len)
{
	/* TODO: get interface IP address */
	return -1;
}


void l2_packet_notify_auth_start(struct l2_packet_data *l2)
{
	/* This function can be left empty */
}


int l2_packet_set_packet_filter(struct l2_packet_data *l2,
				enum l2_packet_filter_type type)
{
	return -1;
}
