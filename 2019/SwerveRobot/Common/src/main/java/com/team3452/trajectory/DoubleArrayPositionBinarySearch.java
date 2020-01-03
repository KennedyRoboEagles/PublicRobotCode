package com.team3452.trajectory;

public class DoubleArrayPositionBinarySearch {

    // Returns element closest to target in arr[]
    public static int findClosest(double arr[], double target) {
        int n = arr.length;

        // Corner cases
        if (target <= arr[0])
            return 0;
        if (target >= arr[n - 1])
            return n - 1;

        // Doing binary search
        int i = 0, j = n, mid = 0;
        while (i < j) {
            mid = (i + j) / 2;

            if (arr[mid] == target)
                return mid;

            /*
             * If target is less than array element, then search in left
             */
            if (target < arr[mid]) {

                // If target is greater than previous
                // to mid, return closest of two
                if (mid > 0 && target > arr[mid - 1])
                    return getClosest(mid - 1, arr[mid - 1], mid, arr[mid], target).pos;

                /* Repeat for left half */
                j = mid;
            }

            // If target is greater than mid
            else {
                if (mid < n - 1 && target < arr[mid + 1])
                    return getClosest(mid, arr[mid], mid + 1, arr[mid + 1], target).pos;
                i = mid + 1; // update i
            }
        }

        // Only single element left after search
        return mid;
    }

    // Method to compare which one is the more close
    // We find the closest by taking the difference
    // between the target and both values. It assumes
    // that val2 is greater than val1 and target lies
    // between these two.
    public static Value getClosest(int pos1, double val1, int pos2, double val2, double target) {
        if (target - val1 >= val2 - target)
            return new Value(pos2, val2);
        else
            return new Value(pos1, val1);
    }

    private static class Value {
        public final double value;
        public final int pos;

        public Value(int pos, double value) {
            this.pos = pos;
            this.value = value;
        }
    }

}