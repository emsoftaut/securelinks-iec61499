package securelinks.handlers;

import java.util.List;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import securelinks.Connection;
import securelinks.ConnectionAdapter;
import javafx.scene.Parent;
import javafx.scene.Scene;



public class JFXUI extends Application {
	@Override
	public void start(Stage stage) {
		try {
			FXMLLoader loader = new FXMLLoader(getClass().getResource("JFXUI.fxml"));
			Parent root = loader.load();
		    Scene scene = new Scene(root);
		    stage.setTitle("Secure Links for IEC 61499");
		    stage.setScene(scene);
		    
		   /* Parameters params = getParameters();
		    List<String> list = params.getRaw();
		    
		    String sysFile = list.get(0);
		    String selectedApp = list.get(1);

		    ConnectionAdapter conAdpt =  new ConnectionAdapter();
		    conAdpt.loadSystem(sysFile, selectedApp);
		    
		    conAdpt.getInterDeviceDataConnections();
		    
		    //List<Connection> conList = conAdpt.getDataConnections();
		    List<Connection> conList = conAdpt.getInterDeviceDataConnections();
		    
		    UIController controller = loader.getController();
		    controller.addConnectionItemtoVbox(conList);*/
		    
		    stage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
}
