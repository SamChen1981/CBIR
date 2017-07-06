package com.stormphoenix.cbir.structs;

/**
 * Created by Developer on 17-7-6.
 */
public class DistIdEntry implements Comparable<DistIdEntry> {
    public double distance;
    public int id;

    public DistIdEntry(double distance, int id) {
        this.distance = distance;
        this.id = id;
    }

    @Override
    public int compareTo(DistIdEntry o) {
        if (this.distance < o.distance) {
            return -1;
        } else if (this.distance == o.distance) {
            return 0;
        }
        return 1;
    }
}
