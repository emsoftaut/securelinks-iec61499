package securelinks;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class Connection {
	private String dstFB;

	private String dstVar;
	private String dstFBDevice;
	
	private String srcFB;
	private String srcVar;
	private String srcFBDevice;
	
	private String connectionComment; // We are using comments attribute for SL annotations
	
	private static SysFileOperator sysReaderWriter;
	private static String selectedApp;
	
	private final String SECURE_LINK_REGEX = "@[sS][lL]\\s*\\((\\s*\\w*\\s*,\\s*\\w*\\s*,)\\s*\\w+\\s*\\)"; reg ex seedha karo
	
	
	public Connection() {
		
	}
	
	public static SysFileOperator getSysFileReader() {
		return sysReaderWriter;
	}
	
	public static void loadSysFile(String sysFile, String selectedApplication) {
		sysReaderWriter = new SysFileOperator(sysFile, selectedApplication);
		if(sysReaderWriter != null) 
			selectedApp = selectedApplication;
	}
	
	public static List<Connection> getDataConnections() {
		List <Connection> connections = null;
		if(sysReaderWriter != null) {
			connections = new ArrayList<Connection>();
			List <DeviceMappings> mappings = getDeviceMappings().stream() //filtering mappings that belong to the selected application
					.filter(m->m.getFrom().split("\\.")[0].equals(selectedApp)).collect(Collectors.toList());
			int numDataConnections = sysReaderWriter.getApplicationDataConnetionsCount();
			
			for(int i = 0; i < numDataConnections; i++) {
				Connection con = new Connection();
		    	con.setSourceFB(sysReaderWriter.getSrcConnectionFBName(i));
		    	con.setDestinationeFB(sysReaderWriter.getDstConnectionFBName(i));
		    	con.setSourceVariable(sysReaderWriter.getSrcFBDataVariableName(i));
		    	con.setDestinationVariable(sysReaderWriter.getDstFBDataVariableName(i));
		    	con.setConnectionComment(sysReaderWriter.getConnectionCommentValue(i)); 
		    	
		    	for(DeviceMappings map : mappings) {
		    		if(map.getFrom().split("\\.")[1].equals(con.getSourceFB()))
		    			con.setSourceFBDevice(map.getTo().split("\\.")[0]);
		    		if(map.getFrom().split("\\.")[1].equals(con.getDestinationFB()))
		    			con.setDestinationFBDevice(map.getTo().split("\\.")[0]);
		    	}
	
		    	connections.add(con);
		    	//System.out.println(con.outFB +"."+ con.outVariable+"--->"+con.inFB+"."+ con.inVariable);
		    }
		}
		return connections;
	}
	
	public static List<Connection> getInterDeviceDataConnections() {
		
		List <Connection> connections = getDataConnections();
		List <Connection> interDevConns = new ArrayList<Connection>();
		for(Connection con : connections) {
			if(!con.getSourceFBDevice().equals(con.getDestinationFBDevice()))
				interDevConns.add(con);
		}
		return interDevConns;
	}
	
	public static void UpdateConnections(List<Connection> conList) {
		
		List <Connection> sysFileCons = getInterDeviceDataConnections();
		
		//Assuming that connections will be the same in existing system file 
		//and the modified connection list obtained from GUI.
		for(int i = 0; i < sysFileCons.size(); i++) {
			Connection sysFileCon = sysFileCons.get(i);
			Connection updatedCon = conList.get(i);
			if(sysFileCon.getSourceFB().equals(updatedCon.getSourceFB()) &&
					sysFileCon.getDestinationFB().equals(updatedCon.getDestinationFB()))	 {
				sysReaderWriter.setConnectionCommentValue(i, updatedCon.getConnectionComment());
			}
		}
		
		sysReaderWriter.saveSysFile();
	}
	
	public static List<DeviceMappings> getDeviceMappings() {
		
		List<DeviceMappings> mappingsList = new ArrayList<DeviceMappings>();
		int numOfMappings = sysReaderWriter.getDeviceMappingsCount();
		
		for(int i = 0; i < numOfMappings; i++) {
			DeviceMappings mapping = new DeviceMappings();
			mapping.setFrom(sysReaderWriter.getDeviceMappingFromAtr(i));
			mapping.setTo(sysReaderWriter.getDeviceMappingToAtr(i));
			mappingsList.add(mapping);
		}
		return mappingsList;
	}
	
	public boolean isValidSecureLink(Connection c) {
		if(Pattern.compile(SECURE_LINK_REGEX).matcher(c.getConnectionComment()).find()) 
			return true;
		else
			return false;
	}

	public String getDestinationFB() {
		return dstFB;
	}

	public void setDestinationeFB(String inFB) {
		this.dstFB = inFB;
	}

	public String getDestinationVariable() {
		return dstVar;
	}

	public void setDestinationVariable(String inVariable) {
		this.dstVar = inVariable;
	}

	public String getDestinationFBDevice() {
		return dstFBDevice;
	}

	public void setDestinationFBDevice(String inFBDevice) {
		this.dstFBDevice = inFBDevice;
	}

	public String getSourceFB() {
		return srcFB;
	}

	public void setSourceFB(String outFB) {
		this.srcFB = outFB;
	}

	public String getSourceVariable() {
		return srcVar;
	}

	public void setSourceVariable(String outVariable) {
		this.srcVar = outVariable;
	}

	public String getSourceFBDevice() {
		return srcFBDevice;
	}

	public void setSourceFBDevice(String outFBDevice) {
		this.srcFBDevice = outFBDevice;
	}

	public String getConnectionComment() { 
		return connectionComment;
	}

	public void setConnectionComment(String connectionComment) {
		this.connectionComment = connectionComment;
	}

}
