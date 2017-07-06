package com.stormphoenix.cbir.reporsitory;

import com.stormphoenix.cbir.entities.ImagesEntity;
import org.springframework.data.jpa.repository.JpaRepository;

/**
 * Created by Developer on 17-7-6.
 */
public interface JpaImages extends JpaRepository<ImagesEntity, Integer> {
    ImagesEntity findById(Integer id);
}
