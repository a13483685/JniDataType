package com.example.administrator.jnidatatypedemo;

import android.util.Log;

class Student {
    public final static String TAG = "Student";
    String name;
    int age;

    public Student() {
    }
    public Student(String name, int age) {
        this.name = name;
        this.age = age;
    }
    public int getAge() {
        Log.i(TAG, "getAge=" + age);
        return age;
    }
    public void setAge(int age) {
        this.age = age;
        Log.i(TAG, "setAge=" + age);
    }
    public String getName() {
        Log.i(TAG, "getName=" + name);
        return name;
    }
    public void setName(String name1) {
        this.name = name1;
        Log.i(TAG, "setName=" + name);
    }
    @Override
    public String toString() {
        String str = "name=" + name + " age=" + age;
        return str;
    }
    public static String getInfo(String name, int age) {
        String str = "静态方法 name=" + name + " age=" + age;
        Log.i(TAG, "getInfo=" + str);
        return str;
    }
}
