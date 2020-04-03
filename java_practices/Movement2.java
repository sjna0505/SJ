//Songjun Na
//5/8/15


import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.applet.Applet;
import javax.swing.*;
import java.awt.Graphics;
import javax.swing.Timer;

public class Move extends JPanel implements ActionListener, KeyListener{
	public static CardLayout cards = new CardLayout();
	public static JPanel cpanel = new JPanel(cards);
	Image i;
	Timer s= new Timer(6, this);
	int x = 0;
	int y = 0;
	int w = 0;
	int z = 0;
	int haha = 0;
	
	public Move(){//constructor
		//setSize(800,850);//size
		//setLocation(0,0);
		//Game p = new Game();
		//setVisible(true);
		
		
		
		s.start();
		addKeyListener(this);
		setFocusable(true);
		setFocusTraversalKeysEnabled(false);
	}
/*
	class Game extends JPanel{
	
		public Game(){
		
			setLayout(new BorderLayout());
			cpanel.setLayout(cards);
			Phase2 p2 = new Phase2();
			cpanel.add(p2, "Phase 2");
			add(cpanel,BorderLayout.CENTER);
		}
	}

	
	*/
	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		g.drawRect(x,y,30,50);
		g.drawRect(700, 700, 50, 50);
		
		
		Image m = Toolkit.getDefaultToolkit().getImage("Concrete.jpg");//getting image
		g.drawImage(m,0,0,900,800,this);//middle parameters indicate where it starts
		
		Image j = Toolkit.getDefaultToolkit().getImage("Shmurda.jpg");//getting image
		g.drawImage(j,750,400,60,60,this);//middle parameters indicate where it starts
		
		Image c = Toolkit.getDefaultToolkit().getImage("Home.jpg");//getting image
		g.drawImage(c,700,700,780,780,this);//middle parameters indicate where it starts
		
		Image r = Toolkit.getDefaultToolkit().getImage("711.jpg");//getting image
		g.drawImage(r,0,0,80,80,this);//middle parameters indicate where it starts
		
		Image i = Toolkit.getDefaultToolkit().getImage("Character.jpg");//getting image
		g.drawImage(i,x,y,40,40,this);//middle parameters indicate where it starts
		
		
		g.drawString("HAHA x = " + x + " y = " + y + " w = " + w + " z= "+z + " haha=" +haha,20,20);
		g.setColor(Color. BLUE);
		g.fillOval(400,0, 600, 150);
		Font b = new Font("Times New Roman",Font.BOLD, 35);
		g.setFont(b);
		g.setColor(Color.RED);
		g.drawString("Get to your destinination!!",450,100);
	}
	
	
	public void actionPerformed(ActionEvent e){
		x= x+ w;
		y= y+ z;
		repaint();
		
		
		if( (x>=700 && x<=710)  && (y>=700 && y <=710) ){
			cards.show(cpanel, "Phase 2");
		}

		if( x > 800 || x < 0 ) w = w*(-1);
		if( y > 800 || y < 0 ) z = z*(-1);
		
		
	}

	public void keyPressed(KeyEvent e){
		int key = e.getKeyCode();
		if(key == KeyEvent.VK_UP){
			w=0;
			z=-2;
		}
		if(key == KeyEvent.VK_DOWN){
			w=0;
			z=2;
		}
		if(key == KeyEvent.VK_RIGHT){
			w =2;
			z=0;
		}
		if(key == KeyEvent.VK_LEFT){
			w=-2;
			z=0;
		}
	}
	public void keyTyped(KeyEvent e){}
	public void keyReleased(KeyEvent e){}
}
