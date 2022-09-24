package com.example.myfirstjni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tvInfo = findViewById(R.id.tv_info);
        TestJni.sayHello();
        String cString = TestJni.getStringForC();
        tvInfo.setText(cString);
    }
}