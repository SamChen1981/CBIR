package com.stormphoenix.cbir.entities;

import javax.persistence.*;

/**
 * Created by Developer on 17-7-6.
 */
@Entity
@Table(name = "TextureFeature", schema = "CBIR", catalog = "")
public class TextureFeatureEntity {
    private int id;
    private double easm;
    private double casm;
    private double eidm;
    private Double cidm;
    private Double eentropy;
    private Double centropy;
    private Double econ;
    private Double ccon;
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
    @Column(name = "easm", nullable = false, precision = 0)
    public double getEasm() {
        return easm;
    }

    public void setEasm(double easm) {
        this.easm = easm;
    }

    @Basic
    @Column(name = "casm", nullable = false, precision = 0)
    public double getCasm() {
        return casm;
    }

    public void setCasm(double casm) {
        this.casm = casm;
    }

    @Basic
    @Column(name = "eidm", nullable = false, precision = 0)
    public double getEidm() {
        return eidm;
    }

    public void setEidm(double eidm) {
        this.eidm = eidm;
    }

    @Basic
    @Column(name = "cidm", nullable = true, precision = 0)
    public Double getCidm() {
        return cidm;
    }

    public void setCidm(Double cidm) {
        this.cidm = cidm;
    }

    @Basic
    @Column(name = "eentropy", nullable = true, precision = 0)
    public Double getEentropy() {
        return eentropy;
    }

    public void setEentropy(Double eentropy) {
        this.eentropy = eentropy;
    }

    @Basic
    @Column(name = "centropy", nullable = true, precision = 0)
    public Double getCentropy() {
        return centropy;
    }

    public void setCentropy(Double centropy) {
        this.centropy = centropy;
    }

    @Basic
    @Column(name = "econ", nullable = true, precision = 0)
    public Double getEcon() {
        return econ;
    }

    public void setEcon(Double econ) {
        this.econ = econ;
    }

    @Basic
    @Column(name = "ccon", nullable = true, precision = 0)
    public Double getCcon() {
        return ccon;
    }

    public void setCcon(Double ccon) {
        this.ccon = ccon;
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

        TextureFeatureEntity that = (TextureFeatureEntity) o;

        if (id != that.id) return false;
        if (Double.compare(that.easm, easm) != 0) return false;
        if (Double.compare(that.casm, casm) != 0) return false;
        if (Double.compare(that.eidm, eidm) != 0) return false;
        if (foreignKey != that.foreignKey) return false;
        if (cidm != null ? !cidm.equals(that.cidm) : that.cidm != null) return false;
        if (eentropy != null ? !eentropy.equals(that.eentropy) : that.eentropy != null) return false;
        if (centropy != null ? !centropy.equals(that.centropy) : that.centropy != null) return false;
        if (econ != null ? !econ.equals(that.econ) : that.econ != null) return false;
        if (ccon != null ? !ccon.equals(that.ccon) : that.ccon != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        result = id;
        temp = Double.doubleToLongBits(easm);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(casm);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(eidm);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        result = 31 * result + (cidm != null ? cidm.hashCode() : 0);
        result = 31 * result + (eentropy != null ? eentropy.hashCode() : 0);
        result = 31 * result + (centropy != null ? centropy.hashCode() : 0);
        result = 31 * result + (econ != null ? econ.hashCode() : 0);
        result = 31 * result + (ccon != null ? ccon.hashCode() : 0);
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
