package ServerProgram;

import java.io.Serializable;

public class OnlyManager implements PublicConstants, Serializable {
	private static final long serialVersionUID = 1L;
	String adminId;
	String passwd;
	String msg;
	int num = -1;

	public String getMsg() {
		return msg;
	}

	public int getNum() {
		return num;
	}

	public void setMsg(String msg) {
		this.msg = msg;
	}

	public void setNum(int num) {
		this.num = num;
	}

	public String getAdminId() {
		return adminId;
	}

	public String getPasswd() {
		return passwd;
	}

	public void setAdminId(String adminId) {
		this.adminId = adminId;
	}

	public void setPasswd(String passwd) {
		this.passwd = passwd;
	}
}
