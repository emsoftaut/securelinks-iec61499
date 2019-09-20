package slib;

import org.w3c.dom.NodeList;

import securelinks.Connection;
import securelinks.SysFileOperator;

public class Compiler {
	
	private final int PARAM_START_INDEX = 4;
	
	private Connection connection;
	
	private String requirement; //will  be used future versions
	private String fbnName;
	private String params;
	
	
	public Compiler(Connection con) {
		connection = con;
		
		splitSecureLinkAnnotation(connection.getConnectionComment());
	}
	
	private void splitSecureLinkAnnotation(String conComment) {
		if(!conComment.isEmpty()) {
			String sansWhiteSpaces = conComment.replaceAll("\\s+",""); // remove white spaces
			String justThecommaSperatedString = sansWhiteSpaces.substring(PARAM_START_INDEX, sansWhiteSpaces.length() - 1);
			this.requirement = justThecommaSperatedString.split(",")[0];
			this.fbnName = justThecommaSperatedString.split(",")[1];
			String [] a = justThecommaSperatedString.split(",", 3);
			System.out.println(a);
		}
	}
	
	public void compile() throws Exception {
		
		//line 3 - We already have connections that are mapped on different devices.
		//line 4 - Retrieve sl.sm from SLib
		SlibFBNetwork sfbn = new SlibFBNetwork();
		sfbn.instantiateFBN("SHA1", "abc, cde"); 
		
		SysFileOperator sysFileOp = open4DIACSysFile();
		
		String conSrc = connection.getSourceFB() + "." + connection.getSourceVariable();
		String conDst = connection.getDestinationFB() + "." + connection.getDestinationVariable();
		
		//line 6: Remove sl from fbn_out
		sysFileOp.removeConnection(conSrc, conDst);
		
		//line 8 and 13
		if(!connection.getSourceFB().isEmpty() && !connection.getDestinationFB().isEmpty()) {
			//map sfbn to left (source) device
			addMappingforLeftDevice(sysFileOp, sfbn);
			
			//map sfbn to right (destination) device
			addMappingforRightDevice(sysFileOp, sfbn);
		}
		
		// line 9: connect sl.in to fbns.S.cin.in
		ConnectIn(sysFileOp, sfbn);
		
		//line 14: connect fbns.S.cout.out to sl.out
		ConnectOut(sysFileOp, sfbn); 
		
		//line 18: Add fbn_s to fbn_out
		addSlibFBNToAppFBN(sysFileOp, sfbn);
		
		//line 17: fbns.S.params = sl.pv
		//We defer the assignment of parameters due to implementation reasons. It does not affect the compilation logic. 
		assignParameters(sysFileOp, sfbn);
		
		sysFileOp.saveSysFile();

	}
	
	private void assignParameters(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		for(int i = 0; i < sfbn.getParamsCount(); i++) {
			FbnParameter p = sfbn.getParameter(i);
			String devMap = sfbn.getDeviveFromFB(p.getFbName());
			String devName = null;
			
			if(devMap.equals(SlibFBNetwork.TAG_DEVICE_LEFT))
				devName = connection.getSourceFBDevice();
			else if(devMap.equals(SlibFBNetwork.TAG_DEVICE_RIGHT))
				devName = connection.getDestinationFBDevice();
			
			sysFileOp.addFBParameter(devName, p.getFbName(), p.getParamName(), p.getParamVal());
		}
	}
	
	private void ConnectIn(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		String devName = connection.getSourceFBDevice();
		String src = connection.getSourceFB() + "." + connection.getSourceVariable();
		String dst = sfbn.getInFBName() + "."+ sfbn.getInVariable();
			
		sysFileOp.addMappedConnection(devName, src, dst);
	}
	
	private void ConnectOut(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		String devName = connection.getDestinationFBDevice();
		String dst = connection.getDestinationFB() + "." + connection.getDestinationVariable();
		String src = sfbn.getOutFBName() + "."+ sfbn.getOutVariable();
			
		sysFileOp.addMappedConnection(devName, src, dst);
	}
	
	private void addSlibFBNToAppFBN(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		NodeList nlistFBs = sfbn.getFBs();
		NodeList nlistEventCons = sfbn.getEventConnections();
		NodeList nlistDataCons = sfbn.getDataConnections();

		sysFileOp.addFBsfromSlibFBN(nlistFBs);
		sysFileOp.addEventConnectionsToSelectedApp(nlistEventCons);
		sysFileOp.addDataConnectionsToSelectedApp(nlistDataCons);
	}
	
	private void addMappingforLeftDevice(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		String devName = connection.getSourceFBDevice();
		
		for(String fbName : sfbn.getLeftDeviceFbNameSet())
			sysFileOp.insertMapping(devName, fbName); 
		
		NodeList list = sfbn.getLeftDeviceFBs();
		sysFileOp.addSlibFBsToDevice(list, devName);
		
		list = sfbn.getLeftDeviceEventConnections();
		sysFileOp.addSlibEventConnectionsToDevice(list, devName);
		
		list = sfbn.getLeftDeviceDataConnections();
		sysFileOp.addSlibDataConnectionsToDevice(list, devName);
	}
	
	private void addMappingforRightDevice(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		String devName = connection.getDestinationFBDevice();
		
		for(String fbName : sfbn.getRightDeviceFbNameSet())
			sysFileOp.insertMapping(devName, fbName); 
		
		NodeList list = sfbn.getRightDeviceFBs();
		sysFileOp.addSlibFBsToDevice(list, devName);
		
		list = sfbn.getRightDeviceEventConnections();
		sysFileOp.addSlibEventConnectionsToDevice(list, devName);
		
		list = sfbn.getRightDeviceDataConnections();
		sysFileOp.addSlibDataConnectionsToDevice(list, devName);
	}
	
	private SysFileOperator open4DIACSysFile() {
		String sysFileAbsolutePath = "C:\\Users\\atanveer\\OneDrive - AUT University\\1. D drive\\Awais\\Software Setups\\4diac-ide-incubation_1.10.3-win32.win32.x86_64\\4diac-ide\\workspace\\test\\test.sys";
		//String sysFileAbsolutePath = "C:\\Users\\Awais\\OneDrive - AUT University\\1. D drive\\Awais\\Software Setups\\4diac-ide-incubation_1.10.3-win32.win32.x86_64\\4diac-ide\\workspace\\test\\test.sys";
		String selectedApp = "testApp";
		Connection.loadSysFile(sysFileAbsolutePath, selectedApp);
		return Connection.getSysFileReader();
	}
}
