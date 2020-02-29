Fix parity setting/checking on *BSD and MacOSX
The flag INPCK was set to newtio.c_cflag but it should be set to
newtio.c_iflag.
http://pubs.opengroup.org/onlinepubs/009695399/basedefs/termios.h.html
https://sourceforge.net/p/stm32flash/tickets/89/
https://sourceforge.net/p/stm32flash/tickets/68/

-------------------------------------------------------------------------


--- a/serial_posix.c
+++ b/serial_posix.c
@@ -129,8 +129,8 @@
 
 	switch (parity) {
 		case SERIAL_PARITY_NONE: port_parity = 0; break;
-		case SERIAL_PARITY_EVEN: port_parity = INPCK | PARENB; break;
-		case SERIAL_PARITY_ODD:  port_parity = INPCK | PARENB | PARODD; break;
+		case SERIAL_PARITY_EVEN: port_parity = PARENB; break;
+		case SERIAL_PARITY_ODD:  port_parity = PARENB | PARODD; break;
 
 		default:
 			return PORT_ERR_UNKNOWN;
@@ -174,6 +174,8 @@
 		port_stop	|
 		CLOCAL		|
 		CREAD;
+	if ( port_parity != 0 )
+		h->newtio.c_iflag |= INPCK;
 
 	h->newtio.c_cc[VMIN] = 0;
 	h->newtio.c_cc[VTIME] = 5;	/* in units of 0.1 s */
