#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAP_SIZE (1 << 16)
#define GRN "\e[0;32m"
#define RESET "\e[0m"

#define DBGLOGN(...)  { printf(GRN); printf(__VA_ARGS__); printf(RESET); printf("\n"); }

extern int libQemuInit(int argc, char **argv, char **envp);

#define MAP_SIZE (1 << 16)

uint8_t  __afl_area_initial[MAP_SIZE];
unsigned char *afl_area_ptr = __afl_area_initial;

int main(int argc, char* argv[], char* envp[])
{
    DBGLOGN("==== SLOTH ====");

    memset(afl_area_ptr, 0, sizeof(uint8_t)* MAP_SIZE);

    libQemuInit(argc, argv, envp);
}