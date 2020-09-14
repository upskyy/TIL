package ServerProgram;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class ServerEX implements PublicConstants {

	public static void main(String[] args) {
		Socket socket = null;
		ObjectInputStream objectinputstream = null;
		ObjectOutputStream objectoutputstream = null;
		Scanner sc = new Scanner(System.in);

		BeverageManagement dao = new BeverageManagement();
		
		if (!dao.connect()) {
			return;
		}
		ServerSocket listener;
		try {
			listener = new ServerSocket(SERVER_PORT);
			System.out.println(CONNECTING_MSG);
			socket = listener.accept();
			System.out.println(CONNECTED_MSG);
			OnlyManager manager = new OnlyManager();
			UserInterface ui = new UserInterface();
			Beverage bev = new Beverage();
			
			System.out.println(TITLE);
			while (true) {
				objectoutputstream = new ObjectOutputStream(socket.getOutputStream());
				objectinputstream = new ObjectInputStream(socket.getInputStream());
				ServerManagement server = new ServerManagement(objectinputstream, objectoutputstream, dao);

				objectoutputstream.writeObject(ui);
				objectoutputstream.flush();
				ui = (UserInterface) objectinputstream.readObject();
				
				
				if (ui.getMenu() == ORDER_LIST) {
					server.orderList();
				}
				if (ui.getMenu() == NEW_ORDER) {
					server.newOrder();
				}
				if (ui.getMenu() == DELETE_ORDER) {
					server.deleteOrder();
				}
				if (ui.getMenu() == ONLY_MANAGER) {
					server.manager();
				}
				if (ui.getMenu() == EXIT) {
					server.exit();
					break;
				}
			}

			objectinputstream.close();
			objectoutputstream.close();
			socket.close();
			listener.close();
			sc.close();
		} catch (IOException | ClassNotFoundException e) {
			e.printStackTrace();
		}

	}
}
