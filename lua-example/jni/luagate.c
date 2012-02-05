#include <string.h>
#include <jni.h>
#include <lua/src/lua.h>
#include <lua/src/lauxlib.h>
#include <stdio.h>

#include <android/log.h>

/*
 * Stolen from lauxlib.c for convenience.
 */
static void *l_alloc (void *ud, void *ptr, size_t osize, size_t nsize) {
  (void)ud;
  (void)osize;
  if (nsize == 0) {
    free(ptr);
    return NULL;
  }
  else
    return realloc(ptr, nsize);
}

JNIEXPORT jstring JNICALL Java_com_cafbit_luatest_LuaGate_testLua(JNIEnv *env, jclass jcls) {
	lua_State *L;

	__android_log_print(ANDROID_LOG_INFO, "LuaTest", "Testing Lua");

	L = lua_newstate(l_alloc, NULL);
	luaL_dostring(L, "hello = \"hello\"\n world = \"world\"\n text = hello .. \" \" .. world\n");
	lua_getglobal(L, "text");
	const char *str = lua_tostring(L, -1);
	__android_log_print(ANDROID_LOG_INFO, "LuaTest", "output: %s", str);
	return (*env)->NewStringUTF(env, str);
}

/*
 * Needed to allow the .so to load properly.
 */
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	return JNI_VERSION_1_4;
}

