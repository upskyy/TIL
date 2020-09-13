package ServerProgram;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Scanner;

public class ServerThread1 extends Thread {
	Socket socket = null;
	BufferedReader in = null;
	BufferedWriter out = null;
	Scanner sc = new Scanner(System.in);

	ServerThread1(Socket socket) {
		this.socket = socket;
	}

	public void run() {
		try {
			in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			while (true) {
				String inputMessage = in.readLine();

				if (inputMessage.equalsIgnoreCase("bye")) {
					System.out.println("클라이언트에서 bye로 연결을 종료하였다.");
					break;
				}
				System.out.println("클라이언트 : " + inputMessage);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}
