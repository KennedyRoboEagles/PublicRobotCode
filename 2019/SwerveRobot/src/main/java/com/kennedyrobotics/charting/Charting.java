package com.kennedyrobotics.charting;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import com.team254.lib.trajectory.Trajectory;
import com.team254.lib.trajectory.timing.TimedState;
import frc.robot.trajectory.TrajectoryGenerator;
import org.knowm.xchart.SwingWrapper;
import org.knowm.xchart.XYChart;
import org.knowm.xchart.XYChartBuilder;
import org.knowm.xchart.XYSeries;
import org.knowm.xchart.style.lines.SeriesLines;
import org.knowm.xchart.style.markers.SeriesMarkers;

import static com.kennedyrobotics.charting.FieldConstants.*;

public class Charting {

    static boolean HALF_FIELD = true;

    static double SIZE_MODIFIER = 2.5;

    public static void chartPath(List<Pose2d> poses) {
        var path = TrajectoryGenerator.getInstance().generateTrajectory(false, poses, Arrays.asList(), 96.0, 60.0, 60,
                9.0, 45, 1);
        chartPath(path);
    }

    public static void chartPath(String name, List<Pose2d> poses) {
        var path = TrajectoryGenerator.getInstance().generateTrajectory(false, poses, Arrays.asList(), 96.0, 60.0, 60,
                9.0, 45, 1);
        chartPath(name, path);
    }

    public static void chartPath(Trajectory<TimedState<Pose2dWithCurvature>> path) {
        chartPath("Path", path);
    }

    public static void chartPath(String name, Trajectory<TimedState<Pose2dWithCurvature>> path) {
        var xArray = new ArrayList<Double>();
        var yArray = new ArrayList<Double>();

        for (int i = 0; i < path.length(); i += 1) {
            var s = path.getState(i).state();

            double x = s.getTranslation().x();
            double y = s.getTranslation().y();
            xArray.add(x);
            yArray.add(y);
        }

        chartField(name, xArray, yArray);
    }

    public static void chartField(String name, ArrayList<Double> x, ArrayList<Double> y) {
        double[] xData = new double[x.size()];
        double[] yData = new double[y.size()];

        for (int i = 0; i < x.size(); i++) {
            xData[i] = x.get(i);
        }

        for (int i = 0; i < y.size(); i++) {
            yData[i] = y.get(i);
        }
        chartField(name, xData, yData);
    }

    public static enum FieldType {
        NONE, HALF, FULL
    }

    public static class ChartMaker {
        public XYChart chart;
        private final FieldType field;

        public ChartMaker(String name, FieldType type) {
            this.field = type;
            if (type == FieldType.NONE) {
                this.chart = new XYChartBuilder().title(name).build();
            } else {
                this.chart = getFieldChart(name, type == FieldType.HALF);
            }
        }

        public void add(String name, Translation2d... translations) {
            ArrayList<Double> x = new ArrayList<>();
            ArrayList<Double> y = new ArrayList<>();
            for (Translation2d t : translations) {
                x.add(t.x());
                y.add(t.y());
            }
            add(name, x, y);
        }

        public void add(String name, Color color, Translation2d... translations) {
            ArrayList<Double> x = new ArrayList<>();
            ArrayList<Double> y = new ArrayList<>();
            for (Translation2d t : translations) {
                x.add(t.x());
                y.add(t.y());
            }
            add(name, color, x, y);
        }

        public void add(String name, ArrayList<Translation2d> translations) {
            ArrayList<Double> x = new ArrayList<>();
            ArrayList<Double> y = new ArrayList<>();
            for (Translation2d t : translations) {
                x.add(t.x());
                y.add(t.y());
            }
            add(name, x, y);
        }

        public void add(String name, List<Translation2d> translations) {
            ArrayList<Double> x = new ArrayList<>();
            ArrayList<Double> y = new ArrayList<>();
            for (Translation2d t : translations) {
                x.add(t.x());
                y.add(t.y());
            }
            add(name, x, y);
        }

        public void add(String name, ArrayList<Double> x, ArrayList<Double> y) {
            add(name, Color.BLACK, x, y);
        }

        public void add(String name, Color color, ArrayList<Double> x, ArrayList<Double> y) {
            double[] xData = new double[x.size()];
            double[] yData = new double[y.size()];

            for (int i = 0; i < x.size(); i++) {
                xData[i] = x.get(i);
            }

            for (int i = 0; i < y.size(); i++) {
                yData[i] = y.get(i);
            }

            addSeries(chart, name, color, xData, yData, false);
        }

        public XYChart build() {
            if (field != FieldType.NONE) {
                addField(chart);
                {
                    final double xMax = 54.0 * (field == FieldType.HALF ? 6.0 : 12.0);
                    chart.getStyler().setXAxisMin(0.0);
                    chart.getStyler().setXAxisMax(xMax);

                    // chart.getStyler().setYAxisMin(0.0);
                    // @TODO(Ryan): This is really hacky, to invert the Y axis to match teh 1323 Coordinate system
                    //  Should add feature to xchart, as right now no units appear on the charter
                    chart.getStyler().setYAxisMin(WIDTH);
                    chart.getStyler().setYAxisMax(-WIDTH);
                }

            } else {
                double max = Double.NEGATIVE_INFINITY;
                var series = chart.getSeriesMap().values();
                for (XYSeries s : series) {
                    for (Double d : s.getXData()) {
                        if (d > max) {
                            max = d;
                        }
                    }
                    for (Double d : s.getYData()) {
                        if (d > max) {
                            max = d;
                        }
                    }
                }
                chart.getStyler().setXAxisMax(max);
                chart.getStyler().setYAxisMax(max);
            }


            return chart;
        }

        public void updateSeries(String name, double errorBarSize, List<Translation2d> translations) {
            final int size = translations.size();
            double[] x = new double[size];
            double[] y = new double[size];
            double[] errorBar = new double[size];

            // String out = "";
            for (int i = 0; i < size; i++) {
                var t = translations.get(i);
                x[i] = t.x();
                y[i] = t.y();
                // out+=t;
                errorBar[i] = errorBarSize;
            }
            // System.out.println(out);

            chart.updateXYSeries(name, x, y, errorBar);
        }

        public void updateSeries(String name, double errorBarSize, Translation2d... translations) {
            final int size = translations.length;
            double[] x = new double[size];
            double[] y = new double[size];
            double[] errorBar = new double[size];

            for (int i = 0; i < size; i++) {
                x[i] = translations[i].x();
                y[i] = translations[i].y();
                errorBar[i] = errorBarSize;
            }

            chart.updateXYSeries(name, x, y, errorBar);

        }

        public void graph() {
            build();
            new SwingWrapper(chart).displayChart();
        }

        public void add(String name, double[] xData, double[] yData) {
            addSeries(chart, name, Color.BLACK, xData, yData, false);
        }

    }

    public static XYChart getFieldChart(String name, boolean halfField) {
        return new XYChartBuilder().width((int) ((halfField ? (LENGTH / 2.0) : LENGTH) * SIZE_MODIFIER))
                .height((int) (WIDTH * SIZE_MODIFIER)).title(name).xAxisTitle("X").yAxisTitle("Y").build();
    }

    public static void chartField(String name, double[] x, double[] y) {
        ChartMaker chartBuilder = new ChartMaker(name, HALF_FIELD ? FieldType.HALF : FieldType.FULL);
        chartBuilder.add("Robot Path", x, y);

        chartBuilder.graph();
    }

    private static void addField(XYChart chart) {
        addFieldBorder(chart);
        addFeederStations(chart);
        addRocket(chart);
        addCargoShip(chart);
        addHab(chart);
    }

    private static void addFeederStations(XYChart chart) {
        final double lineLength = 16.8438;
        addFieldDashLine(chart, "Feeder Station", Color.GRAY,
                0, WALL_TO_FEEDER,
                lineLength, WALL_TO_FEEDER
        );
    }

    private static void addCargoShip(XYChart chart) {

        // Outline
        {
            double[] x = { DRV_W_TO_CARGO_SHIP_FACE, DRV_W_TO_CARGO_SHIP_FACE, DRV_W_TO_CARGO_SHIP_END_ANGLE, MIDLINE };
            double[] y = { CENTER_LINE, CENTER_LINE - CARGO_SHIP_FACE_EDGE_FROM_CENTER, CARGO_SHIP_SIDE_TO_WALL,
                    CARGO_SHIP_SIDE_TO_WALL };
            addFieldPiece(chart, "Cargo ship", x, y, false);
        }

        Color c = Color.GRAY;
        addFieldDashLine(chart, "Cargo Ship Face Dash", c,
                DRV_W_TO_CARGO_SHIP_FACE - CARGO_SHIP_TAPE_LENGTH, CENTER_LINE - CARGO_SHIP_FACE_CENTER_FROM_CENTER,
                    DRV_W_TO_CARGO_SHIP_FACE, CENTER_LINE - CARGO_SHIP_FACE_CENTER_FROM_CENTER);

        double y1 = CARGO_SHIP_SIDE_TO_WALL;
        double y2 = CARGO_SHIP_SIDE_TO_WALL - CARGO_SHIP_TAPE_LENGTH;
        addFieldDashLine(chart, "Cargo Ship Bay 1 Dash", c, CARGO_SHIP_BAY_1_X, y1, CARGO_SHIP_BAY_1_X, y2);
        addFieldDashLine(chart, "Cargo Ship Bay 2 Dash", c, CARGO_SHIP_BAY_2_X, y1, CARGO_SHIP_BAY_2_X, y2);
        addFieldDashLine(chart, "Cargo Ship Bay 3 Dash", c, CARGO_SHIP_BAY_3_X, y1, CARGO_SHIP_BAY_3_X, y2);
    }

    public static List<Translation2d> squareAround(Translation2d translation, double diagonal) {
        var list = new ArrayList<Translation2d>();

        double number = diagonal;
        number /= 2;
        list.add(translation.translateBy(number, new Rotation2d(45)));
        list.add(translation.translateBy(number, new Rotation2d(90 + 45)));
        list.add(translation.translateBy(number, new Rotation2d(180 + 45)));
        list.add(translation.translateBy(number, new Rotation2d(360 - 45)));

        return list;
    }

    public static List<Translation2d> circleAround(Translation2d translation, double radius) {
        return circleAround(translation, radius, 10);
    }

    public static List<Translation2d> rectangleAround(Translation2d point1, Translation2d point2, double diag) {
        var list = new ArrayList<Translation2d>();
        var angle = Translation2d.updatedGetAngle(point1, point2);

        Translation2d firstPoint = point1.translateBy(diag, angle.rotateBy(Rotation2d.fromDegrees(90 + 45)));
        list.add(firstPoint);
        list.add(point1.translateBy(diag, angle.rotateBy(Rotation2d.fromDegrees(180 + 45))));
        list.add(point2.translateBy(diag, angle.rotateBy(Rotation2d.fromDegrees(270 + 45))));
        list.add(point2.translateBy(diag, angle.rotateBy(Rotation2d.fromDegrees(45))));
        list.add(firstPoint);

        return list;
    }

    /**
     * 
     * @param translation
     * @param radius
     * @param resolution  Points in circle
     * @return
     */
    public static List<Translation2d> circleAround(Translation2d translation, double radius, double resolution) {
        var list = new ArrayList<Translation2d>();

        final double tick = 360 / resolution;
        for (double a = 0; a <= 360; a += tick) {
            list.add(translation.translateBy(radius, new Rotation2d(a)));
        }

        return list;
    }

    /**
     * Create field dash line
     * @param chart
     * @param name
     * @param c
     * @param x1 Start x
     * @param y1 Start x
     * @param x2 End x
     * @param y2 End y
     */
    private static void addFieldDashLine(XYChart chart, String name, Color c, double x1, double y1, double x2,
            double y2) {
        var s = addDashLine(chart, name, c, x1, y1, x2, y2);

        var h = addHorizontalFlip(name + "HFlip", c, chart, s, true);
        if (!HALF_FIELD) {
            addVerticalFlip(name + "VFlip", c, chart, h, true);
        }
    }

    /**
     * Create dashline
     * @param chart
     * @param name
     * @param c
     * @param x1 Start x
     * @param y1 Start x
     * @param x2 End x
     * @param y2 End y
     * @return
     */
    private static XYSeries addDashLine(XYChart chart, String name, Color c, double x1, double y1, double x2,
            double y2) {
        double[] x = { x1, x2 };
        double[] y = { y1, y2 };
        return addSeries(chart, name, c, x, y, true);
    }

    private static void addHab(XYChart chart) {
        // RED

        // HAB 1 Outline
        {
            double[] x = { DRIVER_WALL_TO_HAB_3, DRV_W_TO_RAMP, DRV_W_TO_RAMP, DRIVER_WALL_TO_HAB_3,
                    DRIVER_WALL_TO_HAB_3 };
            double[] y = { CENTER_LINE + Y_CENTER_TO_END_OF_RAMP, CENTER_LINE + Y_CENTER_TO_END_OF_RAMP,
                    CENTER_LINE - Y_CENTER_TO_END_OF_RAMP, CENTER_LINE - Y_CENTER_TO_END_OF_RAMP,
                    CENTER_LINE + Y_CENTER_TO_END_OF_RAMP };

            addRedBlueFieldPiece(chart, "HAB1 Outline", x, y, true);
            // var hab1outline = addSeries(chart, "Red HAB1 Outline", Color.RED, x, y);
            // addVerticalFlip("Blue HAB1 Outline", Color.BLUE, chart, hab1outline);
        }

        // HAB 1 Detail
        {
            double[] x = { DRIVER_WALL_TO_HAB_3, DRIVER_WALL_TO_HAB_3 + HAB_3_TO_RAMP,
                    DRIVER_WALL_TO_HAB_3 + HAB_3_TO_RAMP, DRIVER_WALL_TO_HAB_3, DRIVER_WALL_TO_HAB_3 };
            double[] y = { CENTER_LINE + Y_CENTER_TO_EDGE_OF_RAMP, CENTER_LINE + Y_CENTER_TO_EDGE_OF_RAMP,
                    CENTER_LINE - Y_CENTER_TO_EDGE_OF_RAMP, CENTER_LINE - Y_CENTER_TO_EDGE_OF_RAMP,
                    CENTER_LINE + Y_CENTER_TO_EDGE_OF_RAMP };
            addRedBlueFieldPiece(chart, "HAB1 Detail", x, y, false);
            // var hab1details = addSeries(chart, "Red HAB1 Detail", Color.RED, x, y);
            // addVerticalFlip("Blue HAB1 Detail", Color.BLUE, chart, hab1details);
        }

        // HAB 3 Outline
        {
            double[] x = { 0, DRIVER_WALL_TO_HAB_3, DRIVER_WALL_TO_HAB_3, 0, 0 };
            double[] y = { CENTER_LINE + Y_CENTER_TO_EDGE_OF_RAMP, CENTER_LINE + Y_CENTER_TO_EDGE_OF_RAMP,
                    CENTER_LINE - Y_CENTER_TO_EDGE_OF_RAMP, CENTER_LINE - Y_CENTER_TO_EDGE_OF_RAMP,
                    CENTER_LINE + Y_CENTER_TO_EDGE_OF_RAMP };
            addRedBlueFieldPiece(chart, "HAB3 Outline", x, y, false);
        }

        // HAB 2 Detail
        {
            double[] x = { 0, DRIVER_WALL_TO_HAB_3 };
            double[] y = { CENTER_LINE + Y_CENTER_TO_EDGE_OF_2, CENTER_LINE + Y_CENTER_TO_EDGE_OF_2 };
            addRedBlueFieldPiece(chart, "HAB2 Detail 1", x, y, true);
        }
        {
            double[] x = { 0, DRIVER_WALL_TO_HAB_3 };
            double[] y = { CENTER_LINE - Y_CENTER_TO_EDGE_OF_2, CENTER_LINE - Y_CENTER_TO_EDGE_OF_2 };
            addRedBlueFieldPiece(chart, "HAB2 Detail 2", x, y, true);
        }

        // Depot
        {
            double[] x = { 0, DRV_W_TO_DEPOT + DEPOT_WIDTH, DRV_W_TO_DEPOT + DEPOT_WIDTH, DRV_W_TO_DEPOT,
                    DRV_W_TO_DEPOT, 0 };
            double[] y = { EDGE_TO_DEPOT-WIDTH/2, EDGE_TO_DEPOT-WIDTH/2, CENTER_LINE - Y_CENTER_TO_EDGE_OF_RAMP,
                    CENTER_LINE - Y_CENTER_TO_EDGE_OF_RAMP, EDGE_TO_DEPOT + DEPOT_WIDTH-WIDTH/2, EDGE_TO_DEPOT + DEPOT_WIDTH-WIDTH/2 };
            addFieldPiece(chart, "Depot", x, y, false);
        }

    }

    private static void addFieldBorder(XYChart chart) {

        // Outline
        {
            double[] x = {        0, 0,        LENGTH,  LENGTH,         0 };
            double[] y = { -WIDTH/2, WIDTH/2, WIDTH/2, -WIDTH/2, -WIDTH/2 };
            addSeries(chart, "Field Border", Color.BLACK, x, y, false);
        }

        // Center Line
        {
            // double
            double[] x = { DRV_W_TO_RAMP, DRV_W_TO_CARGO_SHIP_FACE };
            double[] y = { CENTER_LINE, CENTER_LINE };
            var s = addSeries(chart, "Midline", Color.BLACK, x, y, true);
            addVerticalFlip("Midline Flip", Color.BLACK, chart, s, true);
        }

        {
            double[] x = { MIDLINE, MIDLINE };
            double[] y = { -WIDTH/2, WIDTH/2 };
            addSeries(chart, "Mid line", Color.BLACK, x, y, true);
        }
    }

    private static void addRocket(XYChart chart) {
        // double[] x = { 202, 202, 217, 243, 258, 258, 202 };
        // // double[] y = { 0, 9, 32, 32, 9, 0, 0 };

        {
            Translation2d corner1 = new Translation2d(209.4377, 9.2291 - WIDTH/2);
            Translation2d corner2 = new Translation2d(248.3182, 9.2291 - WIDTH/2);

            Translation2d center1 = corner1.translateBy(ROCKET_HATCH_FACE_WIDTH / 2.0, new Rotation2d(ROCKET_ANGLE));
            Translation2d nextPoint1 = center1.translateBy(ROCKET_TAPE_LENGTH, new Rotation2d(ROCKET_ANGLE + 90));
            Translation2d center2 = corner2.translateBy(ROCKET_HATCH_FACE_WIDTH / 2.0,
                    Rotation2d.fromDegrees(180 - ROCKET_ANGLE));
            Translation2d nextPoint2 = center2.translateBy(ROCKET_TAPE_LENGTH, new Rotation2d(90 - ROCKET_ANGLE));

            Color c = Color.GRAY;
            {
                double[] x = { center1.x(), nextPoint1.x() };
                double[] y = { center1.y(), nextPoint1.y() };
                var s = addSeries(chart, "Red Rocket Near Tape Line", c, x, y, true);
                addFieldPiece(chart, "Rocket Near Tape Line", Color.GRAY, x, y, true);
            }
            {
                double[] x = { center2.x(), nextPoint2.x() };
                double[] y = { center2.y(), nextPoint2.y() };
                addFieldPiece(chart, "Rocket Far Tape Line", Color.GRAY, x, y, true);
            }

        }

        double[] x = { 209.4377, 209.4377, 219.5674, 238.1885, 248.3182, 248.3182 };
        double[] y = { 0 - WIDTH/2, 9.2291 - WIDTH/2, 27.6917 - WIDTH/2, 27.6917 - WIDTH/2, 9.2291 - WIDTH/2, 0 - WIDTH/2 };
        addFieldPiece(chart, "Rocket", x, y, false);
    }

    private static void addFieldPiece(XYChart chart, String name, double[] x, double[] y, boolean dash) {
        addFieldPiece(chart, name, null, x, y, dash);
    }

    /**
     * Assumes provided piece is RED Right
     */
    private static void addFieldPiece(XYChart chart, String name, Color override, double[] x, double[] y,
            boolean dash) {

        String firstName = "Red " + name + " R";
        Color red = (override == null) ? Color.RED : override;
        Color blue = (override == null) ? Color.BLUE : override;

        var piece = addSeries(chart, firstName, red, x, y, dash);

        addHorizontalFlip("Red " + name + " L", red, chart, piece, dash);
        if (!HALF_FIELD) {
            addVerticalFlip("Blue " + name + " R", blue, chart, piece, dash);
            addHorizontalFlip("Blue " + name + " L", blue, chart, chart.getSeriesMap().get("Blue " + name + " R"),
                    dash);
        }
    }

    private static void addRedBlueFieldPiece(XYChart chart, String name, double[] x, double[] y, boolean dash) {
        var piece = addSeries(chart, "Red " + name, Color.RED, x, y, dash);

        if (!HALF_FIELD)
            addVerticalFlip("Blue " + name, Color.BLUE, chart, piece, dash);
    }

    // private static XYSeries addSeries(XYChart chart, String name, Color c,
    // double[] x, double[] y) {
    // return addSeries(chart, name, c, x, y, false);
    // }

    public static XYSeries addSeries(XYChart chart, String name, Color c, double[] x, double[] y, boolean dash) {
        XYSeries s = chart.addSeries(name, x, y);
        s.setLineColor(c);
        s.setMarker(SeriesMarkers.NONE);
        s.setShowInLegend(false);
        if (dash)
            s.setLineStyle(SeriesLines.DASH_DOT);
        return s;
    }

    private static XYSeries addHorizontalFlip(String name, Color c, XYChart chart, XYSeries series, boolean dash) {
        double[] y = series.getYData();
        double[] newY = new double[y.length];
        for (int i = 0; i < y.length; i++) {
//            double val = (27.0 * 12.0) - y[i];
//            newY[i] = val;
            newY[i] = -y[i];
        }
        var s = addSeries(chart, name, c, series.getXData(), newY, dash);
        return s;
    }

    private static XYSeries addVerticalFlip(String name, Color c, XYChart chart, XYSeries series, boolean dash) {
        double[] x = series.getXData();
        double[] newX = new double[x.length];

        for (int i = 0; i < x.length; i++) {
            double val = (54.0 * 12) - x[i];
            newX[i] = val;
        }

        var s = addSeries(chart, name, c, newX, series.getYData(), dash);
        return s;
    }
}
