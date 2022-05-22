package sample;

import javafx.geometry.Orientation;
import javafx.scene.control.*;
import javafx.scene.control.Label;
import javafx.scene.layout.*;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

import javafx.scene.control.Slider;
import javafx.scene.control.ToggleButton;


public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        var sp = SerialPortService.getSerialPort("COM5");
        var outputStream = sp.getOutputStream();

        var pane = new BorderPane();
        primaryStage.setTitle("Thermometer of Heater");

        var label = new Label();
        var label_name = new Label();
        ToggleButton button = new ToggleButton("Send temperature");
        ToggleButton b2 = new ToggleButton("Heater disabled");

        ToggleGroup toggleGroup = new ToggleGroup();
        button.setToggleGroup(toggleGroup);
        b2.setToggleGroup(toggleGroup);

       toggleGroup.getSelectedToggle();
        boolean ON = button.isSelected();
        boolean OFF = button.isSelected();


        label_name.setText("Set thermometer to \n desired temperature");


        var slider = new Slider();
        slider.setMin(20.0);
        slider.setMax(35.0);
        slider.setOrientation(Orientation.VERTICAL);
        slider.setShowTickLabels(true);
        slider.setShowTickMarks(true);
        slider.setMajorTickUnit(5);
        slider.setMinorTickCount(4);
        slider.setBlockIncrement(1);


        label.textProperty().bind(slider.valueProperty().asString(" %.0f ºc"));


        button.setOnMousePressed(value -> {
            try {
                int value1 = (int) slider.getValue();
                int i = 1;
                for(; i <= 400000; ){
                outputStream.write(value1);
                i ++;}
            } catch(IOException e){
                e.printStackTrace();
            }
        });

        b2.setOnMousePressed(value -> {
            try{
                outputStream.write(-1);
                System.out.println("disabled");
            }catch(IOException e){
                e.printStackTrace();
            }
        });






        pane.setLeft(slider);
        pane.setCenter(label);
        pane.setTop(label_name);
        pane.setBottom(button);
        pane.setPadding(new Insets(30, 90, 30, 90));


        var scene = new Scene(pane, 300, 700);

        primaryStage.setScene(scene);

        primaryStage.setX(900);
        primaryStage.setY(65);

        primaryStage.show();
        

   }
}




