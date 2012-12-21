LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := event.cpp

LOCAL_MODULE := mytest
LOCAL_MODULE_TAGS := eng

# for now, until I do a full rebuild.
#LOCAL_PRELINK_MODULE := false

LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libutils libui libbinder

LOCAL_CFLAGS += -Idalvik/libnativehelper/include/nativehelper -O0 -g -Wall -std=gnu++0x -lpthread

LOCAL_C_INCLUDES := \
    external/stlport/stlport \
    bionic \
    $(empty)

include $(BUILD_EXECUTABLE)

