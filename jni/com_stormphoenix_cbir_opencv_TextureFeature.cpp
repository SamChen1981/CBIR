#include "com_stormphoenix_cbir_opencv_TextureFeature.h"
#include "texture_feature.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <cmath>

JNIEXPORT jobject JNICALL Java_com_stormphoenix_cbir_opencv_TextureFeature_calculateTextureFeature
  (JNIEnv * env, jclass, jstring imgPath) {
  const char *path;
      path = env->GetStringUTFChars(imgPath, NULL);
      TextureFeature * feature = calculateTextureFeature(path);
      jclass featureClass = env->FindClass("com/stormphoenix/cbir/structs/Texture");
      jmethodID constructor = env->GetMethodID(featureClass, "<init>", "()V");
      jobject result_obj = env->NewObject(featureClass, constructor);

      jfieldID fieldId1 = env->GetFieldID(featureClass, "eentropy", "D");
      jfieldID fieldId2 = env->GetFieldID(featureClass, "eidm", "D");
      jfieldID fieldId3 = env->GetFieldID(featureClass, "econ", "D");
      jfieldID fieldId4 = env->GetFieldID(featureClass, "easm", "D");
      jfieldID fieldId5 = env->GetFieldID(featureClass, "centropy", "D");
      jfieldID fieldId6 = env->GetFieldID(featureClass, "cidm", "D");
      jfieldID fieldId7 = env->GetFieldID(featureClass, "ccon", "D");
      jfieldID fieldId8 = env->GetFieldID(featureClass, "casm", "D");

      env->SetDoubleField(result_obj, fieldId1, (jdouble) feature -> eentropy);
      env->SetDoubleField(result_obj, fieldId2, (jdouble) feature -> eidm);
      env->SetDoubleField(result_obj, fieldId3, (jdouble) feature -> econ);
      env->SetDoubleField(result_obj, fieldId4, (jdouble) feature -> easm);
      env->SetDoubleField(result_obj, fieldId5, (jdouble) feature -> centropy);
      env->SetDoubleField(result_obj, fieldId6, (jdouble) feature -> cidm);
      env->SetDoubleField(result_obj, fieldId7, (jdouble) feature -> ccon);
      env->SetDoubleField(result_obj, fieldId8, (jdouble) feature -> casm);

      env->ReleaseStringUTFChars(imgPath, path);
      return result_obj;
  }