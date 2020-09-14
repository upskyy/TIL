package ServerProgram;

import java.io.Serializable;

public class Beverage implements Serializable{
	private static final long serialVersionUID = 1L;
	private String orderName = "주문하실 음료를 선택하세요 : ";
	private String orderTemperature = "HOT, ICE ? ";
	private String orderNum = "수량 : ";

	/* Beverage Information */
	private String berverageName;
	private String temperature;
	private int num;
	private String recipe1;
	private String recipe2;
	private String deleteName;
	// getters & setters

	public String getDeleteName() {
		return deleteName;
	}

	public void setDeleteName(String deleteName) {
		this.deleteName = deleteName;
	}

	public String getRecipe1() {
		return recipe1;
	}

	public String getOrderName() {
		return orderName;
	}

	public String getOrderTemperature() {
		return orderTemperature;
	}

	public String getOrderNum() {
		return orderNum;
	}

	public String getBerverageName() {
		return berverageName;
	}

	public void setBerverageName(String berverageName) {
		this.berverageName = berverageName;
	}

	public void setRecipe1(String recipe1) {
		this.recipe1 = recipe1;
	}

	public String getRecipe2() {
		return recipe2;
	}

	public void setRecipe2(String recipe2) {
		this.recipe2 = recipe2;
	}

	public String getTemperature() {
		return temperature;
	}

	public void setTemperature(String temperature) {
		this.temperature = temperature;
	}

	public int getNum() {
		return num;
	}

	public void setNum(int num) {
		this.num = num;
	}

}
