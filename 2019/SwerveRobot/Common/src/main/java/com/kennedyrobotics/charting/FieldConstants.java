package com.kennedyrobotics.charting;

// @TODO Rewrite this constants to use 1323's cordinate systems
//

public class FieldConstants {

    public static final double WIDTH = (27.0 * 12.0);

    public static final double CENTER_LINE = 0;
    public static final double LENGTH = (54.0 * 12.0);
    public static final double MIDLINE = LENGTH / 2.0;

    public static final double DRIVER_WALL_TO_HAB_3 = 47.9997;
    public static final double HAB_3_TO_RAMP = 36;
    public static final double DRV_W_TO_RAMP = 95.2752;

    public static final double Y_CENTER_TO_EDGE_OF_RAMP = 64.1684;
    public static final double Y_CENTER_TO_END_OF_RAMP = 75.2758;
    public static final double Y_CENTER_TO_EDGE_OF_2 = 24;
    public static final double LEVEL_2_WIDTH = Y_CENTER_TO_EDGE_OF_RAMP - Y_CENTER_TO_EDGE_OF_2;

    public static final double EDGE_TO_DEPOT = 71 + (5.0 / 8.0);
    public static final double DRV_W_TO_DEPOT = 45;
    public static final double DEPOT_WIDTH = 3;

    public static final double WALL_TO_FEEDER = 25.72 - WIDTH/2;

    public static final double DRV_W_TO_CARGO_SHIP_FACE = 220.25;
    public static final double RAMP_TO_CARGO_SHIP_FACE = DRV_W_TO_CARGO_SHIP_FACE - DRV_W_TO_RAMP;

    public static final double CARGO_SHIP_FACE_CENTER_FROM_CENTER = 11 + (7.0 / 8.0);
    public static final double CARGO_SHIP_SIDE_TO_WALL = 133 + (3.0 / 8.0 ) - WIDTH/2;
    public static final double DRV_W_TO_CARGO_SHIP_END_ANGLE = 249.177777;

    public static final double CARGO_SHIP_FACE_EDGE_FROM_CENTER = 22.5;
    public static final double CARGO_SHIP_TAPE_LENGTH = 18.1875;
    public static final double ROCKET_TAPE_LENGTH = 18;
    public static final double ROCKET_HATCH_FACE_WIDTH = 21.032;

    public static final double CARGO_SHIP_BAY_1_X = MIDLINE - 64.4189;
    public static final double CARGO_SHIP_BAY_2_X = MIDLINE - 42.5811;
    public static final double CARGO_SHIP_BAY_3_X = MIDLINE - 20.8311;

    public static final double ROCKET_ANGLE = 61.25;
}