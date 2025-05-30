#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main() {
    int serial_port = open("/dev/serial0", O_RDWR | O_NOCTTY);
    if (serial_port < 0) {
        perror("Error opening serial port");
        return 1;
    }
    // grep -rnw /path/to/search -e "PARENB" --include="*.h"
    struct termios options;
    tcgetattr(serial_port, &options);

    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CREAD | CLOCAL;

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_oflag &= ~OPOST;

    tcsetattr(serial_port, TCSANOW, &options);

    char read_buf[256];
    memset(read_buf, 0, sizeof(read_buf));

    printf("Waiting for UART response...\n");

    int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
    if (num_bytes < 0) {
        perror("UART read error");
        close(serial_port);
        return 1;
    }

    printf("Received (%d bytes): %s\n", num_bytes, read_buf);

    close(serial_port);
    return 0;
}
