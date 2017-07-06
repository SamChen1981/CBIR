package com.stormphoenix.cbir.reporsitory;

import com.stormphoenix.cbir.entities.HsiFeatureEntity;
import org.springframework.data.jpa.repository.JpaRepository;

/**
 * Created by Developer on 17-7-6.
 */
public interface JpaHsiFeature extends JpaRepository<HsiFeatureEntity, Integer> {
    HsiFeatureEntity findById(Integer id);
    HsiFeatureEntity findByForeignKey(Integer id);
}
