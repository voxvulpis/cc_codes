module br.unesp.demo1 {
    requires javafx.controls;
    requires javafx.fxml;


    opens br.unesp.demo1 to javafx.fxml;
    exports br.unesp.demo1;
}