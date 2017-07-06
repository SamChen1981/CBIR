#include "com_stormphoenix_cbir_opencv_HsiFeature.h"
#include "hsi_feature.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <cmath>

using namespace std;
using namespace cv;

/*
 * Class:     com_stormphoenix_cbir_opencv_HsiFeature
 * Method:    compareHsiFeature
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_stormphoenix_cbir_opencv_HsiFeature_compareHsiFeature
  (JNIEnv * env, jclass, jstring imgPath1, jstring imgPath2) {
        const char *path1;
        const char *path2;

        path1 = env->GetStringUTFChars(imgPath1, NULL);
        path2 = env->GetStringUTFChars(imgPath2, NULL);

        HSI_CenterM *hsi1R = calculateHSICenterMByPath(path1, 0);
        HSI_CenterM *hsi1G = calculateHSICenterMByPath(path1, 1);
        HSI_CenterM *hsi1B = calculateHSICenterMByPath(path1, 2);

        HSI_CenterM *hsi2R = calculateHSICenterMByPath(path2, 0);
        HSI_CenterM *hsi2G = calculateHSICenterMByPath(path2, 1);
        HSI_CenterM *hsi2B = calculateHSICenterMByPath(path2, 2);

        double result = calcHsiDistance(hsi1R, hsi1G, hsi1B, hsi2R, hsi2G, hsi2B);

        env->ReleaseStringUTFChars(imgPath1, path1);
        env->ReleaseStringUTFChars(imgPath2, path2);

        delete hsi1R;
        delete hsi1G;
        delete hsi1B;
        delete hsi2R;
        delete hsi2G;
        delete hsi2B;

        cout << "native method result : " << result << endl;

        if (result >= 0.80) {
            return (jboolean) true;
        } else {
            return (jboolean) false;
        }
  }

JNIEXPORT jobject JNICALL Java_com_stormphoenix_cbir_opencv_HsiFeature_calculateHsiCenterMatrix
  (JNIEnv * env, jclass, jstring imgPath, jint weight) {
  const char *path;
  int w = (int) weight;
  path = env->GetStringUTFChars(imgPath, NULL);
  HSI_CenterM *hsi_m = calculateHSICenterMByPath(path, w);
  jclass hsi_class = env->FindClass("com/stormphoenix/cbir/structs/HsiCenterMatrix");
  jmethodID constructorMID = env->GetMethodID(hsi_class, "<init>", "()V");
  jobject result_obj = env->NewObject(hsi_class, constructorMID);

  jfieldID weightID = env->GetFieldID(hsi_class, "weight", "I");
  jfieldID m1ID = env->GetFieldID(hsi_class, "M1", "D");
  jfieldID m2ID = env->GetFieldID(hsi_class, "M2", "D");
  jfieldID m3ID = env->GetFieldID(hsi_class, "M3", "D");

  env->SetIntField(result_obj, weightID, (jint) weight);
  env->SetDoubleField(result_obj, m1ID, (jdouble) hsi_m -> M1);
  env->SetDoubleField(result_obj, m2ID, (jdouble) hsi_m -> M2);
  env->SetDoubleField(result_obj, m3ID, (jdouble) hsi_m -> M3);

  env->ReleaseStringUTFChars(imgPath, path);

  return result_obj;
  }