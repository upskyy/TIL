package ServerProgram;

public interface PublicConstants {
	public final static int SERVER_PORT = 9999;
	public final static String CONNECTING_MSG = "연결을 기다리고 있습니다.....";
	public final static String CONNECTED_MSG = "연결되었습니다.";
	public static final String[] MENUS = { "## 0. 주문 내용 출력\n", "## 1. 주문 하기\n", "## 2. 주문 내용 삭제\n",
			"## 3. 관리자 전용 프로그램\n", "## 4. 프로그램 종료\n", ">> Input : " };
	public final static String PROGRAM_END_MSG = "프로그램을 종료합니다.";
	public static final int MENU_NUM = 6;
	public static final int ORDER_LIST = 0;
	public static final int NEW_ORDER = 1;
	public static final int NEW_MENU_ADD = 1;
	public static final int DELETE_ORDER = 2;
	public static final int DELETE_MENU = 2;
	public static final int ALL_DELETE_ORDER = 3;
	public static final int ONLY_MANAGER = 3;
	public static final int EXIT = 4;
	public static final String TITLE = "\n\t### CafeOrder Management Program v1.1 ###\n";
	public static final String INT_MISMATCH_EXCEPT_MSG = "잘못입력했습니다!! 정수로 다시 입력해주세요.";
	public static final String FATAL_ELSE_MSG = "발생하면 안 되는 else가 발생했습니다!!";
	public static final String NO_EXIST_BEVERAGE_MSG = "주문하신 메뉴에 없습니다!!";
	public static final String ADMIN_LOGIN_ID_MSG = "관리자 권한이 필요합니다.\n>> ADMIN ID : ";
	public static final String ADMIN_LOGIN_PASSWD_MSG = ">> ADMIN PASSWORD : ";
	public static final String ADMIN_LOGIN_FAIL_MSG = "관리자 권한 접근에 실패하셨습니다.";
	public static final String DB_NOT_CONNECT = "데이터베이스와 연결이 되지 않았습니다\n프로그램이 종료됩니다.";
	public static final String DB_CONNECT = "데이터베이스와 연결 되었습니다!!";
	public static final String TAP = "\t";
	public static final String SQL_COMMA = "','";
	public static final String SQL_INT_COMMA = ",";
	public static final String SQL_OPEN = "('";
	public static final String SQL_INT_COM = "',";
	public static final String SQL_INT_CLOSE = ")";
	public static final String SQL_CLOSE = "')";
	public static final String NOT_DELETE_ALL_ORDER_MSG = "주문 내역이 모두 삭제 되지 않았습니다.";
	public static final String NOT_DELETE_ALL_ORDER_MSG2 = "정확히 입력 되지 않았습니다!!";
	public static final String DELETE_ALL_ORDER_MSG = "전체 주문 내역을 삭제하시겠습니까?(Y,N)\nInput>> ";
	public static final String DELETE_ALL_ORDER_CONFIRM_MSG = "전체 주문 내역을 삭제했습니다.";
	public static final String ONLY_MANAGER_UI_MSG = "1.신 메뉴 추가\n2.메뉴 삭제\n3.주문 내역 전체 삭제\nInput >> ";
	public static final String MENU_REGISTER_NAME = "메뉴 이름?\n";
	public static final String MENU_REGISTER_TEMPERATURE = "온도(HOT,ICE)?\n";
	public static final String MENU_REGISTER_RECIPE1 = "레시피1(ex.차가운물200ML)?\n";
	public static final String MENU_REGISTER_RECIPE2 = "레시피2(ex.자몽1)?\n";
	public static final String MENU_DELETE_MSG = "어떤 메뉴를 삭제하시겠습니까?(ex.아메리카노_HOT)";
	public static final String MENU_DELETE_CONFIRM_MSG = "메뉴를 삭제했습니다.";
	public static final String DB_LOGIN_ID_MSG = "ORACLE ID : ";
	public static final String DB_LOGIN_PASSWD_MSG = "ORACLE PASSWD : ";

}
