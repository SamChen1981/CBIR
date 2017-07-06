package com.stormphoenix.cbir.opencv;

import com.stormphoenix.cbir.entities.HsiFeatureEntity;
import com.stormphoenix.cbir.structs.HsiCenterMatrix;

/**
 * Created by Developer on 17-7-6.
 */
public class HsiFeature {
    static {
        System.loadLibrary("com_stormphoenix_cbir_opencv");
    }

    public native static boolean compareHsiFeature(String imgPath1, String imgPath2);

    public native static HsiCenterMatrix calculateHsiCenterMatrix(String path, int weight);

    public static double calculateHsiDistance(HsiCenterMatrix matrixR,
                                              HsiCenterMatrix matrixG,
                                              HsiCenterMatrix matrixB,
                                              HsiFeatureEntity entity) {
        double temp = Math.pow(matrixR.M1 - entity.getrM1(), 2) + Math.pow(matrixR.M2 - entity.getrM2(), 2) + Math.pow(matrixR.M3 - entity.getrM3(), 2)
                + Math.pow(matrixG.M1 - entity.getgM1(), 2) + Math.pow(matrixG.M2 - entity.getgM2(), 2) + Math.pow(matrixG.M3 - entity.getgM3(), 2)
                + Math.pow(matrixB.M1 - entity.getbM1(), 2) + Math.pow(matrixB.M2 - entity.getbM2(), 2) + Math.pow(matrixB.M3 - entity.getbM3(), 2);
        temp = Math.sqrt(temp);
        return temp;
    }
}
