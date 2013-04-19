#LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS)

#LOCAL_MODULE := libpython2.7-prebuilt
#LOCAL_SRC_FILES := /../../build/lib/libpython2.7.so
#LOCAL_EXPORT_C_INCLUDES := \
$(LOCAL_PATH)/../../build/include/python2.7 \
$(LOCAL_PATH)/../../Python/Include
#LOCAL_LDLIBS := -llog -lm

#include $(PREBUILT_SHARED_LIBRARY)
