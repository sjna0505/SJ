//Songjun Na
//Phase3.java

//Another situation following Phase2.java
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class Phase3 extends JPanel implements ActionListener, ChangeListener{

	public void paintComponent(Graphics g){//paintComponent method
//get image
//draw image
Font a = new Font("Times New Roman",Font.BOLD,50);
setFont(a);
		g.drawString("silence means acceptance", 600 ,600);//write hint which states "silence means acceptance" in the bottom
		g.drawString("You have" + fatepoints + "fatepoints", 1000,100);
		
		
		
		
}

class Button extends JPanel implements ActionListener{//class JButtonPanel implements ActionListener 
	JButton next;//declare button next
	JButton restart;//declare button restart

	public Button(){//constructor method

next = new JButton("next");//constructs the buttons
	next.addActionListener(this);
	
	restart= new JButton("restart");
	restart.addActionListener(this);
	
	
			add(next);
			add(restart);	//add them
	}

public void actionPerformed(ActionEvent e){//actionPerformed method
	if(e.getSource() == next)//if e.getSource() of next
		ca.next(this);//then call the next panel(card) in order

	else if(e.getSource() == restart)//if e.getSource() of restart
	//then goes back to the panel StartGame
}
}

class Slider extends JPanel implements ChangeListener{
	
	JSlider s;
	int value;
	boolean no;
	boolean yes;
	JTextArea k;
	public Slider(){
		
		JTextArea k = new JTextArea("Your morale is pretty low...Will you get help??", 20,20);
		
		Jslider s = new JSlider(VERTICAL,0,1,0);
		s.addChangeListener(this);
		
		add(s);
		
	if(no)
		fatepoints = 0;
		
		else if(yes)
		fatepoints = 0;
		
	}
	
public void actionPerformed(ChangeEvent e){
	if(e.getValue()== 0)
		no= true
		
	else if(e.getValue() == 1)
		yes = true
	
}


}

}

