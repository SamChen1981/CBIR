package com.stormphoenix.cbir.entities;

import javax.persistence.*;

/**
 * Created by Developer on 17-7-6.
 */
@Entity
@Table(name = "HuFeature", schema = "CBIR", catalog = "")
public class HuFeatureEntity {
    private int id;
    private double m1;
    private double m2;
    private double m3;
    private double m4;
    private double m5;
    private double m6;
    private Integer foreignKey;
    private ImagesEntity imagesByForeignKey;

    @Id
    @Column(name = "id", nullable = false)
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Basic
    @Column(name = "m1", nullable = false, precision = 0)
    public double getM1() {
        return m1;
    }

    public void setM1(double m1) {
        this.m1 = m1;
    }

    @Basic
    @Column(name = "m2", nullable = false, precision = 0)
    public double getM2() {
        return m2;
    }

    public void setM2(double m2) {
        this.m2 = m2;
    }

    @Basic
    @Column(name = "m3", nullable = false, precision = 0)
    public double getM3() {
        return m3;
    }

    public void setM3(double m3) {
        this.m3 = m3;
    }

    @Basic
    @Column(name = "m4", nullable = false, precision = 0)
    public double getM4() {
        return m4;
    }

    public void setM4(double m4) {
        this.m4 = m4;
    }

    @Basic
    @Column(name = "m5", nullable = false, precision = 0)
    public double getM5() {
        return m5;
    }

    public void setM5(double m5) {
        this.m5 = m5;
    }

    @Basic
    @Column(name = "m6", nullable = false, precision = 0)
    public double getM6() {
        return m6;
    }

    public void setM6(double m6) {
        this.m6 = m6;
    }

    @Basic
    @Column(name = "foreign_key", nullable = true, insertable = false, updatable = false)
    public Integer getForeignKey() {
        return foreignKey;
    }

    public void setForeignKey(Integer foreignKey) {
        this.foreignKey = foreignKey;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        HuFeatureEntity that = (HuFeatureEntity) o;

        if (id != that.id) return false;
        if (Double.compare(that.m1, m1) != 0) return false;
        if (Double.compare(that.m2, m2) != 0) return false;
        if (Double.compare(that.m3, m3) != 0) return false;
        if (Double.compare(that.m4, m4) != 0) return false;
        if (Double.compare(that.m5, m5) != 0) return false;
        if (Double.compare(that.m6, m6) != 0) return false;
        if (foreignKey != null ? !foreignKey.equals(that.foreignKey) : that.foreignKey != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        result = id;
        temp = Double.doubleToLongBits(m1);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(m2);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(m3);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(m4);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(m5);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(m6);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        result = 31 * result + (foreignKey != null ? foreignKey.hashCode() : 0);
        return result;
    }

    @ManyToOne
    @JoinColumn(name = "foreign_key", referencedColumnName = "id")
    public ImagesEntity getImagesByForeignKey() {
        return imagesByForeignKey;
    }

    public void setImagesByForeignKey(ImagesEntity imagesByForeignKey) {
        this.imagesByForeignKey = imagesByForeignKey;
    }
}
