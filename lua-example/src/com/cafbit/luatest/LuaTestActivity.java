package com.cafbit.luatest;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class LuaTestActivity extends Activity {
    
    static {
        System.loadLibrary("lua");
    }
    
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        String output = LuaGate.testLua();
        TextView tv = new TextView(this);
        tv.setText(output);
        setContentView(tv);
    }
}