SLOTH_WORK_DIR=/sloth/src
ANDROID_NDK_HOME=/opt/android-ndk

cd $SLOTH_WORK_DIR
# clone qemu and apply Sloth patches 
git clone --depth 1 --branch v5.1.0 https://github.com/qemu/qemu
svn checkout https://github.com/llvm/llvm-project/branches/release/12.x/compiler-rt/lib/fuzzer

cd $SLOTH_WORK_DIR/qemu/
git apply --stat /setup/qemu.patch && git apply --check /setup/qemu.patch && git apply /setup/qemu.patch

# clone libfuzzer and apply Sloth patches 
cd $SLOTH_WORK_DIR/fuzzer/
git apply --stat /setup/libfuzzer.patch && git apply --check /setup/libfuzzer.patch && git apply /setup/libfuzzer.patch

cd $SLOTH_WORK_DIR

curl -O https://dl.google.com/android/repository/android-ndk-r21d-linux-x86_64.zip
unzip android-ndk-r21d-linux-x86_64.zip
mv android-ndk-r21d /opt/android-ndk
rm android-ndk-r21d-linux-x86_64.zip