#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define FATFS_BS 512

typedef uint8_t BYTE;

int check_sig(BYTE sig[]);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./recover card.raw\n");

        return 1;
    }

    FILE *strg = fopen(argv[1], "r");

    if (strg == NULL) {
        printf("Raw file couldn't be opened\n");
        fclose(strg);

        return 1;
    }

    BYTE *block = calloc(1, sizeof(int[FATFS_BS]));
    FILE *img_out;
    int  is_open = 0;
    int  fread_ret;
    int  fc = 0;
    char fn[8];

    while (!feof(strg)) {
        // Read from file stream, moving forward by FAT_fs' block size
        fread_ret = fread(block, sizeof *block, FATFS_BS, strg);

        // If current FAT block starts with JPG initials, open out image file
        if (check_sig(block)) {
            if (img_out != NULL) {
                fclose(img_out);
                is_open = 0;
            }

            sprintf(fn, "%.3i.jpg", fc++);
            img_out = fopen(fn, "w");
            is_open = 1;
        }

        // Write however many bytes were read to current opened file
        if (is_open) {
			// TODO Check backwards for byte != 0x00
            int fwrite_ret = fwrite(block, sizeof *block, fread_ret, img_out);
        }
    }

    if (is_open && fread_ret < 512) {
        fclose(img_out);
    }

    free(block);
    fclose(strg);

    return 0;
}

int check_sig(BYTE sig[])
{
    if (sig[0] == 0xff && sig[1] == 0xd8 && sig[2] == 0xff) {
        for (BYTE j = 0xe0; j < 0xf0; ++j) {
            if (sig[3] == j) {
                return 1;
            }
        }
    }

    return 0;
}

