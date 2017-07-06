package com.stormphoenix.cbir.entities;

import javax.persistence.*;
import java.util.Collection;

/**
 * Created by Developer on 17-7-6.
 */
@Entity
@Table(name = "Images", schema = "CBIR", catalog = "")
public class ImagesEntity {
    private int id;
    private String path;
    private Collection<HsiFeatureEntity> hsiFeaturesById;
    private Collection<HuFeatureEntity> huFeaturesById;
    private Collection<TextureFeatureEntity> textureFeaturesById;

    @Id
    @Column(name = "id", nullable = false)
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Basic
    @Column(name = "path", nullable = true, length = 100)
    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        ImagesEntity that = (ImagesEntity) o;

        if (id != that.id) return false;
        if (path != null ? !path.equals(that.path) : that.path != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + (path != null ? path.hashCode() : 0);
        return result;
    }

    @OneToMany(mappedBy = "imagesByForeignKey")
    public Collection<HsiFeatureEntity> getHsiFeaturesById() {
        return hsiFeaturesById;
    }

    public void setHsiFeaturesById(Collection<HsiFeatureEntity> hsiFeaturesById) {
        this.hsiFeaturesById = hsiFeaturesById;
    }

    @OneToMany(mappedBy = "imagesByForeignKey")
    public Collection<HuFeatureEntity> getHuFeaturesById() {
        return huFeaturesById;
    }

    public void setHuFeaturesById(Collection<HuFeatureEntity> huFeaturesById) {
        this.huFeaturesById = huFeaturesById;
    }

    @OneToMany(mappedBy = "imagesByForeignKey")
    public Collection<TextureFeatureEntity> getTextureFeaturesById() {
        return textureFeaturesById;
    }

    public void setTextureFeaturesById(Collection<TextureFeatureEntity> textureFeaturesById) {
        this.textureFeaturesById = textureFeaturesById;
    }
}
