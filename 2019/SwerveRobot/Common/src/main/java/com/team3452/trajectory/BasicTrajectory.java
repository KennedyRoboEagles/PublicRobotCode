package com.team3452.trajectory;

/**
 * Implementation of a Trajectory using arrays as the underlying storage
 * mechanism.
 *
 * @author Jared341
 */
public class BasicTrajectory {

    public Segment interpolate(double timestamp) {
        int pos = DoubleArrayPositionBinarySearch.findClosest(times, timestamp);
        return segments_[pos];
    }

    public double perdictedTime() {
        return times[times.length - 1];
    }

    public static class Segment {

        public double pos, vel, acc, jerk, heading, dt, x, y;

        public Segment() {
        }

        public Segment(double pos, double vel, double acc, double jerk, double heading, double dt, double x, double y) {
            this.pos = pos;
            this.vel = vel;
            this.acc = acc;
            this.jerk = jerk;
            this.heading = heading;
            this.dt = dt;
            this.x = x;
            this.y = y;
        }

        public Segment(Segment to_copy) {
            pos = to_copy.pos;
            vel = to_copy.vel;
            acc = to_copy.acc;
            jerk = to_copy.jerk;
            heading = to_copy.heading;
            dt = to_copy.dt;
            x = to_copy.x;
            y = to_copy.y;
        }

        public String toString() {
            return "pos: " + pos + "; vel: " + vel + "; acc: " + acc + "; jerk: " + jerk + "; heading: " + heading;
        }

        public void flipPos() {
            this.pos = -this.pos;
        }

    }

    Segment[] segments_ = null;
    double[] times = null;

    public BasicTrajectory(int length) {
        Segment[] newSegments_ = new Segment[length];
        for (int i = 0; i < length; ++i) {
            newSegments_[i] = new Segment();
        }
        setSegements(newSegments_);
    }

    public void updateTimes() {
        setSegements(this.segments_);
    }

    private void setSegements(Segment[] segments) {
        this.segments_ = segments;
        times = new double[segments.length];

        double t = 0;
        final double dt = segments[0].dt;

        for (int i = 0; i < getNumSegments(); i++) {
            times[i] = t;
            t += dt;
            // System.out.println(i + "\t" + getSegment(i));
            // System.out.println(i + "\t" + times[i]);
        }
    }

    public BasicTrajectory(Segment[] segments) {
        setSegements(segments);
    }

    public void flipY() {
        for (Segment s : segments_) {
            s.flipPos();
        }
        updateTimes();
    }

    public int getNumSegments() {
        return segments_.length;
    }

    public Segment getSegment(int index) {
        return segments_[index];
    }

    public void setSegment(int index, Segment segment) {
        segments_[index] = segment;
    }

    public void scale(double scaling_factor) {
        for (int i = 0; i < getNumSegments(); ++i) {
            segments_[i].pos *= scaling_factor;
            segments_[i].vel *= scaling_factor;
            segments_[i].acc *= scaling_factor;
            segments_[i].jerk *= scaling_factor;
        }
    }

    public void append(BasicTrajectory to_append) {
        Segment[] temp = new Segment[getNumSegments() + to_append.getNumSegments()];

        for (int i = 0; i < getNumSegments(); ++i) {
            temp[i] = new Segment(segments_[i]);
        }
        for (int i = 0; i < to_append.getNumSegments(); ++i) {
            temp[i + getNumSegments()] = new Segment(to_append.getSegment(i));
        }

        this.segments_ = temp;
        setSegements(this.segments_);
    }

    public BasicTrajectory copy() {
        BasicTrajectory cloned = new BasicTrajectory(getNumSegments());
        cloned.segments_ = copySegments(this.segments_);
        return cloned;
    }

    private Segment[] copySegments(Segment[] tocopy) {
        Segment[] copied = new Segment[tocopy.length];
        for (int i = 0; i < tocopy.length; ++i) {
            copied[i] = new Segment(tocopy[i]);
        }
        return copied;
    }

    public String toStringDT() {
        String str = "";
        for (int i = 0; i < getNumSegments(); ++i) {
            Segment segment = getSegment(i);
            str += i;
            str += ",";
            str += segment.dt;
            str += "\n";
        }
        return str;
    }

    public String toStringPosition() {
        String str = "";
        double t = 0;
        for (int i = 0; i < getNumSegments(); ++i) {
            Segment segment = getSegment(i);
            str += t;
            str += ",";
            str += segment.pos;
            str += "\n";
            t += segment.dt;
        }
        return str;
    }

    public String toString() {
        String str = "Segment\tPos\tVel\tAcc\tJerk\tHeading\n";
        for (int i = 0; i < getNumSegments(); ++i) {
            Segment segment = getSegment(i);
            str += i + "\t";
            str += segment.pos + "\t";
            str += segment.vel + "\t";
            str += segment.acc + "\t";
            str += segment.jerk + "\t";
            str += segment.heading + "\t";
            str += segment.dt + "\t";
            str += "\n";
        }

        return str;
    }

    public String toStringProfile() {
        return toString();
    }

    public String toStringEuclidean() {
        String str = "Segment\tx\ty\tHeading\n";
        for (int i = 0; i < getNumSegments(); ++i) {
            Segment segment = getSegment(i);
            str += i + "\t";
            str += segment.x + "\t";
            str += segment.y + "\t";
            str += segment.heading + "\t";
            str += "\n";
        }

        return str;
    }
}