#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <errno.h>
#include <ctype.h>

int validate_compressed_string(const char* str) {
    int expect_digit = 1;
    
    while (*str) {
        if (expect_digit) {
            if (!isdigit(*str)) return 0;
            expect_digit = 0;
        } else {
            if (!isalpha(*str)) return 0;
            expect_digit = 1;
        }
        str++;
    }
    return !expect_digit; // Последний символ должен быть буквой
}

int main(void) {
    char compressed[512];
    char decompressed[2048];
    int coid;
    long serv_pid;

    printf("Compression client. Enter server PID: ");
    scanf("%ld", &serv_pid);
    printf("Connecting to server PID: %ld\n", serv_pid);

    if ((coid = ConnectAttach(0, serv_pid, 1, 0, 0)) == -1) {
        perror("ConnectAttach");
        exit(EXIT_FAILURE);
    }

    printf("Enter compressed string (format like '3a2b1c'): ");
    scanf("%511s", compressed);
    
    if (!validate_compressed_string(compressed)) {
        fprintf(stderr, "Invalid compressed string format!\n");
        ConnectDetach(coid);
        exit(EXIT_FAILURE);
    }

    printf("Sending compressed string: \"%s\"\n", compressed);

    if (MsgSend(coid, compressed, strlen(compressed) + 1, decompressed, sizeof(decompressed)) == -1) {
        perror("MsgSend");
        ConnectDetach(coid);
        exit(EXIT_FAILURE);
    }

    printf("Server response (decompressed string): \"%s\"\n", decompressed);
    printf("Belova Ksenia Egorovna\nGroup: i914b\n);

    ConnectDetach(coid);
    return EXIT_SUCCESS;
}
