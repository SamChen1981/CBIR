#include "shape_feature.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <cmath>
#include "com_stormphoenix_cbir_opencv_HuFeature.h"

JNIEXPORT jobject JNICALL Java_com_stormphoenix_cbir_opencv_HuFeature_calculateShapeHuFeature
  (JNIEnv * env, jclass, jstring imgPath) {
   const char *path;
      path = env->GetStringUTFChars(imgPath, NULL);
      HuMatrix *huMatrix = calculateHuMatrix(path);
      jclass featureClass = env->FindClass("com/stormphoenix/cbir/structs/ShapeHuMatrix");
      jmethodID constructor = env->GetMethodID(featureClass, "<init>", "()V");
      jobject result_obj = env->NewObject(featureClass, constructor);

      jfieldID fieldId = env->GetFieldID(featureClass, "m", "[F");

      jfloatArray array = env->NewFloatArray(6);
      jfloat *floatArrayPointer = env->GetFloatArrayElements(array, NULL);
      int i;
      for (i = 0;i < 6;i ++) {
          *(floatArrayPointer + i) = huMatrix->m[i];
      }
      env->SetFloatArrayRegion(array, 0, 6, floatArrayPointer);
      env->SetObjectField(result_obj, fieldId, array);

      env->ReleaseStringUTFChars(imgPath, path);
      return result_obj;
  }