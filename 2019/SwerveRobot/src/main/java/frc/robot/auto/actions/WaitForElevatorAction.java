/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.auto.actions;

import com.team254.lib.auto.actions.Action;

/**
 * 
 */
public class WaitForElevatorAction implements Action {
//    Elevator elevator;
//    double targetHeight;
//    boolean above;

    public WaitForElevatorAction(double height, boolean above){
//        elevator = Elevator.getInstance();
//        targetHeight = height;
//        this.above = above;
    }

    @Override
    public boolean isFinished() {
        return true;
//        return above ? (elevator.getHeight() > targetHeight) : (elevator.getHeight() < targetHeight);
    }

    @Override
    public void start() {

    }

    @Override
    public void update() {

    }

    @Override
    public void done() {

    }

}
