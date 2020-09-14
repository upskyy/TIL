package ServerProgram;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Scanner;

public class ServerManagement implements PublicConstants {
	BeverageManagement dao;
	ObjectInputStream objectinputstream = null;
	ObjectOutputStream objectoutputstream = null;
	Scanner sc = null;
	OnlyManager manager = new OnlyManager();
	UserInterface ui = new UserInterface();
	Beverage bev = new Beverage();

	ServerManagement(ObjectInputStream objectinputstream, ObjectOutputStream objectoutputstream,BeverageManagement dao) {
		this.objectinputstream = objectinputstream;
		this.objectoutputstream = objectoutputstream;
		this.sc = new Scanner(System.in);
		this.dao = dao;
	}

	public void orderList() {
		try {
			objectoutputstream.writeObject(dao.printOrder());
			objectoutputstream.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void newOrder() {
		try {
			objectoutputstream.writeObject(bev);
			objectoutputstream.flush();
			bev = (Beverage) objectinputstream.readObject();
			objectoutputstream.writeObject(dao.insertDB(bev));
			objectoutputstream.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		
	}
	public void deleteOrder() {
		try {
			objectoutputstream.writeObject(dao.AdminReadMenu());
			objectoutputstream.flush();
			bev = (Beverage) objectinputstream.readObject();
			objectoutputstream.writeObject(dao.deleteOrder(bev.getDeleteName()));
			objectoutputstream.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
	public void manager() {
		try {
			objectoutputstream.writeObject(manager);
			objectoutputstream.flush();
			manager = (OnlyManager) objectinputstream.readObject();
			manager.setMsg(dao.onlyManager(manager.getAdminId(), manager.getPasswd()));
			objectoutputstream.writeObject(manager);
			objectoutputstream.flush();
			manager = (OnlyManager) objectinputstream.readObject();
			if (manager.getNum() == NEW_MENU_ADD) {
				newMenuAdd();
			}
			if (manager.getNum() == DELETE_MENU) {
				deleteMenu();
			}
			if (manager.getNum() == ALL_DELETE_ORDER) {
				allDeleteOrder();
			}
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	private void newMenuAdd() {
		try {
			objectoutputstream.writeObject(bev);
			objectoutputstream.flush();
			bev = (Beverage) objectinputstream.readObject();
			objectoutputstream.writeObject(dao.newMenuRegister(bev));
			objectoutputstream.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		
	}
	
	private void deleteMenu() {
		try {
			objectoutputstream.writeObject(MENU_DELETE_MSG);
			objectoutputstream.flush();
			bev = (Beverage) objectinputstream.readObject();
			objectoutputstream.writeObject(dao.menuDelete(bev.getDeleteName()));
			objectoutputstream.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		
	}
	private void allDeleteOrder() {
		try {
			objectoutputstream.writeObject(DELETE_ALL_ORDER_MSG);
			objectoutputstream.flush();
			String msg = (String) objectinputstream.readObject();
			objectoutputstream.writeObject(dao.deleteAll(msg));
			objectoutputstream.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		
	}
	public void exit() {
		try {
			objectoutputstream.writeObject(PROGRAM_END_MSG);
			objectoutputstream.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
}
