#include <jni.h>
#include "log.h"

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("myfirstjni");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("myfirstjni")
//      }
//    }
void callOtherJava(JNIEnv *env);

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myfirstjni_TestJni_sayHello(JNIEnv *env, jclass clazz) {
    LOGI("Hello World from C/C++");
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myfirstjni_TestJni_getStringForC(JNIEnv *env, jclass clazz) {
    const char* name = "str from C/C++";
    jstring arg = env->NewStringUTF(name);

    // C/C++回调Java
    jmethodID cCallJavaID = env->GetStaticMethodID(clazz, "CCallJava", "(Ljava/lang/String;)V");
    if (cCallJavaID == 0){
        LOGE("failed to find method in java!");
    } else {
        LOGE("find method succeed!");
        env->CallStaticVoidMethod(clazz, cCallJavaID, arg);
    }

    callOtherJava(env);
    return arg;
}

// 调用其他Java类方法
void callOtherJava(JNIEnv *env) {
    jclass personClazz = env->FindClass("com/example/myfirstjni/Person");
    if (personClazz == NULL) {
        LOGE("personClazz is NULL");
        return;
    }
    jmethodID toStringID = env->GetMethodID(personClazz, "toString", "()Ljava/lang/String;");
    if (toStringID == 0) {
        LOGE("failed to find toStringID method in java!");
        return;
    }
    // 获取类的构造函数，记住这里是调用无参的构造函数
    jmethodID constructNoArgs = env->GetMethodID(personClazz, "<init>", "()V");
    if (constructNoArgs == 0) {
        LOGE("failed to find constructNoArgs method in java!");
        return;
    }
    // 创建一个新的对象
    jobject personObj = env->NewObject(personClazz, constructNoArgs);
    jobject result = env->CallObjectMethod(personObj, toStringID);
    LOGI("Person toString = %s", env->GetStringUTFChars(static_cast<jstring>(result), 0));
}