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

#include "Mesh.h"

#include "android/asset_manager_jni.h"

namespace mgn {
extern "C" {
JNIEXPORT jlong JNICALL
Java_com_eje_1c_meganekko_Mesh_initNativeInstance(JNIEnv* env, jobject obj);
JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getVertices(JNIEnv * env,
        jobject obj, jlong jmesh);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setVertices(JNIEnv * env,
        jobject obj, jlong jmesh, jfloatArray vertices);
JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getNormals(JNIEnv * env,
        jobject obj, jlong jmesh);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setNormals(JNIEnv * env,
        jobject obj, jlong jmesh, jfloatArray normals);
JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getTexCoords(JNIEnv * env,
        jobject obj, jlong jmesh);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setTexCoords(JNIEnv * env,
        jobject obj, jlong jmesh, jfloatArray tex_coords);
JNIEXPORT jcharArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getTriangles(JNIEnv * env,
        jobject obj, jlong jmesh);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setTriangles(JNIEnv * env,
        jobject obj, jlong jmesh, jcharArray triangles);
JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getFloatVector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setFloatVector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key, jfloatArray float_vector);
JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getVec2Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setVec2Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key, jfloatArray vec2_vector);
JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getVec3Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setVec3Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key, jfloatArray vec3_vector);
JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getVec4Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key);

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setVec4Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key, jfloatArray vec4_vector);
JNIEXPORT jlong JNICALL
Java_com_eje_1c_meganekko_Mesh_getBoundingBox(JNIEnv * env,
        jobject obj, jlong jmesh);
}
;

JNIEXPORT jlong JNICALL
Java_com_eje_1c_meganekko_Mesh_initNativeInstance(JNIEnv* env, jobject obj) {
    return reinterpret_cast<jlong>(new Mesh());
}

JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getVertices(JNIEnv * env,
        jobject obj, jlong jmesh) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    std::vector<OVR::Vector3f>& vertices = mesh->vertices();
    jfloatArray jvertices = env->NewFloatArray(vertices.size() * 3);
    env->SetFloatArrayRegion(jvertices, 0, vertices.size() * 3,
            reinterpret_cast<jfloat*>(vertices.data()));
    return jvertices;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setVertices(JNIEnv * env,
        jobject obj, jlong jmesh, jfloatArray vertices) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    jfloat* jvertices_pointer = env->GetFloatArrayElements(vertices, 0);
    OVR::Vector3f* vertices_pointer =
            reinterpret_cast<OVR::Vector3f*>(jvertices_pointer);
    int vertices_length = static_cast<int>(env->GetArrayLength(vertices))
            / (sizeof(OVR::Vector3f) / sizeof(jfloat));
    std::vector<OVR::Vector3f> native_vertices;
    for (int i = 0; i < vertices_length; ++i) {
        native_vertices.push_back(vertices_pointer[i]);
    }
    mesh->set_vertices(native_vertices);
    env->ReleaseFloatArrayElements(vertices, jvertices_pointer, 0);
}

JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getNormals(JNIEnv * env,
        jobject obj, jlong jmesh) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    std::vector<OVR::Vector3f>& normals = mesh->normals();
    jfloatArray jnormals = env->NewFloatArray(normals.size() * 3);
    env->SetFloatArrayRegion(jnormals, 0, normals.size() * 3,
            reinterpret_cast<jfloat*>(normals.data()));
    return jnormals;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setNormals(JNIEnv * env,
        jobject obj, jlong jmesh, jfloatArray normals) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    jfloat* jnormals_pointer = env->GetFloatArrayElements(normals, 0);
    OVR::Vector3f* normals_pointer = reinterpret_cast<OVR::Vector3f*>(jnormals_pointer);
    int normals_length = static_cast<int>(env->GetArrayLength(normals))
            / (sizeof(OVR::Vector3f) / sizeof(jfloat));
    std::vector<OVR::Vector3f> native_normals;
    for (int i = 0; i < normals_length; ++i) {
        native_normals.push_back(normals_pointer[i]);
    }
    mesh->set_normals(native_normals);
    env->ReleaseFloatArrayElements(normals, jnormals_pointer, 0);
}

JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getTexCoords(JNIEnv * env,
        jobject obj, jlong jmesh) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    std::vector<OVR::Vector2f>& uvs = mesh->tex_coords();
    jfloatArray juvs = env->NewFloatArray(uvs.size() * 2);
    env->SetFloatArrayRegion(juvs, 0, uvs.size() * 2,
            reinterpret_cast<jfloat*>(uvs.data()));
    return juvs;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setTexCoords(JNIEnv * env,
        jobject obj, jlong jmesh, jfloatArray tex_coords) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    jfloat* jtex_coords_pointer = env->GetFloatArrayElements(tex_coords, 0);
    OVR::Vector2f* tex_coords_pointer =
            reinterpret_cast<OVR::Vector2f*>(jtex_coords_pointer);
    int tex_coords_length = static_cast<int>(env->GetArrayLength(tex_coords))
            / (sizeof(OVR::Vector2f) / sizeof(jfloat));
    std::vector<OVR::Vector2f> native_tex_coords;
    for (int i = 0; i < tex_coords_length; ++i) {
        native_tex_coords.push_back(tex_coords_pointer[i]);
    }
    mesh->set_tex_coords(native_tex_coords);
    env->ReleaseFloatArrayElements(tex_coords, jtex_coords_pointer, 0);
}

JNIEXPORT jcharArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getTriangles(JNIEnv * env,
        jobject obj, jlong jmesh) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    std::vector<unsigned short>& triangles = mesh->triangles();
    jcharArray jtriangles = env->NewCharArray(triangles.size());
    env->SetCharArrayRegion(jtriangles, 0, triangles.size(), triangles.data());
    return jtriangles;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setTriangles(JNIEnv * env,
        jobject obj, jlong jmesh, jcharArray triangles) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    jchar* jtriangles_pointer = env->GetCharArrayElements(triangles, 0);
    unsigned short* triangles_pointer =
            static_cast<unsigned short*>(jtriangles_pointer);
    int triangles_length = env->GetArrayLength(triangles);
    std::vector<unsigned short> native_triangles;
    for (int i = 0; i < triangles_length; ++i) {
        native_triangles.push_back(triangles_pointer[i]);
    }
    mesh->set_triangles(native_triangles);
    env->ReleaseCharArrayElements(triangles, jtriangles_pointer, 0);
}

JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getFloatVector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    const char* char_key = env->GetStringUTFChars(key, 0);
    std::string native_key = std::string(char_key);
    std::vector<float>& float_vector = mesh->getFloatVector(native_key);
    env->ReleaseStringUTFChars(key, char_key);
    jfloatArray jfloat_vector = env->NewFloatArray(float_vector.size());
    env->SetFloatArrayRegion(jfloat_vector, 0, float_vector.size(),
            reinterpret_cast<jfloat*>(float_vector.data()));
    return jfloat_vector;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setFloatVector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key, jfloatArray float_vector) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    jfloat* jfloat_vector_pointer = env->GetFloatArrayElements(float_vector, 0);
    float* float_vector_pointer =
            reinterpret_cast<float*>(jfloat_vector_pointer);
    int float_vector_length =
            static_cast<int>(env->GetArrayLength(float_vector));
    std::vector<float> native_float_vector;
    for (int i = 0; i < float_vector_length; ++i) {
        native_float_vector.push_back(float_vector_pointer[i]);
    }
    const char* char_key = env->GetStringUTFChars(key, 0);
    std::string native_key = std::string(char_key);
    mesh->setFloatVector(native_key, native_float_vector);
    env->ReleaseStringUTFChars(key, char_key);
    env->ReleaseFloatArrayElements(float_vector, jfloat_vector_pointer, 0);
}

JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getVec2Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    const char* char_key = env->GetStringUTFChars(key, 0);
    std::string native_key = std::string(char_key);
    std::vector<OVR::Vector2f>& vec2_vector = mesh->getVec2Vector(native_key);
    env->ReleaseStringUTFChars(key, char_key);
    jfloatArray jvec2_vector = env->NewFloatArray(vec2_vector.size() * 2);
    env->SetFloatArrayRegion(jvec2_vector, 0, vec2_vector.size() * 2,
            reinterpret_cast<jfloat*>(vec2_vector.data()));
    return jvec2_vector;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setVec2Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key, jfloatArray vec2_vector) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    jfloat* jvec2_vector_pointer = env->GetFloatArrayElements(vec2_vector, 0);
    OVR::Vector2f* vec2_vector_pointer =
            reinterpret_cast<OVR::Vector2f*>(jvec2_vector_pointer);
    int vec2_vector_length = static_cast<int>(env->GetArrayLength(vec2_vector))
            / (sizeof(OVR::Vector2f) / sizeof(jfloat));
    std::vector<OVR::Vector2f> native_vec2_vector;
    for (int i = 0; i < vec2_vector_length; ++i) {
        native_vec2_vector.push_back(vec2_vector_pointer[i]);
    }
    const char* char_key = env->GetStringUTFChars(key, 0);
    std::string native_key = std::string(char_key);
    mesh->setVec2Vector(native_key, native_vec2_vector);
    env->ReleaseStringUTFChars(key, char_key);
    env->ReleaseFloatArrayElements(vec2_vector, jvec2_vector_pointer, 0);
}

JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getVec3Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    const char* char_key = env->GetStringUTFChars(key, 0);
    std::string native_key = std::string(char_key);
    std::vector<OVR::Vector3f>& vec3_vector = mesh->getVec3Vector(native_key);
    env->ReleaseStringUTFChars(key, char_key);
    jfloatArray jvec3_vector = env->NewFloatArray(vec3_vector.size() * 3);
    env->SetFloatArrayRegion(jvec3_vector, 0, vec3_vector.size() * 3,
            reinterpret_cast<jfloat*>(vec3_vector.data()));
    return jvec3_vector;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setVec3Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key, jfloatArray vec3_vector) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    jfloat* jvec3_vector_pointer = env->GetFloatArrayElements(vec3_vector, 0);
    OVR::Vector3f* vec3_vector_pointer =
            reinterpret_cast<OVR::Vector3f*>(jvec3_vector_pointer);
    int vec3_vector_length = static_cast<int>(env->GetArrayLength(vec3_vector))
            / (sizeof(OVR::Vector3f) / sizeof(jfloat));
    std::vector<OVR::Vector3f> native_vec3_vector;
    for (int i = 0; i < vec3_vector_length; ++i) {
        native_vec3_vector.push_back(vec3_vector_pointer[i]);
    }
    const char* char_key = env->GetStringUTFChars(key, 0);
    std::string native_key = std::string(char_key);
    mesh->setVec3Vector(native_key, native_vec3_vector);
    env->ReleaseStringUTFChars(key, char_key);
    env->ReleaseFloatArrayElements(vec3_vector, jvec3_vector_pointer, 0);
}

JNIEXPORT jfloatArray JNICALL
Java_com_eje_1c_meganekko_Mesh_getVec4Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    const char* char_key = env->GetStringUTFChars(key, 0);
    std::string native_key = std::string(char_key);
    std::vector<OVR::Vector4f>& vec4_vector = mesh->getVec4Vector(native_key);
    env->ReleaseStringUTFChars(key, char_key);
    jfloatArray jvec4_vector = env->NewFloatArray(vec4_vector.size() * 4);
    env->SetFloatArrayRegion(jvec4_vector, 0, vec4_vector.size() * 4,
            reinterpret_cast<jfloat*>(vec4_vector.data()));
    return jvec4_vector;
}

JNIEXPORT void JNICALL
Java_com_eje_1c_meganekko_Mesh_setVec4Vector(JNIEnv * env,
        jobject obj, jlong jmesh, jstring key, jfloatArray vec4_vector) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    jfloat* jvec4_vector_pointer = env->GetFloatArrayElements(vec4_vector, 0);
    OVR::Vector4f* vec4_vector_pointer =
            reinterpret_cast<OVR::Vector4f*>(jvec4_vector_pointer);
    int vec4_vector_length = static_cast<int>(env->GetArrayLength(vec4_vector))
            / (sizeof(OVR::Vector4f) / sizeof(jfloat));
    std::vector<OVR::Vector4f> native_vec4_vector;
    for (int i = 0; i < vec4_vector_length; ++i) {
        native_vec4_vector.push_back(vec4_vector_pointer[i]);
    }
    const char* char_key = env->GetStringUTFChars(key, 0);
    std::string native_key = std::string(char_key);
    mesh->setVec4Vector(native_key, native_vec4_vector);
    env->ReleaseStringUTFChars(key, char_key);
    env->ReleaseFloatArrayElements(vec4_vector, jvec4_vector_pointer, 0);
}

JNIEXPORT jlong JNICALL
Java_com_eje_1c_meganekko_Mesh_getBoundingBox(JNIEnv * env,
        jobject obj, jlong jmesh) {
    Mesh* mesh = reinterpret_cast<Mesh*>(jmesh);
    return reinterpret_cast<jlong>(mesh->getBoundingBox());
}

}