package com.kennedyrobotics.swerve.module;

public enum







ModuleID {
    FRONT_RIGHT(0, "Front Right"),
    FRONT_LEFT(3, "Front Left"),
    REAR_LEFT(2, "Rear Left"),
    REAR_RIGHT(1, "Rear Right");

    public final int id;
    public final String name;

    private ModuleID(int id, String name) {
        this.id = id;
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    public static ModuleID get(int id) {
        ModuleID ret = null;
        switch (id) {
            case 0:
                ret = FRONT_RIGHT;
                break;
            case 1:
                ret = REAR_RIGHT;
                break;
            case 2:
                ret = REAR_LEFT;
                break;
            case 3:
                ret = FRONT_LEFT;
                break;
        }

        if (ret == null) {
            System.out.println("Invalid SwerveModuleID: " + id);
            return null;
        }

        if (ret.id != id) {
            System.out.println("Major booboo in SwerveModuleID.get(int) " + ret + " (value " + ret.id
                    + ") does not equal " + id);
            return null;
        }
        return ret;
    }

    public static String getName(int id) {
        ModuleID ret = get(id);
        if (ret == null)
            return null;
        return ret.name;
    }
}

