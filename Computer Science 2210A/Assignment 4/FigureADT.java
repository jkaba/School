public interface FigureADT {
    public void setType (int t);
    public int getWidth ();
    public int getHeight();
    public int getType ();
    public int getId();
    public Position getOffset();
    public void setOffset(Position value);
    public void addPixel(int x, int y, int rgb) throws BSTException;
    public boolean intersects(Figure fig);
}
