LOCAL_PATH := $(call my-dir)
FULL_PATH_TO_ROOTFS := /Users/ant4g0nist/Sloth/resources/rootfs/

include $(CLEAR_VARS)
LOCAL_MODULE    := libhwui 
LOCAL_SRC_FILES := $(FULL_PATH_TO_ROOTFS)/system/lib64/libhwui.so
include $(PREBUILT_SHARED_LIBRARY)

### build your lib ###
include $(CLEAR_VARS)
LOCAL_LDLIBS := -lhwui -L$(FULL_PATH_TO_ROOTFS)/system/lib64/ 
LOCAL_MODULE := libBooFuzz
LOCAL_SRC_FILES := lib/fuzz.cpp 
include $(BUILD_SHARED_LIBRARY)

# ### build the main ###
include $(CLEAR_VARS)
LOCAL_LDLIBS := -llog -landroidicu -lz -lGLESv1_CM -lGLESOverlay -lEGL -lGLESv3 -lBooFuzz -L../libs/arm64-v8a/ -landroidicu -lhwui -L$(FULL_PATH_TO_ROOTFS)/system/lib64/ -Wl,-rpath-link=$(FULL_PATH_TO_ROOTFS)/system/lib64/ -Wl,--dynamic-linker=/rootfs/system/bin/linker64
LOCAL_MODULE := boofuzz
LOCAL_SRC_FILES := boo.cpp

include $(BUILD_EXECUTABLE)