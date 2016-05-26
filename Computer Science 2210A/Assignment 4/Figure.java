
public class Figure implements FigureADT {
private int id;
int width;
int height;
int type;
BinarySearchTree tree;
Position offset;

	public Figure (int id, int width, int height, int type, Position pos){
		this.id = id;
		this.width = width;
		this.height = height;
		this.type = type;
		this.offset = pos;
	}
	
	public void setType(int type){
		this.type = type;
	}
	
	public int getWidth(){
		return this.width;
	}
	
	public int getHeight(){
		return this.height;
	}
	
	public int getId(){
		return this.id;
	}
	
	public int getType(){
		return this.type;
	}
	
	public Position getOffset(){
		return this.offset;
	}
	
	public void setOffset(Position value){
		this.offset = value;
	}
	
	public void addPixel(int x, int y, int color) throws BSTException{
		Position pos = new Position(x,y);
		DictEntry addition = new DictEntry(pos, color);
		try{
			this.tree.insert(addition);
		} catch (BSTException e){
			System.out.println(e);
		}
	}
	
	public boolean intersects (Figure fig){
		Position topL = this.offset;
		Position topR = new Position(this.offset.getX() + this.width, this.offset.getY());
		Position botL = new Position(this.offset.getX(), this.offset.getY() + height);
		//Position botR = new Position(this.offset.getX() + this.width, this.offset.getY() + this.height);
		Position figtopL = fig.offset;
		//Position figtopR = new Position(this.offset.getX() + this.width, this.offset.getY());
		Position figbotL = new Position(this.offset.getX(), this.offset.getY() + height);
		Position figbotR = new Position(this.offset.getX() + this.width, this.offset.getY() + this.height);
		if (figtopL.getY() > botL.getY() || figbotL.getY() < topL.getY()){
			return false;
		}
		else if (figtopL.getX() > topR.getX() || figbotR.getX() < topL.getX()){
			return false;
		} else return true;
	}
}
