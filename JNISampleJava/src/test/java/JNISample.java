package test.java;

// JNIで呼び出される側のjavaクラス
public class JNISample {
	private int ivalue;
	private double dvalue;
	private boolean bool;
	private String message;

	public JNISample() {
		ivalue = 0;
		dvalue = 0.0;
		bool = false;
		message = "";
	}

	public void print() {
		System.out.println("=== This is Java method ===");
	}

	public void printValues() {
		System.out.println("JNISample.ivalue = " + String.valueOf(ivalue));
		System.out.println("JNISample.dvalue = " + String.valueOf(dvalue));
		System.out.println("JNISample.bool = " + String.valueOf(bool));
		System.out.println("JNISample.message = " + message);
	}

	public int getIvalue() {
		return ivalue;
	}

	public void setIvalue(int ivalue) {
		this.ivalue = ivalue;
	}

	public double getDvalue() {
		return dvalue;
	}

	public void setDvalue(double dvalue) {
		this.dvalue = dvalue;
	}

	public boolean isBool() {
		return bool;
	}

	public void setBool(boolean bool) {
		this.bool = bool;
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}
}
