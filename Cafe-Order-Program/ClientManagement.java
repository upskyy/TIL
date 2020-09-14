package ServerProgram;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Scanner;

public class ClientManagement implements PublicConstants {
	ObjectInputStream objectinputstream = null;
	ObjectOutputStream objectoutputstream = null;
	Scanner sc = null;
	Beverage bev = new Beverage();
	OnlyManager manager = new OnlyManager();

	ClientManagement(ObjectInputStream objectinputstream, ObjectOutputStream objectoutputstream) {
		this.objectinputstream = objectinputstream;
		this.objectoutputstream = objectoutputstream;
		this.sc = new Scanner(System.in);
	}

	public void printList() {
		String[] msg;
		try {
			msg = (String[]) objectinputstream.readObject();
			for (String order : msg) {
				if (order != null) {
					System.out.println(order);
				}
			}
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}
	}

	public void newOrder() {
		try {
			bev = (Beverage) objectinputstream.readObject();
			System.out.println(bev.getOrderName());
			bev.setBerverageName(sc.next());
			System.out.println(bev.getOrderTemperature());
			bev.setTemperature(sc.next());
			System.out.println(bev.getOrderNum());
			bev.setNum(sc.nextInt());
			objectoutputstream.writeObject(bev);
			String message;
			message = (String) objectinputstream.readObject();
			System.out.println(message);
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}

	}

	public void deleteOrder() {
		System.out.println("INPUT >>");
		bev.setDeleteName(sc.next());
		try {
			objectoutputstream.writeObject(bev);
			objectoutputstream.flush();
			String message = (String) objectinputstream.readObject();
			System.out.println(message);
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

	}

	public void manager() {
		try {
			manager = (OnlyManager) objectinputstream.readObject();
			System.out.print(ADMIN_LOGIN_ID_MSG);
			manager.setAdminId(sc.next());
			System.out.print(ADMIN_LOGIN_PASSWD_MSG);
			manager.setPasswd(sc.next());
			objectoutputstream.writeObject(manager);
			objectoutputstream.flush();
			manager = (OnlyManager) objectinputstream.readObject();
			System.out.println(manager.getMsg());
			if (manager.getMsg().equals(ONLY_MANAGER_UI_MSG)) {
				manager.setNum(sc.nextInt());
			}
			objectoutputstream.writeObject(manager);
			objectoutputstream.flush();
			if (manager.getNum() == NEW_MENU_ADD) {
				newMenuAdd();
			}
			if (manager.getNum() == DELETE_MENU) {
				deleteMenu();
			}
			if (manager.getNum() == ALL_DELETE_ORDER) {
				allDeleteOrder();
			}
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}

	}

	private void newMenuAdd() {
		try {
			bev = (Beverage) objectinputstream.readObject();
			System.out.print(MENU_REGISTER_NAME);
			bev.setBerverageName(sc.next());
			System.out.print(MENU_REGISTER_TEMPERATURE);
			bev.setTemperature(sc.next());
			System.out.print(MENU_REGISTER_RECIPE1);
			bev.setRecipe1(sc.next());
			System.out.print(MENU_REGISTER_RECIPE2);
			bev.setRecipe2(sc.next());
			objectoutputstream.writeObject(bev);
			objectoutputstream.flush();
			String message = (String) objectinputstream.readObject();
			System.out.println(message);
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}

	}

	private void deleteMenu() {
		String message;
		try {
			message = (String) objectinputstream.readObject();
			System.out.println(message);
			bev.setDeleteName(sc.next());
			objectoutputstream.writeObject(bev);
			objectoutputstream.flush();
			message = (String) objectinputstream.readObject();
			System.out.println(message);
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}

	}

	private void allDeleteOrder() {
		String message;
		try {
			message = (String) objectinputstream.readObject();
			System.out.println(message);
			message = sc.next();
			objectoutputstream.writeObject(message);
			objectoutputstream.flush();
			message = (String) objectinputstream.readObject();
			System.out.println(message);
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}

	}

	public void exit() {
		String end;
		try {
			end = (String) objectinputstream.readObject();
			System.out.println(end);
		} catch (ClassNotFoundException | IOException e) {
			e.printStackTrace();
		}
	}
}
