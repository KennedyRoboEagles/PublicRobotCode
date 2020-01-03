package frc.robot.auto.modes;

import com.team254.lib.auto.AutoModeEndedException;
import frc.robot.auto.AutoModeBase2019;

/**
 * Fallback for when all autonomous modes do not work, resulting in a robot standstill
 */
public class StandStillMode extends AutoModeBase2019 {
    @Override
    protected void routine() throws AutoModeEndedException {
        System.out.println("Starting Stand Still Mode... Done!");
    }
}