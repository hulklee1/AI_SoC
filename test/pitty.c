#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>

#define SERIAL_PORT "/dev/serial0"
#define BAUDRATE B9600

int serial_fd;

void *uart_read_thread(void *arg) {
    char buf[256];
    while (1) {
        int len = read(serial_fd, buf, sizeof(buf) - 1);
        if (len > 0) {
            buf[len] = '\0';
            printf("\n[RX] %s", buf);
            fflush(stdout);
        }
    }
    return NULL;
}

int main() {
    struct termios options;

    serial_fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
    if (serial_fd < 0) {
        perror("Serial port open error");
        return 1;
    }

    tcgetattr(serial_fd, &options);
    cfsetispeed(&options, BAUDRATE);
    cfsetospeed(&options, BAUDRATE);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag |= CREAD | CLOCAL;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_oflag &= ~OPOST;
    tcsetattr(serial_fd, TCSANOW, &options);

    // RX 수신 쓰레드 
    pthread_t tid;
    pthread_create(&tid, NULL, uart_read_thread, NULL);

    // 
    char input[256];
    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) != NULL) {
            write(serial_fd, input, strlen(input));
        }
    }

    close(serial_fd);
    return 0;
}
