#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
int i;
int fd;
int left_speed;
char buf[16];
char temperature[16];
struct termios opt;
int init()
{
	int ret;
	int len;
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd <0){
		printf("Can't open /dev/ttyUSB0\n");
		return 1;
	}
	tcgetattr(fd, &opt);
	cfsetispeed(&opt, 9600);
	cfsetospeed(&opt, 9600);

	opt.c_iflag = 0;
	opt.c_iflag |= IXON;
	opt.c_iflag |= IGNBRK;
	opt.c_iflag |= BRKINT;
	opt.c_iflag |= IMAXBEL;

	opt.c_oflag = 0;
	opt.c_oflag |= OPOST;
	opt.c_oflag |= ONLCR;

	opt.c_cflag = 0;
	opt.c_cflag |= B9600;
	opt.c_cflag |= CS8;
	opt.c_cflag |= CRTSCTS;

	opt.c_lflag = 0;
	opt.c_lflag |= ISIG;
	opt.c_lflag |= ICANON;
	opt.c_lflag |= ECHO;
	opt.c_lflag |= ECHOE;
	opt.c_lflag |= ECHOK;
	opt.c_lflag |= ECHOCTL;
	opt.c_lflag |= ECHOKE;
	opt.c_lflag |= IEXTEN;
	opt.c_lflag |= NOFLSH;

	ret = tcsetattr(fd, TCSANOW, &opt);
	if(ret < 0){
		printf("Can't set attr\n");
		return 2;
	}

	ret = tcflush(fd, TCIOFLUSH);
	if(ret < 0){
		printf("Can't flush\n");
		return 3;
	}

	write(fd, "A", 1);
	return 0;
}
void read_info()
{
	int len;
	int flag = 0;
	while(1)
	{
		len = read(fd,buf,16);
		if(len > 0)
		{
			if(flag == 0)
			{
				flag++;
				left_speed = atoi(buf);
		/*		printf("left: %d\n",left_speed);*/
			}
			else if(flag == 1)
			{
				flag++;
				strcpy(temperature,buf);
		/*		for(i = 0; i < len;++i)
					printf("%c",temperature[i]);*/
			}
		}
		if(flag == 2)
			break;
	}
}

int main()
{
	init();
	while(1)
	{
		read_info();
		printf("left speed: %d\n",left_speed);
		printf("temperature: %s\n",temperature);
	}
	return 0;
}
