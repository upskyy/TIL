package ServerProgram;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client implements PublicConstants {

	public static void main(String[] args) {
		Socket socket = null;
		Scanner sc = new Scanner(System.in);
		ObjectInputStream objectinputstream = null;
		ObjectOutputStream objectoutputstream = null;
		try {
			socket = new Socket("localhost", SERVER_PORT);
			System.out.println(TITLE);

			UserInterface ui = new UserInterface();
			OnlyManager manager = new OnlyManager();
			int menu;
			String msg[] = new String[20];
			Beverage bev = new Beverage();

			while (true) {
				try {
					objectinputstream = new ObjectInputStream(socket.getInputStream());
					objectoutputstream = new ObjectOutputStream(socket.getOutputStream());
					ClientManagement client = new ClientManagement(objectinputstream, objectoutputstream);
					ui = (UserInterface) objectinputstream.readObject();
					ui.printMenu();
					menu = sc.nextInt();
					ui.setMenu(menu);
					objectoutputstream.writeObject(ui);
					objectoutputstream.flush();
					if (menu == ORDER_LIST) {
						client.printList();
					}
					if (menu == NEW_ORDER) {
						client.newOrder();
					}
					if (menu == DELETE_ORDER) {
						client.printList();
						client.deleteOrder();
					}
					if (menu == ONLY_MANAGER) {
						client.manager();
					}
					if (menu == EXIT) {
						client.exit();
						break;
					}
				} catch (ClassNotFoundException e) {
					e.printStackTrace();
				}

			}
			objectinputstream.close();
			objectoutputstream.close();
			socket.close();
			sc.close();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}
