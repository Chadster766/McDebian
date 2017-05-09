/*
 * Copyright (C) 2006-2017, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modify this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.
 *
 * THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

/* Description:  This file defines device related information. */

#ifndef _DEV_H_
#define _DEV_H_

#include <linux/version.h>
#include <linux/interrupt.h>
#include <linux/pci.h>
#include <linux/firmware.h>
#include <linux/delay.h>
#include <linux/bitops.h>
#include <net/mac80211.h>

#define PCIE_DRV_NAME    KBUILD_MODNAME
#define PCIE_DRV_VERSION "10.3.4.0-20170421"

#define PCIE_MIN_BYTES_HEADROOM   64
#define PCIE_NUM_OF_DESC_DATA     SYSADPT_TOTAL_TX_QUEUES
#define PCIE_AMPDU_QUEUES         4
#define PCIE_MAX_NUM_TX_DESC      256
#define PCIE_TX_QUEUE_LIMIT       (3 * PCIE_MAX_NUM_TX_DESC)
#define PCIE_TX_WAKE_Q_THRESHOLD  (2 * PCIE_MAX_NUM_TX_DESC)
#define PCIE_DELAY_FREE_Q_LIMIT   PCIE_MAX_NUM_TX_DESC
#define PCIE_MAX_NUM_RX_DESC      256
#define PCIE_RECEIVE_LIMIT        64

enum {
	IEEE_TYPE_MANAGEMENT = 0,
	IEEE_TYPE_CONTROL,
	IEEE_TYPE_DATA
};

#define MAC_REG_ADDR(offset)      (offset)
#define MAC_REG_ADDR_PCI(offset)  ((pcie_priv->iobase1 + 0xA000) + offset)

#define MCU_CCA_CNT               MAC_REG_ADDR(0x06A0)
#define MCU_TXPE_CNT              MAC_REG_ADDR(0x06A4)
#define MCU_LAST_READ             MAC_REG_ADDR(0x06A8)

/* Map to 0x80000000 (Bus control) on BAR0 */
#define MACREG_REG_H2A_INTERRUPT_EVENTS      0x00000C18 /* (From host to ARM) */
#define MACREG_REG_H2A_INTERRUPT_CAUSE       0x00000C1C /* (From host to ARM) */
#define MACREG_REG_H2A_INTERRUPT_MASK        0x00000C20 /* (From host to ARM) */
#define MACREG_REG_H2A_INTERRUPT_CLEAR_SEL   0x00000C24 /* (From host to ARM) */
#define MACREG_REG_H2A_INTERRUPT_STATUS_MASK 0x00000C28 /* (From host to ARM) */

#define MACREG_REG_A2H_INTERRUPT_EVENTS      0x00000C2C /* (From ARM to host) */
#define MACREG_REG_A2H_INTERRUPT_CAUSE       0x00000C30 /* (From ARM to host) */
#define MACREG_REG_A2H_INTERRUPT_MASK        0x00000C34 /* (From ARM to host) */
#define MACREG_REG_A2H_INTERRUPT_CLEAR_SEL   0x00000C38 /* (From ARM to host) */
#define MACREG_REG_A2H_INTERRUPT_STATUS_MASK 0x00000C3C /* (From ARM to host) */

/* Map to 0x80000000 on BAR1 */
#define MACREG_REG_GEN_PTR                  0x00000C10
#define MACREG_REG_INT_CODE                 0x00000C14

/* Bit definition for MACREG_REG_A2H_INTERRUPT_CAUSE (A2HRIC) */
#define MACREG_A2HRIC_BIT_TX_DONE           BIT(0)
#define MACREG_A2HRIC_BIT_RX_RDY            BIT(1)
#define MACREG_A2HRIC_BIT_OPC_DONE          BIT(2)
#define MACREG_A2HRIC_BIT_MAC_EVENT         BIT(3)
#define MACREG_A2HRIC_BIT_RX_PROBLEM        BIT(4)
#define MACREG_A2HRIC_BIT_RADIO_OFF         BIT(5)
#define MACREG_A2HRIC_BIT_RADIO_ON          BIT(6)
#define MACREG_A2HRIC_BIT_RADAR_DETECT      BIT(7)
#define MACREG_A2HRIC_BIT_ICV_ERROR         BIT(8)
#define MACREG_A2HRIC_BIT_WEAKIV_ERROR      BIT(9)
#define MACREG_A2HRIC_BIT_QUE_EMPTY         BIT(10)
#define MACREG_A2HRIC_BIT_QUE_FULL          BIT(11)
#define MACREG_A2HRIC_BIT_CHAN_SWITCH       BIT(12)
#define MACREG_A2HRIC_BIT_TX_WATCHDOG       BIT(13)
#define MACREG_A2HRIC_BA_WATCHDOG           BIT(14)
/* 15 taken by ISR_TXACK */
#define MACREG_A2HRIC_BIT_SSU_DONE          BIT(16)
#define MACREG_A2HRIC_CONSEC_TXFAIL         BIT(17)

#define ISR_SRC_BITS        (MACREG_A2HRIC_BIT_RX_RDY | \
			     MACREG_A2HRIC_BIT_TX_DONE | \
			     MACREG_A2HRIC_BIT_OPC_DONE | \
			     MACREG_A2HRIC_BIT_MAC_EVENT | \
			     MACREG_A2HRIC_BIT_WEAKIV_ERROR | \
			     MACREG_A2HRIC_BIT_ICV_ERROR | \
			     MACREG_A2HRIC_BIT_SSU_DONE | \
			     MACREG_A2HRIC_BIT_RADAR_DETECT | \
			     MACREG_A2HRIC_BIT_CHAN_SWITCH | \
			     MACREG_A2HRIC_BIT_TX_WATCHDOG | \
			     MACREG_A2HRIC_BIT_QUE_EMPTY | \
			     MACREG_A2HRIC_BA_WATCHDOG | \
			     MACREG_A2HRIC_CONSEC_TXFAIL)

#define MACREG_A2HRIC_BIT_MASK      ISR_SRC_BITS

/* Bit definition for MACREG_REG_H2A_INTERRUPT_CAUSE (H2ARIC) */
#define MACREG_H2ARIC_BIT_PPA_READY         BIT(0)
#define MACREG_H2ARIC_BIT_DOOR_BELL         BIT(1)
#define MACREG_H2ARIC_BIT_PS                BIT(2)
#define MACREG_H2ARIC_BIT_PSPOLL            BIT(3)
#define ISR_RESET                           BIT(15)
#define ISR_RESET_AP33                      BIT(26)

/* Data descriptor related constants */
#define EAGLE_RXD_CTRL_DRIVER_OWN           0x00
#define EAGLE_RXD_CTRL_DMA_OWN              0x80

#define EAGLE_RXD_STATUS_OK                 0x01

#define EAGLE_TXD_STATUS_IDLE               0x00000000
#define EAGLE_TXD_STATUS_OK                 0x00000001
#define EAGLE_TXD_STATUS_FW_OWNED           0x80000000

struct pcie_tx_desc {
	u8 data_rate;
	u8 tx_priority;
	__le16 qos_ctrl;
	__le32 pkt_ptr;
	__le16 pkt_len;
	u8 dest_addr[ETH_ALEN];
	__le32 pphys_next;
	__le32 sap_pkt_info;
	__le32 rate_info;
	u8 type;
	u8 xmit_control;     /* bit 0: use rateinfo, bit 1: disable ampdu */
	__le16 reserved;
	__le32 tcpack_sn;
	__le32 tcpack_src_dst;
	__le32 reserved1;
	__le32 reserved2;
	u8 reserved3[2];
	u8 packet_info;
	u8 packet_id;
	__le16 packet_len_and_retry;
	__le16 packet_rate_info;
	__le32 reserved4;
	__le32 status;
} __packed;

struct pcie_tx_hndl {
	struct sk_buff *psk_buff;
	struct pcie_tx_desc *pdesc;
	struct pcie_tx_hndl *pnext;
};

#define MWL_RX_RATE_FORMAT_MASK       0x0007
#define MWL_RX_RATE_NSS_MASK          0x0018
#define MWL_RX_RATE_NSS_SHIFT         3
#define MWL_RX_RATE_BW_MASK           0x0060
#define MWL_RX_RATE_BW_SHIFT          5
#define MWL_RX_RATE_GI_MASK           0x0080
#define MWL_RX_RATE_GI_SHIFT          7
#define MWL_RX_RATE_RT_MASK           0xFF00
#define MWL_RX_RATE_RT_SHIFT          8

struct pcie_rx_desc {
	__le16 pkt_len;              /* total length of received data      */
	__le16 rate;                 /* receive rate information           */
	__le32 pphys_buff_data;      /* physical address of payload data   */
	__le32 pphys_next;           /* physical address of next RX desc   */
	__le16 qos_ctrl;             /* received QosCtrl field variable    */
	__le16 ht_sig2;              /* like name states                   */
	__le32 hw_rssi_info;
	__le32 hw_noise_floor_info;
	u8 noise_floor;
	u8 reserved[3];
	u8 rssi;                     /* received signal strengt indication */
	u8 status;                   /* status field containing USED bit   */
	u8 channel;                  /* channel this pkt was received on   */
	u8 rx_control;               /* the control element of the desc    */
	__le32 reserved1[3];
} __packed;

struct pcie_rx_hndl {
	struct sk_buff *psk_buff;    /* associated sk_buff for Linux       */
	struct pcie_rx_desc *pdesc;
	struct pcie_rx_hndl *pnext;
};

struct pcie_desc_data {
	dma_addr_t pphys_tx_ring;          /* ptr to first TX desc (phys.)    */
	struct pcie_tx_desc *ptx_ring;     /* ptr to first TX desc (virt.)    */
	struct pcie_tx_hndl *tx_hndl;
	struct pcie_tx_hndl *pnext_tx_hndl;/* next TX handle that can be used */
	struct pcie_tx_hndl *pstale_tx_hndl;/* the staled TX handle           */
	dma_addr_t pphys_rx_ring;          /* ptr to first RX desc (phys.)    */
	struct pcie_rx_desc *prx_ring;     /* ptr to first RX desc (virt.)    */
	struct pcie_rx_hndl *rx_hndl;
	struct pcie_rx_hndl *pnext_rx_hndl;/* next RX handle that can be used */
	u32 wcb_base;                      /* FW base offset for registers    */
	u32 rx_desc_write;                 /* FW descriptor write position    */
	u32 rx_desc_read;                  /* FW descriptor read position     */
	u32 rx_buf_size;                   /* length of the RX buffers        */
};

/* DMA header used by firmware and hardware. */
struct pcie_dma_data {
	__le16 fwlen;
	struct ieee80211_hdr wh;
	char data[0];
} __packed;

/* New Data Path */
#define MACREG_REG_SCRATCH3                0x00000C44
#define MACREG_REG_TXSENDHEAD              0x00000CD0
#define MACREG_REG_TXSEDNTAIL              0x00000CD4
#define MACREG_REG_TXDONEHEAD              0x00000CD8
#define MACREG_REG_TXDONETAIL              0x00000CDC
#define MACREG_REG_RXDESCHEAD              0x00000CE0
#define MACREG_REG_RXDESCTAIL              0x00000CE4
#define MACREG_REG_RXDONEHEAD              0x00000CE8
#define MACREG_REG_RXDONETAIL              0x00000CEC
#define MACREG_REG_ACNTHEAD                0x00000CF0
#define MACREG_REG_ACNTTAIL                0x00000CF4

/* Buff removed from Tx Send Ring */
#define MACREG_A2HRIC_TX_DESC_TAIL_RDY     (1<<9)
/* Buff added to Tx Done Ring */
#define MACREG_A2HRIC_TX_DONE_HEAD_RDY     (1<<10)
/* Records added to Accounting Ring */
#define MACREG_A2HRIC_ACNT_HEAD_RDY        (1<<12)
/* Buff removed from Rx Desc Ring */
#define MACREG_A2HRIC_RX_DESC_TAIL_RDY     (1<<17)
/* Buff added to Rx Done Ring */
#define MACREG_A2HRIC_RX_DONE_HEAD_RDY     (1<<18)
#define MACREG_A2HRIC_NEWDP_DFS            (1<<19)
#define MACREG_A2HRIC_NEWDP_CHANNEL_SWITCH (1<<20)

#define ISR_SRC_BITS_NDP     ((MACREG_A2HRIC_ACNT_HEAD_RDY) | \
			      (MACREG_A2HRIC_RX_DONE_HEAD_RDY) | \
			      (MACREG_A2HRIC_NEWDP_DFS)     | \
			      (MACREG_A2HRIC_NEWDP_CHANNEL_SWITCH))

#define MACREG_A2HRIC_BIT_MASK_NDP ISR_SRC_BITS_NDP

#define MIN_BYTES_RX_HEADROOM  (64 + 2)
#define AMPDU_QUEUES_NDP       (SYSADPT_MAX_STA_SC4 * \
				SYSADPT_MAX_TID)
#define MAX_NUM_TX_DESC        1024
#define MAX_NUM_RX_DESC        (1024 * 16)
#define MAX_TX_RING_SEND_SIZE  (4 * MAX_NUM_TX_DESC)
#define MAX_TX_RING_DONE_SIZE  MAX_NUM_TX_DESC
#define MAX_RX_RING_SEND_SIZE  MAX_NUM_RX_DESC
#define MAX_RX_RING_DONE_SIZE  MAX_NUM_RX_DESC
#define DEFAULT_ACNT_RING_SIZE 0x10000
#define MAX_AGGR_SIZE          2700
#define TX_QUEUE_LIMIT         MAX_NUM_TX_DESC
#define TX_WAKE_Q_THRESHOLD    (MAX_NUM_TX_DESC - 256)

/* RateCode usage notes:
 * * General
 *     * No error checking is provided on RateCodes, so usage of invalid values
 *       or rates not supported by HW can result in undefined operation.
 *     * Some values are not allowed by Std, but are included to sanitize the
 *       table;
 *     * MaxPwr should only be used for rates that can be sent using Max Power,
 *       such as for TxEVM limits or regulatory. It is only valid for Host
 *       Generated frames, and not for DRA, etc.
 * * VHT
 *     * Need to reconsile MU.
 * * HT
 *     * MCS and SS are made to mimic 11ac, so MCS=mcs[2:0] and SS=mcs[4:3];
 *     * MCS32 is selected by providing MCS=10;
 * * Legacy
 *     * MCS0..7  = 6/9/12/18/24/36/48/54;
 *     * MCS8..15 = 1S/1L/2S/2L/5.5S/5.5L/11S/11L;
 *     * BW is used to request legacy duplicate modes;
 */
#define RATECODE_DEFAULT        0xFFFF  /* Don't override the Rate            */
#define RATECODE_TYPE_MASK      0xC000  /* Mask  to extract Type              */
#define RATECODE_TYPE_SHIFT     14      /* Shift to extract Type              */
#define RATECODE_TYPE_VHT       0x8000  /* Use VHT rates                      */
#define RATECODE_TYPE_HT        0x4000  /* Use HT rates                       */
#define RATECODE_TYPE_LEGACY    0x0000  /* Use Legacy (a/b/g) rates           */
#define RATECODE_MAXPWR         0x2000  /* Send at Max Power / Off Channel    */
#define RATECODE_RSVD           0x1000  /* Unused                             */
#define RATECODE_STBC           0x0800  /* Use Space Time Block Codes         */
#define RATECODE_BFMR           0x0400  /* Use Beamforming                    */
#define RATECODE_SS_MASK        0x0300  /* Mask  to extract nSS-1             */
#define RATECODE_SS_SHIFT       8       /* Shift to extract nSS-1             */
#define RATECODE_MCS_MASK       0x00F0  /* Mask  to extract MCS rate          */
#define RATECODE_MCS_SHIFT      4       /* Shift to extract MCS rate          */
#define RATECODE_BW_MASK        0x000C  /* Mask  to extract Channel BW        */
#define RATECODE_BW_SHIFT       2       /* Shift to extract Channel BW        */
#define RATECODE_BW_160MHZ      0x000C  /* Send 160M wide packet (or 80+80)   */
#define RATECODE_BW_80MHZ       0x0008  /* Send  80M wide packet              */
#define RATECODE_BW_40MHZ       0x0004  /* Send  40M wide packet              */
#define RATECODE_BW_20MHZ       0x0000  /* Send  20M wide packet              */
#define RATECODE_LDPC           0x0002  /* Use Low Density Parity Codes       */
#define RATECODE_SGI            0x0001  /* Use Short Guard Interval           */

#define TXRING_CTRL_LEN_SHIFT   0      /* PCIe Payload size (Starts w/ SNAP)  */
#define TXRING_CTRL_LEN_MASK    0x3FFF /* PCIe Payload size (Starts w/ SNAP)  */
#define TXRING_CTRL_QID_SHIFT   14     /* Queue ID (STA*UP, Mcast, MC2UC, etc)*/
#define TXRING_CTRL_QID_MASK    0xFFF  /* Queue ID (STA*UP, Mcast, MC2UC, etc)*/
#define TXRING_CTRL_TAG_SHIFT   26     /* Tags for special Processing         */
#define TXRING_CTRL_TAG_MASK    0x3F   /* Tags for special Processing         */
#define TXRING_CTRL_TAG_MGMT    0x01   /* Has Host generated dot11 Header     */
#define TXRING_CTRL_TAG_EAP     0x02   /* Tag for EAPOL frames                */
#define TXRING_CTRL_TAG_TCP_ACK 0x4
#define TXRING_CTRL_TAG_RSVD    0x3C   /* Unused                              */

struct pcie_tx_desc_ndp {
	union { /* Union for Tx DA/SA or Mgmt Overrides */
		struct { /* Fields for Data frames     */
			u8 da[ETH_ALEN];  /* L2 Destination Address         */
			u8 sa[ETH_ALEN];  /* L2 Source Address              */
		};
		struct { /* Fields when marked as Mgmt */
			__le16 rate_code; /* Rate Code: Table + Index       */
			u8 max_retry;
			u8 pad[5];        /* Unused                         */
			__le32 call_back; /* Used for Packet returned to FW */
		};
	} u;
	__le32 ctrl; /* Bit fields (TXRING_CTRL_*)            */
	__le32 data; /* PCIe Payload Pointer (Starts w/ SNAP) */
	__le32 user; /* Value returned to Host when done      */
	__le32 tcp_dst_src;
	__le32 tcp_sn;
} __packed;

struct tx_ring_done {
	__le32 user;
} __packed;

#define RXRING_CTRL_CASE_SHIFT  0     /* What is in the buffer(RXRING_CASE_*) */
#define RXRING_CTRL_CASE_MASK   0x1F  /* What is in the buffer(RXRING_CASE_*) */
#define RXRING_CTRL_STA_SHIFT   5     /* STA information (or Mcast group)     */
#define RXRING_CTRL_STA_MASK    0x1FF /* STA information (or Mcast group)     */
#define RXRING_CTRL_STA_UNKNOWN 0x1FF /* STA Idx for packets from Unknown STA */
#define RXRING_CTRL_STA_FROMDS  0x1FE /* STA Idx for packets from DS          */
#define RXRING_CTRL_TID_SHIFT   14    /* TID/UP for QoS Data frames           */
#define RXRING_CTRL_TID_MASK    0xF   /* TID/UP for QoS Data frames           */
#define RXRING_CTRL_KEY_SHIFT   18    /* Key Type used (KEY_TYPE_*)           */
#define RXRING_CTRL_KEY_MASK    0xF   /* Key Type used (KEY_TYPE_*)           */
#define RXRING_CTRL_TRUNC       (1UL<<31) /* Packet Truncated                 */

/* Rx Buffer Formats
 *    Each Case listed above will indicate the format used, and each format will
 *    carry their length in the packet buffer. Should the packet be too big for
 *    the buffer, it will be truncated, but the full length will still be
 *    indicated. Currently only a single, fixed size Rx Pool is envisioned.
 *
 * Fmt0 is used for Slow path, when some processing of dot11 headers may still
 * be required, or for promiscuous mode captures. It is in the HW RxINFO
 * (rx_info_t) format including dot11_t followed by Payload. The Length field in
 * the dot11_t is updated to only include Payload bytes, and is in Little Endian
 * format. If the frame is too big, it is truncated to the buffer size, and
 * promiscuous packets may also be configured for truncation to reduce load. The
 * mark field is replaced with software status, and the RSSI will be updated to
 * apply Rx calibration.
 *
 * Fmt1 is used for fast path Data packets in the run state, where all rx
 * processing of dot11 headers is performed from radio FW. It has an AMSDU
 * centric format of DA/SA/Len followed by SNAP, with the Length in Big Endian
 * Format. In most cases conversion to Ethernet format is accomplished by
 * copying 12 bytes to drop 8 bytes in the middle.
 *
 * Fmt2 is used for fast path AMSDU packets that are malformed. They just
 * contain the dot11 header (dot11_t) containing the residual Len (Little
 * Endian) after any valid MSDU have been extracted. The header is followed by
 * the first invalid MSDU which will be truncated to 64 bytes.
 */
enum { /* What is in Rx Buffer and why it was delivered */
	/* Data for Assoc Clients in Run State on Channel [Fmt1]              */
	RXRING_CASE_FAST_DATA,
	RXRING_CASE_FAST_BAD_AMSDU, /* Fast Data with bad AMSDU Header [Fmt2] */
	/* Data for Assoc Clients using unconfigured queue [Fmt0]             */
	RXRING_CASE_SLOW_NOQUEUE,
	/* Data for Assoc Clients not matching Run State [Fmt0]               */
	RXRING_CASE_SLOW_NORUN,
	/* Data for filtered Multicast groups [Fmt0]                          */
	RXRING_CASE_SLOW_MCAST,
	RXRING_CASE_SLOW_BAD_STA,   /* Data for Unassoc Clients [Fmt0]        */
	RXRING_CASE_SLOW_BAD_MIC,   /* Decrypt failure [Fmt0]                 */
	RXRING_CASE_SLOW_BAD_PN,    /* Decrypt PN replay [Fmt0]               */
	RXRING_CASE_SLOW_MGMT,      /* Mgmt traffic to this AP or Bcast [Fmt0]*/
	RXRING_CASE_SLOW_PROMISC,   /* Packets captured promiscuously [Fmt0]  */
	RXRING_CASE_SLOW_DEL_DONE,  /* Client has been deleted [N/A]          */
	RXRING_CASE_DROP,           /* Buffer returned to Host [N/A]          */
};

enum { /* Type of Key */
	KEY_TYPE_NONE,      /* Bypass (never stored in real keys)     */
	KEY_TYPE_WEP40,     /* WEP with  40 bit key + 24 bit IV =  64 */
	KEY_TYPE_WEP104,    /* WEP with 104 bit key + 24 bit IV = 128 */
	KEY_TYPE_TKIP,      /* TKIP                                   */
	KEY_TYPE_CCMP128,   /* CCMP with 128 bit Key                  */
	KEY_TYPE_CCMP256,   /* CCMP with 256 bit Key + 16 byte MIC    */
	KEY_TYPE_WAPI,      /* WAPI                                   */
	KEY_TYPE_UNKNOWN,   /* Not known what key was used (Rx Only)  */
	KEY_TYPE_GCMP128,   /* GCMP with 128 bit Key                  */
	KEY_TYPE_GCMP256,   /* GCMP with 256 bit Key + 16 byte MIC    */
};

#define RXINFO_RSSI_X_SHIFT     0
#define RXINFO_RSSI_X_MASK      0xFF
#define RXINFO_HT_SIG1_SHIFT    8
#define RXINFO_HT_SIG1_MASK     0xFFFFFF
#define RXINFO_HT_SIG2_SHIFT    14
#define RXINFO_HT_SIG2_MASK     0x3FFFF
#define RXINFO_RATE_SHIFT       0
#define RXINFO_RATE_MASK        0xFF

struct rx_info { /* HW Rx buffer */
	__le32 reserved0[2];
	__le32 rssi_x;
	__le32 reserved1[2];
	__le32 ht_sig1;
	__le32 ht_sig2_rate;
	__le32 reserved2[17];
	__le32 hdr[0]; /* Len from HW includes rx_info w/ hdr */
} __packed;

struct pcie_rx_desc_ndp { /* ToNIC Rx Empty Buffer Ring Entry */
	__le32 data; /* PCIe Payload Pointer               */
	__le32 user; /* Value returned to Host when done   */
} __packed;

struct rx_ring_done { /* FromNIC Rx Done Ring Entry */
	__le32 user; /* Value returned to Host when done   */
	__le32 tsf;  /* Rx Radio Timestamp from MAC        */
	__le32 ctrl; /* Bit fields (RXRING_CTRL_*)         */
} __packed;

struct pcie_desc_data_ndp {
	dma_addr_t pphys_tx_ring;         /* ptr to first TX desc (phys.)    */
	struct pcie_tx_desc_ndp *ptx_ring;/* ptr to first TX desc (virt.)    */
	dma_addr_t pphys_rx_ring;         /* ptr to first RX desc (phys.)    */
	struct pcie_rx_desc_ndp *prx_ring;/* ptr to first RX desc (virt.)    */
	u32 wcb_base;                     /* FW base offset for registers    */
	u32 rx_buf_size;                  /* length of the RX buffers        */
	u32 tx_sent_tail;                 /* index to the TX desc FW used    */
	u32 tx_sent_head;                 /* index to next TX desc to be used*/
	u32 tx_done_tail;                 /* index to Tx Done queue tail     */
	/* keept the skb owned by fw */
	dma_addr_t pphys_tx_buflist[MAX_TX_RING_SEND_SIZE];
	struct sk_buff *tx_vbuflist[MAX_TX_RING_SEND_SIZE];
	u32 tx_vbuflist_idx;              /* idx to empty slot in tx_vbuflist*/
	struct sk_buff *rx_vbuflist[MAX_NUM_RX_DESC];
	struct tx_ring_done *ptx_ring_done;
	dma_addr_t pphys_tx_ring_done; /* ptr to first TX done desc (phys.)  */
	struct rx_ring_done *prx_ring_done;
	dma_addr_t pphys_rx_ring_done; /* ptr to first RX done desc (phys.)  */
	dma_addr_t pphys_acnt_ring;    /* ptr to first account record (phys.)*/
	u8 *pacnt_ring;                /* ptr to first accounting record     */
	u32 tx_desc_busy_cnt;
	u8 *pacnt_buf;
	u32 acnt_ring_size;
};

struct ndp_rx_counter {
	u32 fast_data_cnt;
	u32 fast_bad_amsdu_cnt;
	u32 slow_noqueue_cnt;
	u32 slow_norun_cnt;
	u32 slow_mcast_cnt;
	u32 slow_bad_sta_cnt;
	u32 slow_bad_mic_cnt;
	u32 slow_bad_pn_cnt;
	u32 slow_mgmt_cnt;
	u32 slow_promisc_cnt;
	u32 drop_cnt;
	u32 offch_promisc_cnt;
	u32 mu_pkt_cnt;
};

struct pcie_priv {
	struct mwl_priv *mwl_priv;
	struct pci_dev *pdev;
	void __iomem *iobase0; /* MEM Base Address Register 0  */
	void __iomem *iobase1; /* MEM Base Address Register 1  */
	u32 next_bar_num;

	struct sk_buff_head txq[PCIE_NUM_OF_DESC_DATA];

	spinlock_t int_mask_lock ____cacheline_aligned_in_smp;
	struct tasklet_struct tx_task;
	struct tasklet_struct tx_done_task;
	struct tasklet_struct rx_task;
	struct tasklet_struct qe_task;
	int txq_limit;
	int txq_wake_threshold;
	bool is_tx_schedule;
	bool is_tx_done_schedule;
	int recv_limit;
	bool is_rx_schedule;
	bool is_qe_schedule;
	u32 qe_trig_num;
	unsigned long qe_trig_time;

	/* various descriptor data */
	/* for tx descriptor data  */
	spinlock_t tx_desc_lock ____cacheline_aligned_in_smp;
	struct pcie_desc_data desc_data[PCIE_NUM_OF_DESC_DATA];
	struct sk_buff_head delay_q;
	/* number of descriptors owned by fw at any one time */
	int fw_desc_cnt[PCIE_NUM_OF_DESC_DATA];

	/* new data path */
	struct pcie_desc_data_ndp desc_data_ndp;
	int tx_done_cnt;
	struct ieee80211_sta *sta_link[SYSADPT_MAX_STA_SC4 + 1];
	struct sk_buff_head rx_skb_trace;
	struct ndp_rx_counter rx_cnts;
	u32 rx_skb_unlink_err;
	u32 signature_err;
};

static inline void pcie_tx_add_dma_header(struct mwl_priv *priv,
					 struct sk_buff *skb,
					 int head_pad,
					 int tail_pad)
{
	struct ieee80211_hdr *wh;
	int hdrlen;
	int reqd_hdrlen;
	struct pcie_dma_data *dma_data;

	/* Add a firmware DMA header; the firmware requires that we
	 * present a 2-byte payload length followed by a 4-address
	 * header (without QoS field), followed (optionally) by any
	 * WEP/ExtIV header (but only filled in for CCMP).
	 */
	wh = (struct ieee80211_hdr *)skb->data;

	hdrlen = ieee80211_hdrlen(wh->frame_control);

	reqd_hdrlen = sizeof(*dma_data) + head_pad;

	if (hdrlen != reqd_hdrlen)
		skb_push(skb, reqd_hdrlen - hdrlen);

	if (ieee80211_is_data_qos(wh->frame_control))
		hdrlen -= IEEE80211_QOS_CTL_LEN;

	dma_data = (struct pcie_dma_data *)skb->data;

	if (wh != &dma_data->wh)
		memmove(&dma_data->wh, wh, hdrlen);

	if (hdrlen != sizeof(dma_data->wh))
		memset(((void *)&dma_data->wh) + hdrlen, 0,
		       sizeof(dma_data->wh) - hdrlen);

	/* Firmware length is the length of the fully formed "802.11
	 * payload".  That is, everything except for the 802.11 header.
	 * This includes all crypto material including the MIC.
	 */
	dma_data->fwlen =
		cpu_to_le16(skb->len - sizeof(*dma_data) + tail_pad);
}

static inline void pcie_tx_encapsulate_frame(struct mwl_priv *priv,
					     struct sk_buff *skb,
					     struct ieee80211_key_conf *k_conf,
					     bool *ccmp)
{
	int head_pad = 0;
	int data_pad = 0;

	/* Make sure the packet header is in the DMA header format (4-address
	 * without QoS), and add head & tail padding when HW crypto is enabled.
	 *
	 * We have the following trailer padding requirements:
	 * - WEP: 4 trailer bytes (ICV)
	 * - TKIP: 12 trailer bytes (8 MIC + 4 ICV)
	 * - CCMP: 8 trailer bytes (MIC)
	 */

	if (k_conf) {
		head_pad = k_conf->iv_len;

		switch (k_conf->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			data_pad = 4;
			break;
		case WLAN_CIPHER_SUITE_TKIP:
			data_pad = 12;
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			data_pad = 8;
			if (ccmp)
				*ccmp = true;
			break;
		}
	}

	pcie_tx_add_dma_header(priv, skb, head_pad, data_pad);
}

static inline void pcie_tx_prepare_info(struct mwl_priv *priv, u32 rate,
					struct ieee80211_tx_info *info)
{
	u32 format, bandwidth, short_gi, rate_id;

	ieee80211_tx_info_clear_status(info);

	info->status.rates[0].idx = -1;
	info->status.rates[0].count = 0;
	info->status.rates[0].flags = 0;
	info->flags |= IEEE80211_TX_STAT_ACK;

	if (rate) {
		/* Prepare rate information */
		format = rate & MWL_TX_RATE_FORMAT_MASK;
		bandwidth =
			(rate & MWL_TX_RATE_BANDWIDTH_MASK) >>
			MWL_TX_RATE_BANDWIDTH_SHIFT;
		short_gi = (rate & MWL_TX_RATE_SHORTGI_MASK) >>
			MWL_TX_RATE_SHORTGI_SHIFT;
		rate_id = (rate & MWL_TX_RATE_RATEIDMCS_MASK) >>
			MWL_TX_RATE_RATEIDMCS_SHIFT;

		info->status.rates[0].idx = rate_id;
		if (format == TX_RATE_FORMAT_LEGACY) {
			if (priv->hw->conf.chandef.chan->hw_value >
			    BAND_24_CHANNEL_NUM) {
				info->status.rates[0].idx -= 5;
			}
		}
		if (format == TX_RATE_FORMAT_11N)
			info->status.rates[0].flags |=
				IEEE80211_TX_RC_MCS;
		if (format == TX_RATE_FORMAT_11AC)
			info->status.rates[0].flags |=
				IEEE80211_TX_RC_VHT_MCS;
		if (bandwidth == TX_RATE_BANDWIDTH_40)
			info->status.rates[0].flags |=
				IEEE80211_TX_RC_40_MHZ_WIDTH;
		if (bandwidth == TX_RATE_BANDWIDTH_80)
			info->status.rates[0].flags |=
				IEEE80211_TX_RC_80_MHZ_WIDTH;
		if (bandwidth == TX_RATE_BANDWIDTH_160)
			info->status.rates[0].flags |=
				IEEE80211_TX_RC_160_MHZ_WIDTH;
		if (short_gi == TX_RATE_INFO_SHORT_GI)
			info->status.rates[0].flags |=
				IEEE80211_TX_RC_SHORT_GI;
		info->status.rates[0].count = 1;
		info->status.rates[1].idx = -1;
	}
}

static inline void pcie_rx_remove_dma_header(struct sk_buff *skb, __le16 qos)
{
	struct pcie_dma_data *dma_data;
	int hdrlen;

	dma_data = (struct pcie_dma_data *)skb->data;
	hdrlen = ieee80211_hdrlen(dma_data->wh.frame_control);

	if (hdrlen != sizeof(dma_data->wh)) {
		if (ieee80211_is_data_qos(dma_data->wh.frame_control)) {
			memmove(dma_data->data - hdrlen,
				&dma_data->wh, hdrlen - 2);
			*((__le16 *)(dma_data->data - 2)) = qos;
		} else {
			memmove(dma_data->data - hdrlen, &dma_data->wh, hdrlen);
		}
	}

	if (hdrlen != sizeof(*dma_data))
		skb_pull(skb, sizeof(*dma_data) - hdrlen);
}

static inline void pcie_mask_int(struct pcie_priv *pcie_priv,
				 u32 mask_bit, bool set)
{
	unsigned long flags;
	void __iomem *int_status_mask;
	u32 status;

	spin_lock_irqsave(&pcie_priv->int_mask_lock, flags);
	int_status_mask = pcie_priv->iobase1 +
		MACREG_REG_A2H_INTERRUPT_STATUS_MASK;
	status = readl(int_status_mask);
	if (set)
		writel((status | mask_bit), int_status_mask);
	else
		writel((status & ~mask_bit), int_status_mask);
	spin_unlock_irqrestore(&pcie_priv->int_mask_lock, flags);
}

#endif /* _DEV_H_ */
