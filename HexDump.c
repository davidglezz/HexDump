/***************************************************************************
* @ProjectName	HexDump													   *
* @Description	Simple hexadecimal file viewer							   *
* @Author		David Gonzalez Garcia.									   *
* @Web			davidxl.es												   *
* @license		No license, Open source									   *
* @date			10-10-2010												   *
* @version		1.2														   *
***************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage:  HexDump file  \n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file)
    {
       printf("Can't open the file.\n");
       return 2;
    }

    char d[] = "                \0";
    unsigned int i, bytes, index = 0;

    while (bytes = fread(d, 1, 16, file))
    {
        printf("%08X%c", index, 179);

        index += 16;

        for (i = 0; i < bytes; i++)
        {
            printf(" %02X", (unsigned char)(d[i]));

            if ((i + 1) % 4 == 0)
				printf(" ");

            if (d[i] == 127 || d[i] < -127 || (d[i] >= 0 && d[i] <= 31))
				d[i] = '.';
        }

        if (bytes < 16)
        {
            for(i = bytes; i < 16; i++)
            {
                printf("   ");
                if ((i + 1) % 4 == 0)
					printf(" ");
            }
            d[bytes] = '\0';
        }

        printf("%c%s\n", 179, d);
    }

    fclose(file);
    return 0;
}
