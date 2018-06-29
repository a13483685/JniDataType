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
    const char *cppString;
    jboolean isCopy;
    jstring javastring = env->NewStringUTF(hello.c_str());
    cppString = env->GetStringUTFChars(javastring, &isCopy);
    if (cppString != 0) {
        printf("Java String is : %s", cppString);
        LOGD("Java string is : %s", cppString);
    }
    env->ReleaseStringUTFChars(javastring, cppString);
    return javastring;
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_intArrayFromJNI(JNIEnv *env,
                                                                            jobject instance,
                                                                            jintArray nums_) {
    int nativeArray[3];

    env->GetIntArrayRegion(nums_, 0, 3, nativeArray);
    if (nativeArray != 0) {
        for (int i = 0; i < 3; i++) {
            nativeArray[i] = nativeArray[i] * 2;
            LOGD("jni num are : %d", nativeArray[i]);
        }
        env->SetIntArrayRegion(nums_, 0, 3, nativeArray);
    }

    return nums_;
//    env->ReleaseIntArrayElements(nums_,nativeArray,0);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_getInstall(JNIEnv *env,
                                                                       jobject instance) {

    // TODO
    jclass clazz;
    jfieldID installFieldId;
    clazz = env->GetObjectClass(instance);
    installFieldId = env->GetStaticFieldID(clazz, "instantFieldId", "Ljava/lang/String");


    return env->NewStringUTF(NULL);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_getStatic(JNIEnv *env,
                                                                      jobject instance,
                                                                      jobject javaClass) {
    // TODO
    jclass clazz;
    jfieldID installFieldId;
    clazz = env->GetObjectClass(javaClass);
    installFieldId = env->GetStaticFieldID(clazz, "staticFieldId", "Ljava/lang/String;");
    LOGD("getStatic is %s", installFieldId);
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_accessConstructMethod(JNIEnv *env,
                                                                                  jobject instance) {
    jclass jstudent;
    //获得类
    jstudent = env->FindClass("com/example/administrator/jnidatatypedemo/Student");
    //获得类的构造方法的id
    jmethodID studentCont = env->GetMethodID(jstudent, "<init>", "(Ljava/lang/String;I)V");
    const char *name = "JNI 构造方法，Nic";
    jstring jname = env->NewStringUTF(name);
    jint jage = 11;
    jobject student = env->NewObject(jstudent, studentCont, jname, jage);
    return student;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_getNameAge(JNIEnv *env,
                                                                       jobject instance,
                                                                       jobject student) {
    //1.先拿到对象的类
    jclass studentClass = env->GetObjectClass(student);
    //2.拿到对象方法d的id
    jmethodID methodID1 = env->GetMethodID(studentClass, "getName", "()Ljava/lang/String;");
    //3.根据id来执行方法
//    jstring jname = (jstring)env->CallObjectMethod(student,methodID1);

//    jmethodID methodID2 = env->GetMethodID(studentClass,"getAge","()I");

//    jmethodID getAge=env->GetMethodID(studentClass,"getAge","()I");

//
//    jint jage = (jint)env->CallObjectMethod(student,methodID2);

    jmethodID methodID3 = env->GetMethodID(studentClass, "toString", "()Ljava/lang/String;");

    jstring toString = (jstring) env->CallObjectMethod(student, methodID3);

    const char *tostr = env->GetStringUTFChars(toString, 0);
    return env->NewStringUTF(tostr);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_setNameAge(JNIEnv *env,
                                                                       jobject instance,
                                                                       jobject student) {
    jclass jclass1 = env->GetObjectClass(student);
    jmethodID jmethodID1 = env->GetMethodID(jclass1, "setName", "(Ljava/lang/String;)V");
    //設置名字
    jstring name = env->NewStringUTF("nic");
    env->CallVoidMethod(student, jmethodID1, name);
    //設置年齡
    jmethodID jmethodID2 = env->GetMethodID(jclass1, "setAge", "(I)V");

    jint age = 20;
    env->CallVoidMethod(student, jmethodID2, age);

    jmethodID methodID3 = env->GetMethodID(jclass1, "toString", "()Ljava/lang/String;");

    jstring toString = (jstring) env->CallObjectMethod(student, methodID3);

    const char *tostr = env->GetStringUTFChars(toString, 0);

    return env->NewStringUTF(tostr);
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_administrator_jnidatatypedemo_MainActivity_getStaticInfo(JNIEnv *env,
                                                                          jobject instance) {

    jclass jclass = env->FindClass("com/example/administrator/jnidatatypedemo/Student");
    jmethodID jmethodID = env->GetStaticMethodID(jclass,"getInfo","(Ljava/lang/String;I)Ljava/lang/String;");
    jstring name = env->NewStringUTF("NICHOLAS");
    int age =23;
    jstring msg = (jstring)env->CallStaticObjectMethod(jclass,jmethodID,name,age);
    const char * info = env->GetStringUTFChars(msg,0);
    return env->NewStringUTF(info);
}