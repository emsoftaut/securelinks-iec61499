package securelinks;

public class Connection {
	private String dstFB;

	private String dstVar;
	private String dstFBDevice;
	
	private String srcFB;
	private String srcVar;
	private String srcFBDevice;
	
	private String connectionComment; // We are using comments attribute for SL annotations
	
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
