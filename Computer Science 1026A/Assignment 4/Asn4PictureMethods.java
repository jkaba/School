//Add these two methods to the Picture Class for Assignment 4

/** This method will draw a the given text, using the font size specified
    * in a bold font at the yPos given and centered in the image
    * @param text : the text to write
    * @param fontSize : the size of font to use
    * @param yPos : the vertical position of the baseline of the first character
    */
  public void drawCenteredString(String text, int yPos, int fontSize){
    Graphics2D g = (Graphics2D)this.getGraphics();
    
    g.setFont(new Font("Arial",Font.BOLD,fontSize));
    g.setColor(Color.BLACK);
    int stringLen = (int) g.getFontMetrics().getStringBounds(text, g).getWidth();  
    int xPos = this.getWidth()/2 - stringLen/2;  
    
    g.drawString(text, xPos, yPos);
  }
  
  /** This method will draw the given text, using the font size specified
    * in italics in the bottom right corner of the image
    * @param text : the text to write
    * @param fontSize: the size of font to use
    */
  public void drawInfoWatermark(String text, int fontSize){
    
    //Get the graphics object of this image
    Graphics2D g = (Graphics2D)this.getGraphics();
    
    //Set up transparency (alpha channel)
    AlphaComposite alpha = AlphaComposite.getInstance(AlphaComposite.SRC_OVER,0.5f);
    g.setComposite(alpha);
    g.setColor(Color.white);  
    g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);  
    
    //Font setup
    g.setFont(new Font("Arial", Font.ITALIC, fontSize));   
    
    //use a pad at the edge
    final int PAD = 20;
    int stringLen = (int) g.getFontMetrics().getStringBounds(text, g).getWidth();  
    int stringHeight = (int) g.getFontMetrics().getStringBounds(text, g).getHeight();
    //write text onto the image
    g.drawString(text, this.getWidth()-stringLen-PAD, this.getHeight()-stringHeight);  
  }