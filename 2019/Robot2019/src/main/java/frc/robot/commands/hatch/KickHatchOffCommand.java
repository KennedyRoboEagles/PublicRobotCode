package frc.robot.commands.hatch;

import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.WaitCommand;
import frc.robot.commands.hatch.ControlHatchCommand.Direction;

public class KickHatchOffCommand extends CommandGroup {

    public KickHatchOffCommand() {
        addSequential(new ControlHatchCommand(Direction.kExtend));
        // addSequential(new WaitCommand(1.0));
        addSequential(new ControlHatchCommand(Direction.kRetract));
    }


}