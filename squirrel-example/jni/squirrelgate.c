#include <stdarg.h> 
#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <squirrel.h>
#include <sqstdio.h> 
#include <sqstdaux.h> 

#ifdef SQUNICODE 
#define scvprintf vfwprintf
#else 
#define scvprintf vfprintf
#endif 

static const char *program =
	"local hello=\"hello\"; "
	"local world=\"world\"; "
	"return hello+\" \"+world;";
static int program_pos = 0;

// squirrel output goes to logcat.
void printfunc(HSQUIRRELVM v, const SQChar *s, ...) {
	va_list vl;
	va_start(vl, s);
	__android_log_vprint(ANDROID_LOG_INFO, "Squirrel", s, vl);
	va_end(vl);
}
void errorfunc(HSQUIRRELVM v,const SQChar *s, ...) {
	va_list vl;
	va_start(vl, s);
	__android_log_vprint(ANDROID_LOG_INFO, "Squirrel", s, vl);
	va_end(vl);
}

SQInteger program_reader(SQUserPointer p) {
	if (program_pos == strlen(program)) {
		return 0;
	}
	return program[program_pos++];
}

JNIEXPORT jstring JNICALL Java_com_cafbit_squirreltest_SquirrelGate_testSquirrel(JNIEnv *env, jclass jcls) {
	const SQChar *str = NULL;

	// initialize squirrel
	HSQUIRRELVM v; 
	v = sq_open(1024);
	sqstd_seterrorhandlers(v);
	sq_setprintfunc(v, printfunc,errorfunc);

	// compile our program
	sq_pushroottable(v);
	if (! SQ_SUCCEEDED(sq_compile(v, program_reader, 0, _SC("squirreltest"), SQTrue))) {
		goto finish;
	}
	// call our program
	sq_pushroottable(v);
	if (! SQ_SUCCEEDED(sq_call(v, 1, SQTrue, SQTrue))) {
		goto finish;
	}
	// regard the output
	if (! SQ_SUCCEEDED(sq_getstring(v, sq_gettop(v), &str))) {
		goto finish;
	}
	sq_pop(v,1);
	sq_pop(v,1);

	sq_close(v); 

finish:
	if (str == NULL) str = "ERROR";
	return (*env)->NewStringUTF(env, str);
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	return JNI_VERSION_1_4;
}

