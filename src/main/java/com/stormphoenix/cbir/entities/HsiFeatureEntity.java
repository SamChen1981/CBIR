package com.stormphoenix.cbir.entities;

import javax.persistence.*;

/**
 * Created by Developer on 17-7-6.
 */
@Entity
@Table(name = "HsiFeature", schema = "CBIR", catalog = "")
public class HsiFeatureEntity {
    private int id;
    private double rM1;
    private double rM2;
    private double rM3;
    private double gM1;
    private double gM2;
    private double gM3;
    private double bM1;
    private double bM2;
    private double bM3;
    private int foreignKey;
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
    @Column(name = "R_m1", nullable = false, precision = 0)
    public double getrM1() {
        return rM1;
    }

    public void setrM1(double rM1) {
        this.rM1 = rM1;
    }

    @Basic
    @Column(name = "R_m2", nullable = false, precision = 0)
    public double getrM2() {
        return rM2;
    }

    public void setrM2(double rM2) {
        this.rM2 = rM2;
    }

    @Basic
    @Column(name = "R_m3", nullable = false, precision = 0)
    public double getrM3() {
        return rM3;
    }

    public void setrM3(double rM3) {
        this.rM3 = rM3;
    }

    @Basic
    @Column(name = "G_m1", nullable = false, precision = 0)
    public double getgM1() {
        return gM1;
    }

    public void setgM1(double gM1) {
        this.gM1 = gM1;
    }

    @Basic
    @Column(name = "G_m2", nullable = false, precision = 0)
    public double getgM2() {
        return gM2;
    }

    public void setgM2(double gM2) {
        this.gM2 = gM2;
    }

    @Basic
    @Column(name = "G_m3", nullable = false, precision = 0)
    public double getgM3() {
        return gM3;
    }

    public void setgM3(double gM3) {
        this.gM3 = gM3;
    }

    @Basic
    @Column(name = "B_m1", nullable = false, precision = 0)
    public double getbM1() {
        return bM1;
    }

    public void setbM1(double bM1) {
        this.bM1 = bM1;
    }

    @Basic
    @Column(name = "B_m2", nullable = false, precision = 0)
    public double getbM2() {
        return bM2;
    }

    public void setbM2(double bM2) {
        this.bM2 = bM2;
    }

    @Basic
    @Column(name = "B_m3", nullable = false, precision = 0)
    public double getbM3() {
        return bM3;
    }

    public void setbM3(double bM3) {
        this.bM3 = bM3;
    }

    @Basic
    @Column(name = "foreign_key", nullable = false, insertable = false, updatable = false)
    public int getForeignKey() {
        return foreignKey;
    }

    public void setForeignKey(int foreignKey) {
        this.foreignKey = foreignKey;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        HsiFeatureEntity that = (HsiFeatureEntity) o;

        if (id != that.id) return false;
        if (Double.compare(that.rM1, rM1) != 0) return false;
        if (Double.compare(that.rM2, rM2) != 0) return false;
        if (Double.compare(that.rM3, rM3) != 0) return false;
        if (Double.compare(that.gM1, gM1) != 0) return false;
        if (Double.compare(that.gM2, gM2) != 0) return false;
        if (Double.compare(that.gM3, gM3) != 0) return false;
        if (Double.compare(that.bM1, bM1) != 0) return false;
        if (Double.compare(that.bM2, bM2) != 0) return false;
        if (Double.compare(that.bM3, bM3) != 0) return false;
        if (foreignKey != that.foreignKey) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        result = id;
        temp = Double.doubleToLongBits(rM1);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(rM2);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(rM3);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(gM1);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(gM2);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(gM3);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(bM1);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(bM2);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(bM3);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        result = 31 * result + foreignKey;
        return result;
    }

    @ManyToOne
    @JoinColumn(name = "foreign_key", referencedColumnName = "id", nullable = false)
    public ImagesEntity getImagesByForeignKey() {
        return imagesByForeignKey;
    }

    public void setImagesByForeignKey(ImagesEntity imagesByForeignKey) {
        this.imagesByForeignKey = imagesByForeignKey;
    }
}
