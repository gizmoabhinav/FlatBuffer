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

static const Repos::ReposList *repoList;
static std::string jsonData;
static int size;

JNIEXPORT void JNICALL
Java_com_example_hellojni_HelloJni_load(JNIEnv *env, jobject thiz) {
    if (access("/sdcard/repos_json.bin", F_OK) != -1) {
        FILE *file = fopen("/sdcard/repos_json.bin", "rb");
        if (file == NULL) {
            return;
        }
        fseek(file, 0L, SEEK_END);
        int length = ftell(file);
        fseek(file, 0L, SEEK_SET);
        char *data = new char[length];
        fread(data, sizeof(char), length, file);
        fclose(file);
        size = length;
        repoList = Repos::GetReposList(data);
    } else {
        size = 0;
    }
    if (access("/sdcard/repos_json.json", F_OK) != -1) {
        FILE *file = fopen("/sdcard/repos_json.json", "rb");
        if (file == NULL) {
            return;
        }
        fseek(file, 0L, SEEK_END);
        int length = ftell(file);
        fseek(file, 0L, SEEK_SET);
        char *data = new char[length];
        fread(data, sizeof(char), length, file);
        fclose(file);
        size = length;
        jsonData = data;
    } else {
        size = 0;
    }
}


JNIEXPORT jbyteArray JNICALL
Java_com_example_hellojni_HelloJni_fbFromJNI(JNIEnv *env, jobject thiz) {
    if (size > 0) {
        auto fb = flatbuffers::GetBufferStartFromRootPointer(repoList);
        jbyteArray ret = env->NewByteArray(size);
        env->SetByteArrayRegion(ret, 0, size, (const jbyte *) fb);
        return ret;
    } else {
        return NULL;
    }
}


JNIEXPORT jstring JNICALL
Java_com_example_hellojni_HelloJni_jaFromJNI(JNIEnv *env, jobject thiz) {
    if (size > 0) {
        return env->NewStringUTF(jsonData.c_str());
    } else {
        return NULL;
    }
}
}
