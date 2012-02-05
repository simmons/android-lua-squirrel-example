package com.cafbit.squirreltest;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class SquirrelTestActivity extends Activity {
    
    static {
        System.loadLibrary("squirrel");
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        String output = SquirrelGate.testSquirrel();
        TextView tv = new TextView(this);
        tv.setText(output);
        setContentView(tv);
    }
}