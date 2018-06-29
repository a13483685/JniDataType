package com.example.administrator.jnidatatypedemo;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static final String TAG = MainActivity.class.getName();
    private final int GET_STRING = 1;
    private final int GET_INT_ARRAY = 2;
    private final int GET_STUDENT = 3;
    private final int GET_STUDENT_INFO_JNI = 4;
    public final int SET_STUDENT_INFO_JNI = 5;
    private static final int CALL_STATIC_METHOD = 6;
    private TextView tv;

    // Used to load the 'native-lib' library on application startup.

    static {
        System.loadLibrary("native-lib");
    }

    public Handler handler = new Handler() {

        @Override
        public void handleMessage(Message msg) {
            int what = msg.what;
            switch (what) {
                case GET_STRING:
                    String info = (String) msg.obj;
                    tv.setText(info);
                    handler.removeMessages(GET_STRING);
                    break;
                case GET_INT_ARRAY:
//                    int[] nums = (int[]) msg.obj;
                    tv.setText("nums is :" + msg.obj);
                    handler.removeMessages(GET_INT_ARRAY);
                    break;
                case GET_STUDENT:
                    tv.setText("student is :" + msg.obj.toString());
                    break;

                case GET_STUDENT_INFO_JNI:
                    tv.setText("student is :" + msg.obj.toString());
                    break;

                case SET_STUDENT_INFO_JNI:
                    tv.setText("student is :" + msg.obj.toString());
                    break;

                case CALL_STATIC_METHOD:
                    tv.setText("student is :" + msg.obj.toString());
                    break;
            }
            super.handleMessage(msg);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button btn1 = (Button) findViewById(R.id.getString);
        Button btn2 = (Button) findViewById(R.id.getIntArray);
        Button btn3 = (Button) findViewById(R.id.getInstantObj);
        Button btn4 = (Button) findViewById(R.id.getStaticObj);
        Button btn5 = findViewById(R.id.getStFromJni);
        Button btn6 = findViewById(R.id.getStInFoFromJni);
        Button btn7 = findViewById(R.id.setStInFoFromJni);
        Button btn8 = findViewById(R.id.call_static_method);

        tv = (TextView) findViewById(R.id.tv_msg);
        btn1.setOnClickListener(this);
        btn2.setOnClickListener(this);
        btn3.setOnClickListener(this);
        btn4.setOnClickListener(this);
        btn5.setOnClickListener(this);
        btn6.setOnClickListener(this);
        btn7.setOnClickListener(this);
        btn8.setOnClickListener(this);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int[] intArrayFromJNI(int[] nums);

    public native void getStatic(JavaClass javaClass);

    public native String getInstall();


    //构造方法
    public native Student accessConstructMethod();

    //JNI 调用对象
    public native String getNameAge(Student student);

    //JNI 给对象复制
    public native String setNameAge(Student student);

    //调用静态方法
    public native String getStaticInfo();


    @Override
    public void onClick(View view) {
        int id = view.getId();
        switch (id) {
            case R.id.getString:
                String string = stringFromJNI();
                Message msg = new Message();
                msg.what = GET_STRING;
                msg.obj = string;
                handler.sendMessage(msg);
                break;

            case R.id.getIntArray:
                int[] nums = {1, 2, 3};
                int[] nums1 = intArrayFromJNI(nums);
                Message msg1 = new Message();
                msg1.what = GET_INT_ARRAY;
                msg1.obj = nums1;
                handler.sendMessage(msg1);
                break;

            case R.id.getInstantObj:

                break;

            case R.id.getStaticObj:
                JavaClass javaClass = new JavaClass();
                getStatic(javaClass);//传进去的是一个实例化的对象

                break;

            case R.id.getStFromJni:
                Student jniNewObj = accessConstructMethod();
                String stuInfo = jniNewObj.toString();
                Message msg2 = new Message();
                msg2.what = GET_INT_ARRAY;
                msg2.obj = jniNewObj;
                handler.sendMessage(msg2);
                break;

            case R.id.getStInFoFromJni:
                Student student = new Student();
                student.setAge(12);
                student.setName("xie");
                String nameAge = getNameAge(student);
                Log.i(TAG, "Jni 初始的=" + nameAge);
                Message msg3 = new Message();
                msg3.what = GET_INT_ARRAY;
                msg3.obj = student;
                handler.sendMessage(msg3);
                break;
            case R.id.setStInFoFromJni:
                Student student1 = new Student();
                String info = setNameAge(student1);
                Message msg4 = new Message();
                msg4.what = SET_STUDENT_INFO_JNI;
                msg4.obj = student1;
                handler.sendMessage(msg4);
                break;

            case R.id.call_static_method:
                String info1 = getStaticInfo();
                Message msg5 = new Message();
                msg5.what = CALL_STATIC_METHOD;
                msg5.obj = info1;
                handler.sendMessage(msg5);
                break;
        }
    }
}
