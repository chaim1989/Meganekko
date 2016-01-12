/* Copyright 2015 Samsung Electronics Co., LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/***************************************************************************
 * JNI
 ***************************************************************************/

#include <jni.h>

#include "eye_pointee_holder.h"
#include "util/gvr_log.h"

namespace mgn {
extern "C" {
JNIEXPORT jlong JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_ctor(JNIEnv * env,
        jobject obj);

JNIEXPORT jboolean JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_getEnable(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_setEnable(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder, jboolean enable);
JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_getHit(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_addPointee(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder, jlong jeye_pointee);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_removePointee(
        JNIEnv * env, jobject obj, jlong jeye_pointee_holder,
        jlong jeye_pointee);
JNIEXPORT jboolean JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_isPointed(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder);
}
;

JNIEXPORT jlong JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_ctor(JNIEnv * env,
        jobject obj) {
    return reinterpret_cast<jlong>(new EyePointeeHolder());
}

JNIEXPORT jboolean JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_getEnable(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder) {
    EyePointeeHolder* eye_pointee_holder =
            reinterpret_cast<EyePointeeHolder*>(jeye_pointee_holder);
    return static_cast<jboolean>(eye_pointee_holder->enable());
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_setEnable(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder, jboolean enable) {
    EyePointeeHolder* eye_pointee_holder =
            reinterpret_cast<EyePointeeHolder*>(jeye_pointee_holder);
    eye_pointee_holder->set_enable(static_cast<jboolean>(enable));
}

JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_getHit(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder) {
    EyePointeeHolder* eye_pointee_holder =
            reinterpret_cast<EyePointeeHolder*>(jeye_pointee_holder);
    OVR::Vector3f hit = eye_pointee_holder->hit();
    jsize size = sizeof(hit) / sizeof(jfloat);
    if (size != 3) {
        LOGE("sizeof(hit) / sizeof(jfloat) != 3");
        throw "sizeof(hit) / sizeof(jfloat) != 3";
    }
    jfloatArray jhit = env->NewFloatArray(size);
    env->SetFloatArrayRegion(jhit, 0, size, reinterpret_cast<jfloat*>(&hit));
    return jhit;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_addPointee(JNIEnv * env,
        jobject obj, jlong jeye_pointee_holder, jlong jeye_pointee) {
    EyePointeeHolder* eye_pointee_holder =
            reinterpret_cast<EyePointeeHolder*>(jeye_pointee_holder);
    EyePointee* eye_pointee = reinterpret_cast<EyePointee*>(jeye_pointee);
    eye_pointee_holder->addPointee(eye_pointee);
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_EyePointeeHolder_removePointee(
        JNIEnv * env, jobject obj, jlong jeye_pointee_holder,
        jlong jeye_pointee) {
    EyePointeeHolder* eye_pointee_holder =
            reinterpret_cast<EyePointeeHolder*>(jeye_pointee_holder);
    EyePointee* eye_pointee = reinterpret_cast<EyePointee*>(jeye_pointee);
    eye_pointee_holder->removePointee(eye_pointee);
}

}
