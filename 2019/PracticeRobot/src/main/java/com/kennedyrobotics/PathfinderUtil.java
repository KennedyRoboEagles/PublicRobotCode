package com.kennedyrobotics;

import java.io.File;

import jaci.pathfinder.Pathfinder;
import jaci.pathfinder.Trajectory;

public class PathfinderUtil {

    /**
     * https://github.com/CurtinFRC/2018-PowerUp/blob/605b409eb3652bfa9403863b5b5bdc118b3b6ce9/common/src/include/curtinfrc/motors/MotionProfiling.h
     */
    public static Trajectory loadFile(String fileName)  {
        File file = new File(fileName);
        return  Pathfinder.readFromCSV(file);
    }
}