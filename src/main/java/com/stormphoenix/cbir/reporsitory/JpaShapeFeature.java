package com.stormphoenix.cbir.reporsitory;

import com.stormphoenix.cbir.entities.HuFeatureEntity;
import com.stormphoenix.cbir.opencv.HuFeature;
import org.springframework.data.jpa.repository.JpaRepository;

/**
 * Created by Developer on 17-7-6.
 */
public interface JpaShapeFeature extends JpaRepository<HuFeatureEntity, Integer> {
    HuFeatureEntity findById(Integer id);
    HuFeatureEntity findByForeignKey(Integer id);
}
