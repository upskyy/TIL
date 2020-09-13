package ServerProgram;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class ClientEx extends Thread {

	public static void main(String[] args) throws UnknownHostException, IOException {
		ServerSocket listener = null;
		Socket socket = null;

		socket = new Socket("localhost",9999);

		ClientThread1 client1 = new ClientThread1(socket);
		ClientThread2 client2 = new ClientThread2(socket);

		client1.start();
		client2.start();
		try {
			client2.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}finally {
			socket.close();
		}
	}

}
