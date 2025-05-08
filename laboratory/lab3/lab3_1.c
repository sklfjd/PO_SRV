#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

void decompress_string(const char* input, char* output) {
    int count = 0;
    int pos = 0;
    char current;
    
    while (*input) {
        if (isdigit(*input)) {
            count = count * 10 + (*input - '0');
            input++;
        } else if (isalpha(*input)) {
            current = *input++;
            for (int i = 0; i < count; i++) {
                output[pos++] = current;
            }
            count = 0;
        } else {
            input++; // Пропускаем невалидные символы
        }
    }
    output[pos] = '\0';
}

void server(void) {
    int rcvid;
    int chid;
    char compressed[512];
    char decompressed[2048]; // Больше места для разжатой строки

    printf("Decompression server started\n");

    if ((chid = ChannelCreate(0)) == -1) {
        perror("ChannelCreate");
        exit(EXIT_FAILURE);
    }

    printf("Channel id: %d\n", chid);
    printf("Server PID: %d\n", getpid());

    while (1) {
        rcvid = MsgReceive(chid, compressed, sizeof(compressed), NULL);
        if (rcvid == -1) {
            perror("MsgReceive");
            continue;
        }

        printf("Received compressed string: \"%s\"\n", compressed);

        decompress_string(compressed, decompressed);
        printf("Decompressed message: \"%s\"\n", decompressed);

        if (MsgReply(rcvid, 0, decompressed, strlen(decompressed) + 1) == -1) {
            perror("MsgReply");
        }
    }
}

int main(void) {
    printf("Decompression server program\n");
    printf("Belova Ksenia Egorovna\nGroup: i914b\n");
    server();
    return EXIT_SUCCESS;
}
