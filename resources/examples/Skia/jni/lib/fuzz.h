#ifndef FUZZ_H
#define FUZZ_H

#include <stdint.h>

extern "C" int libQemuFuzzerTestOneInput(const uint8_t *Data, size_t Size);

#endif