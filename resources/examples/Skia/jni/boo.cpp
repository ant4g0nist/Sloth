// extern "C" {
    #include "lib/fuzz.h"
// }

#include <stdio.h>

int main(int argc, char** argv) {
    // libQemuFuzzerTestOneInput((const uint8_t*)&"voila", 10);
    const uint8_t data = 0;
    libQemuFuzzerTestOneInput(&data, 1);
}