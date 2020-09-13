package ServerProgram;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.Scanner;

public class ServerThread2 extends Thread {
	Socket socket = null;
	BufferedReader in = null;
	BufferedWriter out = null;
	Scanner sc = new Scanner(System.in);

	ServerThread2(Socket socket) {
		this.socket = socket;
	}

	public void run() {
		try {
			out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
			while (true) {
				System.out.println("º¸³»±â >>");

				String outputMessage = sc.nextLine();
				out.write(outputMessage + "\n");
				out.flush();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
