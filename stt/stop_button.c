#include <stdio.h>
#include <stdlib.h>

void make_dat_file(char *file_name)
{
    FILE *f = fopen(file_name, "w");
    fprintf(f, "horsey will now speak");
    fclose(f);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("YOU WOT MATE\n Are you PUlling MY pisser?? gimme an argument.\n");
        return 1;
    }

    char *file_name = argv[1];
    printf("Yeah mate, we be saving to %s today\n", file_name);

    printf("WHACK ENTER TO STOP YOU PLUMMMMMMMMM\n");
    fgetc(stdin);
    printf("Yeah nice one me lad\n")
    return 0;
}
