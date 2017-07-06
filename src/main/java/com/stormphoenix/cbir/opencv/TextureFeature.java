package com.stormphoenix.cbir.opencv;

import com.stormphoenix.cbir.entities.TextureFeatureEntity;
import com.stormphoenix.cbir.structs.Texture;

/**
 * Created by Developer on 17-7-6.
 */
public class TextureFeature {
    static {
        System.loadLibrary("com_stormphoenix_cbir_opencv");
    }

    public native static Texture calculateTextureFeature(String path);

    public static double calculateTextureDistance(Texture texture, TextureFeatureEntity entity) {
        double temp = (Math.pow(texture.eentropy - entity.getEentropy(), 2) + Math.pow(texture.centropy - entity.getCentropy(), 2)
                + Math.pow(texture.eidm - entity.getEidm(), 2) + Math.pow(texture.cidm - entity.getCidm(), 2)
                + Math.pow(texture.econ - entity.getEcon(), 2) + Math.pow(texture.ccon - entity.getCcon(), 2)
                + Math.pow(texture.easm - entity.getEasm(), 2) + Math.pow(texture.casm - entity.getCasm(), 2)) / 2;
        return Math.sqrt(temp);
    }
}
