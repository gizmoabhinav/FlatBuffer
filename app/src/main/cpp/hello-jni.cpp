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
 *
 */
#include <string>
#include <jni.h>
#include "unistd.h"
#include "repos_schema_generated.h"
#include <cstdio>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   hello-jni/app/src/main/java/com/example/hellojni/HelloJni.java
 */

extern "C"
{

JNIEXPORT jstring JNICALL
Java_com_example_hellojni_HelloJni_stringFromJNI(JNIEnv *env, jobject thiz) {
    if( access( "/sdcard/repos_json.bin", F_OK ) != -1 ) {
        FILE* file = fopen("/sdcard/repos_json.bin", "rb");
        if(file == NULL) {
            return env->NewStringUTF(strerror(errno));
        }
        int length = ftell(file);
        fseek(file, 0L, SEEK_SET);
        char *data = new char[length];
        fread(data, sizeof(char), length, file);
        fclose(file);
        const Repos::ReposList* repoList = Repos::GetReposList(data);
        flatbuffers::FlatBufferBuilder fbb(1024);
        auto struct1 = fbb.CreateStruct(repoList->repos());
        auto fb = Repos::CreateReposList(fbb,struct1.o);
        fbb.Finish(fb);
        uint8_t *buf = fbb.GetBufferPointer();
        int size = fbb.GetSize();
        return env->NewStringUTF("Hello from JNI found file! ");
    } else {
        // file doesn't exist
    }
    return env->NewStringUTF("Hello from JNI ! ");
}
}
