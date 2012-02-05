
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := squirrel
LOCAL_SRC_FILES := squirrelgate.c squirrel/sqapi.cpp squirrel/sqbaselib.cpp squirrel/sqfuncstate.cpp squirrel/sqdebug.cpp squirrel/sqlexer.cpp squirrel/sqobject.cpp squirrel/sqcompiler.cpp squirrel/sqstate.cpp squirrel/sqtable.cpp squirrel/sqmem.cpp squirrel/sqvm.cpp squirrel/sqclass.cpp sqstdlib/sqstdblob.cpp sqstdlib/sqstdio.cpp sqstdlib/sqstdstream.cpp sqstdlib/sqstdmath.cpp sqstdlib/sqstdsystem.cpp sqstdlib/sqstdstring.cpp sqstdlib/sqstdaux.cpp sqstdlib/sqstdrex.cpp
LOCAL_CFLAGS := -I$(LOCAL_PATH)/include
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

