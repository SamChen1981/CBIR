package com.stormphoenix.cbir;

import com.stormphoenix.cbir.structs.DistIdEntry;

import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

/**
 * Created by Developer on 17-7-6.
 */
public class Utils {
    public static List<List<Integer>> getShowingImageLists(PriorityQueue<DistIdEntry> queue) {
        List<List<Integer>> imgRows = new ArrayList<>();
        int resultImgCount = 0;
        while (resultImgCount < 12) {
            if (resultImgCount % 4 == 0) {
                imgRows.add(new ArrayList<>());
                imgRows.get(imgRows.size() - 1).add(queue.poll().id);
            } else {
                imgRows.get(imgRows.size() - 1).add(queue.poll().id);
            }
            resultImgCount++;
        }
        return imgRows;
    }
}
