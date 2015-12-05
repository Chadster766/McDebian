# McDebian
Linksys WRT1900\1200 Router Series Debian Implementation

I've managed to get Debian Jessie to run successfully on a WRT1900AC V2.

The below link outlines how I did it:

Linksys WRT1900\1200 Router Series Debian OS Implementation:

http://www.snbforums.com/threads/linksys-wrt1900-1200-router-series-debian-os-implementation.28394/

I'm hoping this will spur activity and development to improve the SMB potential of the new Linksys WRT series for the advanced IT sector.

I'm also looking for firewall, routing and security suggestions along with system configurations to speed up development of this Debian WRT system.

Only uses these firmwares if you have USB to TTL access to your WRT1900\1200 router.

You can download the rootfs using the below link and credentials:

http://www.protechs-online.com/downloads/McDebian/rootfs

http://www.protechs-online.com/downloads/McDebian/firmwares

Username: mcdebian

Password: mcdebian123

Debian System credentials:


Username: root

Password: mcdebian

Wireles WPA2 Personal:


Password: mcdebian123

Default IP Address 192.168.1.1

To make the USB2.0 or USB3.0 rootfs:

mkfs.ext4 /dev/sdb(x)
mount /dev/sdb(x) /mnt/usbkey
tar zxf mcdebian-(x)-base.gz -C /mnt/usbkey
