package com.example.myfirstjni;

import android.util.Log;

/**
 * 测试jni和java相互的调用
 *
 * 在本目录下，命令行运行：
 * 1.javac TestJni.java     生成class文件，或者在编译好该文件的目录下运行
 * 2.javap -s -private TestJni  查看文件的签名信息
 *  信息如下
 *  Compiled from "TestJni.java"
 * public class com.example.myfirstjni.TestJni {
 *   private static final java.lang.String TAG;
 *     descriptor: Ljava/lang/String;
 *   public com.example.myfirstjni.TestJni();
 *     descriptor: ()V
 *
 *   public static native void sayHello();
 *     descriptor: ()V
 *
 *   public static native java.lang.String getStringForC();
 *     descriptor: ()Ljava/lang/String;
 *
 *   public static void CCallJava(java.lang.String);
 *     descriptor: (Ljava/lang/String;)V
 *
 *   private static void test();
 *     descriptor: ()V
 *
 *   static {};
 *     descriptor: ()V
 */
public class TestJni {
    private static final String TAG = "TestJni";

    static {
        System.loadLibrary("myfirstjni");
    }

    /**
     * 调用C/C++
     */
    public static native void sayHello();

    public static native String getStringForC();

    /**
     * C/C++代码调用
     * @param str
     */
    public static void CCallJava(String str) {
        Log.d(TAG, "C++ str = " +str);
    }

    private static void test() {
        Log.i(TAG, "test test test ...");
    }
}
