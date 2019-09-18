package slib;


import java.util.List;

import org.eclipse.swt.events.GestureListener;
import org.w3c.dom.NodeList;

import securelinks.Connection;
import securelinks.SysFileOperator;

public class Compiler {
	
	private Connection connection;
	
	public Compiler(Connection con) {
		connection = con;
	}
	public void compile() throws Exception {
		
		//line 3 - We already have connections that are mapped on different devices.
		//line 4 - Retrieve sl:sm from SLib
		SlibFBNetwork sfbn = new SlibFBNetwork();
		sfbn.instantiateFBN("SHA1", "abc, cde"); 
		
		SysFileOperator sysFileOp = open4DIACSysFile();
		
		String conSrc = connection.getSourceFB() + "." + connection.getSourceVariable();
		String conDst = connection.getDestinationFB() + "." + connection.getDestinationVariable();
		
		//line 6: Remove sl from fbn_out
		sysFileOp.removeConnection(conSrc, conDst);
		
		if(!connection.getSourceFB().isEmpty() && !connection.getDestinationFB().isEmpty()) {
			//map sfbn to left (source) device
			addMappingforLeftDevice(sysFileOp, sfbn);
			
			//map sfbn to right (destination) device
			addMappingforRightDevice(sysFileOp, sfbn);
		}
		
		//line 18: Add fbn_s to fbn_out
		addSlibFBNToAppFBN(sysFileOp, sfbn);
		
		sysFileOp.saveSysFile();

	}
	
	private void addSlibFBNToAppFBN(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		NodeList nlistFBs = sfbn.getFBs();
		NodeList nlistEventCons = sfbn.getEventConnections();
		NodeList nlistDataCons = sfbn.getDataConnections();

		sysFileOp.addFBsfromSlibFBN(nlistFBs);
		sysFileOp.addEventConnectionsfromSlibFBN(nlistEventCons);
		sysFileOp.addDataConnectionsfromSlibFBN(nlistDataCons);
	}
	
	private void addMappingforLeftDevice(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		for(String fbName : sfbn.getLeftDeviceFbNameSet())
			sysFileOp.insertMapping(connection.getSourceFBDevice(), fbName); 
		
		NodeList list = sfbn.getLeftDeviceFBs();
		sysFileOp.addSlibFBsToDevice(list, connection.getSourceFBDevice());
		
		list = sfbn.getLeftDeviceEventConnections();
		sysFileOp.addSlibEventConnectionsToDevice(list, connection.getSourceFBDevice());
		
		list = sfbn.getLeftDeviceDataConnections();
		sysFileOp.addSlibDataConnectionsToDevice(list, connection.getSourceFBDevice());
	}
	
	private void addMappingforRightDevice(SysFileOperator sysFileOp, SlibFBNetwork sfbn) {
		for(String fbName : sfbn.getRightDeviceFbNameSet())
			sysFileOp.insertMapping(connection.getDestinationFBDevice(), fbName); 
		
		NodeList list = sfbn.getRightDeviceEventConnections();
		sysFileOp.addSlibEventConnectionsToDevice(list, connection.getDestinationFBDevice());
		
		list = sfbn.getRightDeviceDataConnections();
		sysFileOp.addSlibDataConnectionsToDevice(list, connection.getDestinationFBDevice());
	}
	
	private SysFileOperator open4DIACSysFile() {
		String sysFileAbsolutePath = "C:\\Users\\atanveer\\OneDrive - AUT University\\1. D drive\\Awais\\Software Setups\\4diac-ide-incubation_1.10.3-win32.win32.x86_64\\4diac-ide\\workspace\\test\\test.sys";
		//String sysFileAbsolutePath = "C:\\Users\\Awais\\OneDrive - AUT University\\1. D drive\\Awais\\Software Setups\\4diac-ide-incubation_1.10.3-win32.win32.x86_64\\4diac-ide\\workspace\\test\\test.sys";
		String selectedApp = "testApp";
		Connection.loadSysFile(sysFileAbsolutePath, selectedApp);
		return Connection.getSysFileReader();
	}
}
