package sample;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;
import javafx.stage.Window;

import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{


        primaryStage.setTitle("Soccer Inputs");

        GridPane gridPane = createFormPane();
        addObjects(gridPane);
        Scene scene = new Scene(gridPane, 800, 500);


        primaryStage.setScene(scene);

        primaryStage.show();
    }


    private GridPane createFormPane() {
        GridPane gridPane = new GridPane();
        gridPane.setAlignment(Pos.CENTER);
        gridPane.setPadding(new Insets(40, 40, 40, 40));
        gridPane.setHgap(10);
        gridPane.setVgap(10);

        gridPane.setStyle("-fx-background-image: url(" +
                "'pitch2.jpg'" +
                "); " +
                "-fx-background-size: cover;");


        //Labels
        ColumnConstraints columnOneConstraints = new ColumnConstraints(100, 100, 100);
        columnOneConstraints.setHalignment(HPos.RIGHT);
        //TextField
        ColumnConstraints columnTwoConstrains = new ColumnConstraints(200,200, 100);
        columnTwoConstrains.setHgrow(Priority.ALWAYS);

        gridPane.getColumnConstraints().addAll(columnOneConstraints, columnTwoConstrains);

        return gridPane;
    }

    private void addObjects(GridPane gridPane) {
        Label headerLabel = new Label("Soccer Game");

        headerLabel.setTextFill(Color.WHITE);

        headerLabel.setFont(Font.font("Arial", FontWeight.BOLD, 46));

        gridPane.add(headerLabel, 1,0,4,1);
        GridPane.setHalignment(headerLabel, HPos.CENTER);
        GridPane.setMargin(headerLabel, new Insets(20, 0,20,0));

        Label massLabel = new Label("Mass : ");
        massLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        massLabel.setTextFill(Color.WHITE);
        gridPane.add(massLabel, 0,2);

        TextField massField = new TextField("0.4");
        massField.setPrefHeight(40);
        gridPane.add(massField, 1,2);


        Label massLabelUnit = new Label("kg");
        massLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        massLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(massLabelUnit, 2, 2);

        massField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        massField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });

        Label angularXSpeedLabel = new Label("wX : ");
        angularXSpeedLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        angularXSpeedLabel.setTextFill(Color.WHITE);
        gridPane.add(angularXSpeedLabel, 3,2);

        TextField angularXSpeedField = new TextField("0.0");
        angularXSpeedField.setPrefHeight(40);
        gridPane.add(angularXSpeedField, 4,2);

        Label angularXSpeedLabelUnit = new Label("deg/s");
        angularXSpeedLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        angularXSpeedLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(angularXSpeedLabelUnit, 5, 2);

        angularXSpeedField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        angularXSpeedField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });


        Label angularYSpeedLabel = new Label("wY : ");
        angularYSpeedLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        angularYSpeedLabel.setTextFill(Color.WHITE);
        gridPane.add(angularYSpeedLabel, 3,3);

        TextField angularYSpeedField = new TextField("300");
        angularYSpeedField.setPrefHeight(40);
        gridPane.add(angularYSpeedField, 4,3);

        Label angularYSpeedLabelUnit = new Label("deg/s");
        angularYSpeedLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        angularYSpeedLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(angularYSpeedLabelUnit, 5, 3);

        angularYSpeedField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        angularYSpeedField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });


        Label angularZSpeedLabel = new Label("wZ : ");
        angularZSpeedLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        angularZSpeedLabel.setTextFill(Color.WHITE);
        gridPane.add(angularZSpeedLabel, 3,4);

        TextField angularZSpeedField = new TextField("0.0");
        angularZSpeedField.setPrefHeight(40);
        gridPane.add(angularZSpeedField, 4,4);

        Label angularZSpeedLabelUnit = new Label("deg/s");
        angularZSpeedLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        angularZSpeedLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(angularZSpeedLabelUnit, 5, 4);

        angularZSpeedField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        angularZSpeedField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });


        Label frictionLabel = new Label("friction : ");
        frictionLabel.setFont(Font.font("Arial", FontWeight.BOLD, 14));
        frictionLabel.setTextFill(Color.WHITE);
        gridPane.add(frictionLabel, 3,5);

        TextField frictionField = new TextField("0.9");
        frictionField.setPrefHeight(40);
        gridPane.add(frictionField, 4,5);

        frictionField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        frictionField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });


        Label bouncingLabel = new Label("bouncing : ");
        bouncingLabel.setFont(Font.font("Arial", FontWeight.BOLD, 14));
        bouncingLabel.setTextFill(Color.WHITE);
        gridPane.add(bouncingLabel, 3,6);

        TextField bouncingField = new TextField("0.8");
        bouncingField.setPrefHeight(40);
        gridPane.add(bouncingField, 4,6);

        bouncingField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        bouncingField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });



        Label densityLabel = new Label("Air Density : ");
        densityLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        densityLabel.setTextFill(Color.WHITE);
        gridPane.add(densityLabel, 0, 3);

        TextField densityField = new TextField("1.1");
        densityField.setPrefHeight(40);
        gridPane.add(densityField, 1, 3);

        Label densityLabelUnit = new Label("kg/m^3");
        densityLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        densityLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(densityLabelUnit, 2, 3);

        densityField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        densityField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });



        Label speedXLabel = new Label("Air Speed X : ");
        speedXLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        speedXLabel.setTextFill(Color.WHITE);
        gridPane.add(speedXLabel, 0, 4);

        TextField speedXField = new TextField("0.3");
        speedXField.setPrefHeight(40);
        gridPane.add(speedXField, 1, 4);

        Label speedXLabelUnit = new Label("m/s ");
        speedXLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        speedXLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(speedXLabelUnit, 2, 4);

        speedXField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        speedXField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });



        Label speedZLabel = new Label("Air Speed Z : ");
        speedZLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        speedZLabel.setTextFill(Color.WHITE);
        gridPane.add(speedZLabel, 0, 5);

        TextField speedZField = new TextField("0.3");
        speedZField.setPrefHeight(40);
        gridPane.add(speedZField, 1, 5);

        Label speedZLabelUnit = new Label("m/s ");
        speedZLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        speedZLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(speedZLabelUnit, 2, 5);

        speedZField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        speedZField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });


        Label radiusLabel = new Label("Radius : ");
        radiusLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        radiusLabel.setTextFill(Color.WHITE);
        gridPane.add(radiusLabel, 0, 6);

        TextField radiusField = new TextField("0.11");
        radiusField.setPrefHeight(40);
        gridPane.add(radiusField, 1, 6);

        Label radiusLabelUnit = new Label("m");
        radiusLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        radiusLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(radiusLabelUnit, 2, 6);

        radiusField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        radiusField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });


        Label positionLabel = new Label("Position : ");
        positionLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        positionLabel.setTextFill(Color.WHITE);
        gridPane.add(positionLabel, 0, 7);

        TextField positionField = new TextField("3.5");
        positionField.setPrefHeight(40);
        gridPane.add(positionField, 1, 7);

        Label positionLabelUnit = new Label("m");
        positionLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        positionLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(positionLabelUnit, 2, 7);

        positionField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        positionField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });


        Label viscosityLabel = new Label("Viscosity : ");

        viscosityLabel.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        viscosityLabel.setTextFill(Color.WHITE);
        gridPane.add(viscosityLabel, 0, 8);

        TextField viscosityField = new TextField("0.00000181");
        viscosityField.setPrefHeight(40);
        gridPane.add(viscosityField, 1, 8);

        Label viscosityLabelUnit = new Label("kg/(m.s)");
        viscosityLabelUnit.setFont(Font.font("Arial", FontWeight.BOLD, 15));
        viscosityLabelUnit.setTextFill(Color.WHITE);
        gridPane.add(viscosityLabelUnit, 2, 8);

        viscosityField.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue,
                                String newValue) {
                Matcher matcher = Pattern
                        .compile(
                                "[0-9]{1,13}(\\.[0-9]*)?")
                        .matcher(newValue);
                if (!matcher.matches()) {
                    Platform.runLater(() -> {
                        viscosityField.setText(newValue.replaceAll(newValue, ""));
                    });
                }
            }
        });


        Button submitButton = new Button("Save");
        submitButton.setPrefHeight(40);
        submitButton.setDefaultButton(true);
        submitButton.setPrefWidth(100);
        gridPane.add(submitButton, 2, 10, 1, 1);
        GridPane.setHalignment(submitButton, HPos.CENTER);
        GridPane.setMargin(submitButton, new Insets(20, 0,20,0));

        submitButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                if(massField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the mass");
                    return;
                }
                double d = new Double(massField.getText());
                if(d == 0.0) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the mass bigger than 0");
                    return;
                }
                if(densityField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the air density");
                    return;
                }
                if(speedXField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the air speedX");
                    return;
                }
                if(speedZField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the air speedZ");
                    return;
                }
                if(radiusField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the radius");
                    return;
                }
                if(positionField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the position");
                    return;
                }
                double dd = new Double(positionField.getText());
                if(3.5 > dd || dd > 7.5) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the position between 3.5 and 7.5");
                    return;
                }
                if(viscosityField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the drag coefficient");
                    return;
                }
                if(angularXSpeedField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the wx");
                    return;
                }
                if(angularYSpeedField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the wy");
                    return;
                }
                if(angularZSpeedField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the wz");
                    return;
                }
                if(frictionField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the friction");
                    return;
                }
                if(bouncingField.getText().isEmpty()) {
                    showAlert(Alert.AlertType.ERROR, gridPane.getScene().getWindow(), "Form Error!", "Please enter the bouncing");
                    return;
                }

                fileStore(massField.getCharacters().toString(),densityField.getCharacters().toString(),
                        speedXField.getCharacters().toString(),speedZField.getCharacters().toString(),radiusField.getCharacters().toString(),positionField.getCharacters().toString(),
                        viscosityField.getCharacters().toString(),angularXSpeedField.getCharacters().toString(),
                        angularYSpeedField.getCharacters().toString(),angularZSpeedField.getCharacters().toString(),
                        frictionField.getCharacters().toString(),bouncingField.getCharacters().toString());
                showAlert(Alert.AlertType.CONFIRMATION, gridPane.getScene().getWindow(), "Success", "Done :)" );
            }
        });
    }

    private void showAlert(Alert.AlertType alertType, Window owner, String title, String message) {
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.initOwner(owner);
        alert.show();
    }

    public static void main(String[] args) {
        launch(args);
    }


    public static void fileStore(String mass,String density,String speedX,String speedZ,String radius, String position
            ,String viscosity,String wx,String wy,String wz,String friction,String bouncing) {
        File file = new File("../SoccerBall Semulation/SoccerBall Semulation/input.txt");
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(fos));

        try {
            bufferedWriter.write(mass);
            bufferedWriter.newLine();
            bufferedWriter.write(density);
            bufferedWriter.newLine();
            bufferedWriter.write(speedX);
            bufferedWriter.newLine();
            bufferedWriter.write(speedZ);
            bufferedWriter.newLine();
            bufferedWriter.write(radius);
            bufferedWriter.newLine();
            double x = new Double(position);
            bufferedWriter.write(Double.toString(-750 + (x*100)));
            bufferedWriter.newLine();
            bufferedWriter.write(viscosity);
            bufferedWriter.newLine();
            bufferedWriter.write(wx);
            bufferedWriter.newLine();
            bufferedWriter.write(wy);
            bufferedWriter.newLine();
            bufferedWriter.write(wz);
            bufferedWriter.newLine();
            bufferedWriter.write(friction);
            bufferedWriter.newLine();
            bufferedWriter.write(bouncing);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            bufferedWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
