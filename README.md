# McDebian

## A Linksys WRT3200, WRT1900 and WRT1200 Router Series Debian Implementation

**Source of Marvell 802.11ac hostapd driver**

https://github.com/kaloz/mwlwifi

### Wireless driver is upgraded to version 10.3.2.0-20170110

## Rootfs V4.4.16

Linux version is "4.4.16".

Debian root files system is "Jessie" stable.

Dibbler version is "1.0.1"

Wireless driver is version 10.3.0.17-20160531-1

## McDebian Update V4.7.5

Linux version is "4.7.5".

Debian root files system is "Jessie" stable.

Dibbler version is "1.0.1"

Wireless driver is version 10.3.0.18-20160823-1

## McDebian Update V4.8.15

Linux version is "4.8.15".

Debian root files system is "Jessie" stable.

Dibbler version is "1.0.1"

Wireless driver is version 10.3.2.0-20161124

WRT3200ACM V1 support added

## Update 4.8.15-VER3

### Fixes:
1. Hostapd would fail to start with new mwlwifi driver in McDebian 4.7.5\4.8.15 on routers that don't get the power table update from the dts file. This was due to the country code "EU" being hardcoded in mwlwifi and it not being a valid entry in the CRDA database. I've added "EU" to the CRDA database to resolve this issue.

### Additions:

New Kernel Modules and Firmware:

```
CONFIG_USB_SERIAL
CONFIG_USB_SERIAL_GENERIC
CONFIG_USB_SERIAL_OPTION
CONFIG_USB_NET_RNDIS_HOST
CONFIG_USB_NET_CDCETHER
CONFIG_USB_USBNET
CONFIG_BONDING
MWIFIEX
MWIFIEX_SDIO
```

### Updates:

1. WRT3200ACM V1 support for the third radio MWIFIEX which is interface mlan0. You will need to add this to /etc/network/interfaces, /etc/default/hostapd and create /etc/hostapd/mlan0.conf file to put this radio into operation.
1. Updated /etc/systemd/udev-network-interface-rules to work with WRT3200ACM's additional wireless interface.

## McDebian Update V4.9.12

Linux version is "4.9.12".

Debian root files system is "Jessie" stable.

Dibbler version is "1.0.1"

Wireless driver is version 10.3.2.0-20170110

### Notes:

1. EU country code no longer required for mwlwifi in this driver version

## McDebian is compatible with the below Linksys WRT models:

1. WRT1900AC V1
2. WRT1900AC V2
3. WRT1200AC V1
4. WRT1200AC V2
5. WRT1900ACS V1
6. WRT1900ACS V2
7. WRT3200ACM V1

## McDebian Deployment Instructions
https://github.com/Chadster766/McDebian/wiki

-
## Warning!

## Notice: For rootfs USB Flash drives I recommend using Corsair or Sandisk because Wear Leveling is built into the hardware. For mass storage you can use spinning disk external drive or any other type of disk that has built in wear leveling.

-
**Please email me if you would like to be part of the development team.**

