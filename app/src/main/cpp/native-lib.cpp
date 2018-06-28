#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "myDemo-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    const char * cppString ;
    jboolean isCopy;
    jstring javastring = env->NewStringUTF(hello.c_str());
    cppString = env->GetStringUTFChars(javastring,&isCopy);
    if(cppString!=0){
        printf("Java String is : %s",cppString);
        LOGD("Java string is : %s",cppString);
    }
    env->ReleaseStringUTFChars(javastring,cppString);
    return javastring;
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_intArrayFromJNI(JNIEnv *env,
                                                                            jobject instance,
                                                                            jintArray nums_) {
    int nativeArray[3];

    env->GetIntArrayRegion(nums_,0,3,nativeArray);
    if(nativeArray!=0){
        for (int i=0;i<3 ;i++)
        {
            nativeArray[i] = nativeArray[i]*2;
            LOGD("jni num are : %d",nativeArray[i]);
        }
        env->SetIntArrayRegion(nums_,0,3,nativeArray);
    }

    return nums_;
//    env->ReleaseIntArrayElements(nums_,nativeArray,0);
}