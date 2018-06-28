package com.example.administrator.jnidatatypedemo;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    private static final int GET_STRING = 1;
    private TextView tv;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    public Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            int what = msg.what;
            switch (what){
                case GET_STRING:
                    String info = (String) msg.obj;
                    tv.setText(info);
            }
            super.handleMessage(msg);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button btn = (Button) findViewById(R.id.getString);
        tv = (TextView) findViewById(R.id.tv_msg);
        btn.setOnClickListener(this);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    @Override
    public void onClick(View view) {
        int id = view.getId();
        switch (id){
            case R.id.getString:
                String string = stringFromJNI();
                Message msg = new Message();
                msg.what = GET_STRING;
                msg.obj = string;
                handler.sendMessage(msg);
                break;
        }
    }
}
