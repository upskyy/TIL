package ServerProgram;

import java.io.Serializable;
import java.net.Socket;

public class UserInterface implements Serializable, PublicConstants {
	private static final long serialVersionUID = 1L;
	int menu = -1;

	public int getMenu() {
		return menu;
	}

	public void setMenu(int menu) {
		this.menu = menu;
	}
	public void printMenu() {
		for(int i=0; i<MENU_NUM;i++) {
			System.out.println(MENUS[i]);
		}
	}
}
