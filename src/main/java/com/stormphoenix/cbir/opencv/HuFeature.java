package com.stormphoenix.cbir.opencv;

import com.stormphoenix.cbir.entities.HuFeatureEntity;
import com.stormphoenix.cbir.structs.ShapeHuMatrix;

/**
 * Created by Developer on 17-7-6.
 */
public class HuFeature {
    static {
        System.loadLibrary("com_stormphoenix_cbir_opencv");
    }

    public native static ShapeHuMatrix calculateShapeHuFeature(String path);

    public static double calculateHuMatrixDistance(ShapeHuMatrix matrix, HuFeatureEntity entity) {
        double result = (
                Math.pow(matrix.m[0] - entity.getM1(), 2) +
                        Math.pow(matrix.m[1] - entity.getM2(), 2) +
                        Math.pow(matrix.m[2] - entity.getM3(), 2) +
                        Math.pow(matrix.m[3] - entity.getM4(), 2) +
                        Math.pow(matrix.m[4] - entity.getM5(), 2) +
                        Math.pow(matrix.m[5] - entity.getM6(), 2)
        ) / 6;
        return Math.sqrt(result);
    }
}
