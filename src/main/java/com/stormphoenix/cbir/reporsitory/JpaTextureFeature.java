package com.stormphoenix.cbir.reporsitory;

import com.stormphoenix.cbir.entities.TextureFeatureEntity;
import org.springframework.data.jpa.repository.JpaRepository;

/**
 * Created by Developer on 17-7-6.
 */
public interface JpaTextureFeature extends JpaRepository<TextureFeatureEntity, Integer>{
    TextureFeatureEntity findByForeignKey(Integer id);
}
