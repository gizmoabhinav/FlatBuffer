/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.hellojni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.example.hellojni.Repos.ReposList;

import java.nio.ByteBuffer;

public class HelloJni extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hello_jni);
        TextView tv = (TextView)findViewById(R.id.hello_textview);
        TextView tv2 = (TextView)findViewById(R.id.hello_textview2);
        load();
        long start = System.currentTimeMillis();
        byte[] bytearray = fbFromJNI();
        ByteBuffer bb = ByteBuffer.wrap(bytearray);
        ReposList reposList = ReposList.getRootAsReposList(bb);
        long end = System.currentTimeMillis();
        tv.setText( "time taken with flatbuffer : "+(end-start)+" ms");
        start = System.currentTimeMillis();
        String jsonData = jaFromJNI();
        com.example.hellojni.ReposNormal.ReposList reposList1 = new com.example.hellojni.ReposNormal.ReposList().fromJson(jsonData);
        end = System.currentTimeMillis();
        tv2.setText( "time taken with json : "+(end-start)+" ms");
    }
    public native void load();
    public native byte[] fbFromJNI();
    public native String jaFromJNI();

    static {
        System.loadLibrary("hello-jni");
    }
}
