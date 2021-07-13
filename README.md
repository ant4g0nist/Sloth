# Sloth 🦥
   Sloth is a fuzzing setup that makes use of libFuzzer and QEMU’s user-mode emulation (`qemu/linux-user`) on x86_64/aarch64 host to emulate aarch64 Android libraries to fuzz the target Android native library.

# Introduction
Sloth makes use of libFuzzer and QEMU’s user-mode emulation (`qemu/linux-user`) on x86_64/aarch64 host to emulate aarch64 Android libraries to fuzz the target Android native library. Internals of why and what about Sloth are available at : https://fuzzing.science/page/fuzzing-android-native-libraries-with-libfuzzer-qemu/

High level execution flow of QEMU user-mode emulation:

![QEMU linux-user flow](./resources/qemu_linux-user_main.png)

# Build Instructions

To build and launch the docker container:
~~~sh
export image="sloth:v1"
docker build -t $image .
docker run --rm -v `pwd`/resources/rootfs:/rootfs -v `pwd`/resources/examples:/examples -it $image bash
~~~

Check `resources/examples` folder to build an example android native library.

## Usage:

You can copy the /system/ from a rooted Android device into `resources/rootfs` directory.

In the examples folder, check the signature of `libQemuFuzzerTestOneInput` function in `jni/lib/fuzz.cpp` file. This function is equivalent to `LLVMFuzzerTestOneInput` function that we define when creating any libFuzzer harness.

To compile the sample from examples:

~~~
cd examples/jni
ndk-build
~~~

This builds and generates libBooFuzz.so and an executable boofuzz.
Copy `libBooFuzz.so` to `rootfs/system/lib64/` and `boofuzz` to `/rootfs/`

~~~sh
root@b7d9fb6a454e:/examples/jni# make
root@b7d9fb6a454e:/examples/jni# cp ../libs/arm64-v8a/libBooFuzz.so /rootfs/system/lib64/
root@b7d9fb6a454e:/examples/jni# cp ../libs/arm64-v8a/boofuzz /rootfs/
root@b7d9fb6a454e:/examples/jni# 
~~~

Add your target library path that exports `libQemuFuzzerTestOneInput` (libBooFuzz.so in our example) to `SLOTH_TARGET_LIBRARY` env variable.

To start fuzzing:
~~~sh
root@45d7511a2802:/sloth/src# SLOTH_TARGET_LIBRARY=/rootfs/system/lib64/libBooFuzz.so ./sloth /rootfs/boofuzz test/
==== SLOTH ====
WARNING: Failed to find function "__sanitizer_acquire_crash_state".
WARNING: Failed to find function "__sanitizer_print_stack_trace".
WARNING: Failed to find function "__sanitizer_set_death_callback".
INFO: Running with entropic power schedule (0xFF, 100).
INFO: Seed: 557648595
INFO: 65536 Extra Counters
INFO:        1 files found in test/
INFO: -max_len is not provided; libFuzzer will not generate inputs larger than 4096 bytes
INFO: seed corpus: files: 1 min: 6b max: 6b total: 6b rss: 66Mb
#2	INITED ft: 3 corp: 1/6b exec/s: 0 rss: 66Mb
#10	REDUCE ft: 3 corp: 1/4b lim: 6 exec/s: 0 rss: 66Mb L: 4/4 MS: 3 CopyPart-CopyPart-CrossOver-
#11	REDUCE ft: 3 corp: 1/2b lim: 6 exec/s: 0 rss: 66Mb L: 2/2 MS: 1 EraseBytes-
#12	REDUCE ft: 3 corp: 1/1b lim: 6 exec/s: 0 rss: 66Mb L: 1/1 MS: 1 EraseBytes-
#4655	REDUCE ft: 5 corp: 2/37b lim: 48 exec/s: 0 rss: 66Mb L: 36/36 MS: 3 ShuffleBytes-ChangeBit-InsertRepeatedBytes-
#4676	REDUCE ft: 5 corp: 2/20b lim: 48 exec/s: 0 rss: 66Mb L: 19/19 MS: 1 EraseBytes-
#4694	REDUCE ft: 5 corp: 2/11b lim: 48 exec/s: 0 rss: 66Mb L: 10/10 MS: 3 ChangeBinInt-ChangeBinInt-EraseBytes-
#4710	REDUCE ft: 5 corp: 2/7b lim: 48 exec/s: 0 rss: 66Mb L: 6/6 MS: 1 EraseBytes-
#4736	REDUCE ft: 5 corp: 2/5b lim: 48 exec/s: 0 rss: 66Mb L: 4/4 MS: 1 EraseBytes-
#4830	REDUCE ft: 5 corp: 2/3b lim: 48 exec/s: 0 rss: 66Mb L: 2/2 MS: 4 ChangeByte-CopyPart-ChangeByte-CrossOver-
#4896	REDUCE ft: 5 corp: 2/2b lim: 48 exec/s: 0 rss: 66Mb L: 1/1 MS: 1 EraseBytes-
#36480	REDUCE ft: 7 corp: 3/4b lim: 357 exec/s: 0 rss: 66Mb L: 2/2 MS: 4 ShuffleBytes-CrossOver-ShuffleBytes-ChangeByte-
#89256	NEW    ft: 9 corp: 4/26b lim: 877 exec/s: 0 rss: 66Mb L: 22/22 MS: 1 InsertRepeatedBytes-
#89282	REDUCE ft: 9 corp: 4/21b lim: 877 exec/s: 0 rss: 66Mb L: 17/17 MS: 1 EraseBytes-
#89288	REDUCE ft: 9 corp: 4/16b lim: 877 exec/s: 0 rss: 66Mb L: 12/12 MS: 1 EraseBytes-
#89407	REDUCE ft: 9 corp: 4/14b lim: 877 exec/s: 0 rss: 66Mb L: 10/10 MS: 4 ChangeBinInt-InsertByte-ChangeBinInt-EraseBytes-
#89458	REDUCE ft: 9 corp: 4/13b lim: 877 exec/s: 0 rss: 66Mb L: 9/9 MS: 1 EraseBytes-
#89480	REDUCE ft: 9 corp: 4/11b lim: 877 exec/s: 0 rss: 66Mb L: 7/7 MS: 2 ShuffleBytes-EraseBytes-
#89496	REDUCE ft: 9 corp: 4/10b lim: 877 exec/s: 0 rss: 66Mb L: 6/6 MS: 1 EraseBytes-
#89647	REDUCE ft: 9 corp: 4/8b lim: 877 exec/s: 0 rss: 66Mb L: 4/4 MS: 1 EraseBytes-
#92983	REDUCE ft: 9 corp: 4/7b lim: 904 exec/s: 0 rss: 66Mb L: 3/3 MS: 1 EraseBytes-
#350518	REDUCE ft: 11 corp: 5/77b lim: 3458 exec/s: 350518 rss: 66Mb L: 70/70 MS: 2 ShuffleBytes-InsertRepeatedBytes-
#350594	REDUCE ft: 11 corp: 5/44b lim: 3458 exec/s: 350594 rss: 66Mb L: 37/37 MS: 1 EraseBytes-
#350611	REDUCE ft: 11 corp: 5/28b lim: 3458 exec/s: 350611 rss: 66Mb L: 21/21 MS: 2 ChangeBinInt-EraseBytes-
#350787	REDUCE ft: 11 corp: 5/26b lim: 3458 exec/s: 350787 rss: 66Mb L: 19/19 MS: 1 EraseBytes-
#350994	REDUCE ft: 11 corp: 5/22b lim: 3458 exec/s: 350994 rss: 66Mb L: 15/15 MS: 2 InsertByte-EraseBytes-
#351305	REDUCE ft: 11 corp: 5/21b lim: 3458 exec/s: 351305 rss: 66Mb L: 14/14 MS: 1 EraseBytes-
#351466	REDUCE ft: 11 corp: 5/19b lim: 3458 exec/s: 351466 rss: 66Mb L: 12/12 MS: 1 EraseBytes-
#351487	REDUCE ft: 11 corp: 5/18b lim: 3458 exec/s: 351487 rss: 66Mb L: 11/11 MS: 1 EraseBytes-
#351753	REDUCE ft: 11 corp: 5/16b lim: 3458 exec/s: 351753 rss: 66Mb L: 9/9 MS: 1 EraseBytes-
#351760	REDUCE ft: 11 corp: 5/15b lim: 3458 exec/s: 351760 rss: 66Mb L: 8/8 MS: 2 ChangeBit-EraseBytes-
#351867	REDUCE ft: 11 corp: 5/13b lim: 3458 exec/s: 351867 rss: 66Mb L: 6/6 MS: 2 ChangeBit-EraseBytes-
#352673	REDUCE ft: 11 corp: 5/12b lim: 3458 exec/s: 352673 rss: 66Mb L: 5/5 MS: 1 EraseBytes-
#524288	pulse  ft: 11 corp: 5/12b lim: 4096 exec/s: 262144 rss: 66Mb
#1048576	pulse  ft: 11 corp: 5/12b lim: 4096 exec/s: 209715 rss: 66Mb
==17== ERROR: libFuzzer: deadly signal
NOTE: libFuzzer has rudimentary signal handlers.
      Combine libFuzzer with AddressSanitizer or similar for better crash reports.
SUMMARY: libFuzzer: deadly signal
MS: 2 CMP-InsertRepeatedBytes- DE: "\x18\xd6^\x04U\x00\x00\x00"-; base unit: 4504839cf31d63eae201804d840610ae0ffcecea
0xde,0xad,0xbe,0x6f,0xef,0x18,0xd6,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,0x5e,0x4,0x55,0x0,0x0,0x0,
\xde\xad\xbeo\xef\x18\xd6\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca^\x04U\x00\x00\x00
artifact_prefix='./'; Test unit written to ./crash-7ac2928ac40e554032d95ebc28cdccd7ee133b1a
Base64: 3q2+b+8Y1srKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKysrKyl4EVQAAAA==

root@c4627f563a99:/rootfs/src# ls
Makefile  crash-7ac2928ac40e554032d95ebc28cdccd7ee133b1a  fuzzer  qemu  sloth  sloth.c  test

root@45d7511a2802:/sloth/src# xxd crash-7ac2928ac40e554032d95ebc28cdccd7ee133b1a 
00000000: dead be6f ef18 d6ca caca caca caca caca  ...o............
00000010: caca caca caca caca caca caca caca caca  ................
00000020: caca caca caca caca caca caca caca caca  ................
00000030: caca caca caca caca caca caca caca caca  ................
00000040: caca caca caca caca caca caca caca caca  ................
00000050: caca caca caca caca 5e04 5500 0000       ........^.U...
~~~

![](resources/demo.gif)

Happy Fuzzing :)

## TODO
- [x] Fix signal handling in QEMU for libFuzzer to handle
- [x] Use QEMU as a library
- [ ] Fuzzing support for Android JNI libraries
- [ ] Make sure this is thread safe since I moved some variables to global.
- [ ] Add CMP coverage
- [ ] Add ASAN
