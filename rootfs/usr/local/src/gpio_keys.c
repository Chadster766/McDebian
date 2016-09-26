#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

void handler (int sig)
{
	printf ("\nexiting...(%d)\n", sig);
	exit (0);
}

void perror_exit (char *error)
{
	perror (error);
	handler (9);
}

int main (int argc, char *argv[])
{
	struct input_event ev[64];
	int fd, rd, value, size = sizeof (struct input_event);
	char name[256]= "\0";;
	char device[19]= "/dev/input/event0\0";
	char* led_wps_amber="/sys/class/leds/mamba\\:amber\\:wps/brightness\0";
	char* led_wps_white="/sys/class/leds/mamba\\:white\\:wps/brightness\0";
	char* led_pwr="/sys/class/leds/mamba\\:white\\:power/brightness\0";
	char* wps="/usr/local/sbin/wps&\0";
	char cmd[256]="\0";
	int WPS_KEY=0;
	int RESET_KEY=0;
    	FILE* fichier = NULL;


	//Open Device
	if ((fd = open (device, O_RDONLY)) == -1){
		printf ("%s is not a valid device.n", device);
		return 1;
	}
	//Print Device Name
	ioctl (fd, EVIOCGNAME (sizeof (name)), name);
	printf ("Reading From : %s (%s)\n", device, name);


	while (1){
		strcpy(cmd,"");
		WPS_KEY=0;
		if ((rd = read (fd, ev, size * 64)) < size)
			perror_exit ("read()");

		fichier = fopen("/var/run/gpio_keys", "w");

		switch(ev[0].code){
			case 529:/*WPS 0x0211*/
				if (ev[0].value==1){ // press

					strcpy(cmd,"echo 255>");
					strcat(cmd,led_wps_white);
					system(cmd);

					if (fichier != NULL){
						fprintf(fichier, "%d\n", ev[0].code);
					}
				}
				else {// relaxe

					strcpy(cmd,"echo 0 >");
					strcat(cmd,led_wps_white);
					system(cmd);
					system(wps);
				}

			break;
			case 408:/*RESET 0x0198*/
				if (ev[0].value==1){ // press

					strcpy(cmd,"echo 0 >");
					strcat(cmd,led_pwr);
					system(cmd);

					if (fichier != NULL){
						fprintf(fichier, "%d\n", ev[0].code);
					}
				}
				else {// relaxe

					strcpy(cmd,"echo 255 >");
					strcat(cmd,led_pwr);
					system(cmd);
				}
			break;
			default:
			break;
		}

		if (fichier != NULL){
			fclose(fichier);
		}

	}
	return 0;
}
