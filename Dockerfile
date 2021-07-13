FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NONINTERACTIVE_SEEN true

RUN apt-get update -y -q && \
    apt-get upgrade -y && \
    apt-get install -y git && \
    apt-get autoremove -y

RUN apt update -y
RUN apt-get install -y build-essential libtool-bin libglib2.0 wget autoconf automake git bison subversion curl subversion clang make unzip

WORKDIR /sloth/src
WORKDIR /setup

ENV SLOTH_WORK_DIR=/sloth/src
ENV ANDROID_NDK_HOME=/opt/android-ndk

WORKDIR ${SLOTH_WORK_DIR}
# clone qemu and apply Sloth patches 
RUN git clone --depth 1 --branch v5.1.0 https://github.com/qemu/qemu
RUN svn checkout https://github.com/llvm/llvm-project/branches/release/12.x/compiler-rt/lib/fuzzer

WORKDIR $SLOTH_WORK_DIR

RUN curl -O https://dl.google.com/android/repository/android-ndk-r21d-linux-x86_64.zip
RUN unzip android-ndk-r21d-linux-x86_64.zip
RUN mv android-ndk-r21d /opt/android-ndk
RUN rm android-ndk-r21d-linux-x86_64.zip

ENV ANDROID_NDK_HOME /opt/android-ndk

ENV PATH ${PATH}:${ANDROID_NDK_HOME}

RUN apt-get update -y
ADD src/sloth.c /sloth/src/
ADD src/Makefile /sloth/src/

ADD resources/patches/qemu.patch /setup
WORKDIR $SLOTH_WORK_DIR/qemu/
RUN git apply --stat /setup/qemu.patch && git apply --check /setup/qemu.patch && git apply /setup/qemu.patch

# clone libfuzzer and apply Sloth patches 
WORKDIR $SLOTH_WORK_DIR/fuzzer/
ADD resources/patches/libfuzzer.patch /setup
RUN git apply --stat /setup/libfuzzer.patch && git apply --check /setup/libfuzzer.patch && git apply /setup/libfuzzer.patch

WORKDIR /sloth/src
RUN make
