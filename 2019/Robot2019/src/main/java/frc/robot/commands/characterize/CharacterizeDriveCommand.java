package frc.robot.commands.characterize;

import java.util.ArrayList;
import java.util.List;

import com.team254.lib.physics.DriveCharacterization;

import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.InstantCommand;
import edu.wpi.first.wpilibj.command.PrintCommand;
import edu.wpi.first.wpilibj.command.WaitCommand;

public class CharacterizeDriveCommand extends CommandGroup {

    List<DriveCharacterization.VelocityDataPoint> velocityData = new ArrayList<>();
    List<DriveCharacterization.AccelerationDataPoint> accelerationData = new ArrayList<>();

    public CharacterizeDriveCommand() {
        addSequential(new InstantCommand() {
            @Override
            protected void initialize() {
                System.out.println("Clearning data");
                velocityData.clear();
                accelerationData.clear();
            }
        });
        
        addSequential(new PrintCommand("Collecting velocty data"));
        addSequential(new CollectVelocityDataCommand(velocityData, false, true));
        
        addSequential(new PrintCommand("Waiting"));
        addSequential(new WaitCommand(10));
        
        addSequential(new PrintCommand("Collecting acceleration data"));
        addSequential(new CollectAccelDataCommand(accelerationData, false, true));
        
        addSequential(new InstantCommand() {
           @Override
           protected void initialize() {
            try {
                System.out.println("Drive Characterization");
                DriveCharacterization.CharacterizationConstants constants = DriveCharacterization.characterizeDrive(velocityData, accelerationData);
    
                System.out.println("ks: " + constants.ks);
                System.out.println("kv: " + constants.kv);
                System.out.println("ka: " + constants.ka);
                       
            } catch (Exception e) {
                e.printStackTrace();
            }
           } 
        });
    }

}