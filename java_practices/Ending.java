//Songjun Na
//Ending.java

//Dramatic Ending to a Dramatic End
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class Ending extends JPanel{
	private static CardLayout ca = new CardLayout();
	private static JPanel cpa = new JPanel(ca);

	//class header
	int fatepoints;
	public Ending(){//constructor
		setLayout(new BorderLayout());
		cpa.setLayout(ca);
		Ne p = new Ne();
		Ned b = new Ned();
		Nedv s = new Nedv();
		cpa.add(p, "1");
		cpa.add(b, "2");
		cpa.add(s, "3");
		add(cpa,BorderLayout.EAST);
	}
	
class Ne extends JPanel implements ActionListener{//first card, contains next button
	JButton n;//declare JButton
	int constant;
	public Ne(){//constuctor
		
		JButton n = new JButton("next");//construct the button
		n.addActionListener(this);//addActionListener
		add(n);//add button
		
	}
	
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == n)
			ca.show(cpa, "2");
		else 
		constant= 1;
	}
	
}

class Ned extends JPanel implements ActionListener{
	JButton o;
	JButton n;
	int value;
	public Ned(){
		
		JButton o = new JButton("why?");
		o.addActionListener(this);
		add(o);
		JButton n = new JButton("HOHO");//construct the button
		n.addActionListener(this);//addActionListener
		add(n);//add button
		
	}
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == o)
			value = 1;
		else 
		value = 1;
		
		if(e.getSource() == n)
			ca.show(cpa, "3");
	}
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		setBackground(Color. YELLOW);
		
		Font a = new Font("Serif",Font.BOLD,40); 
		setFont(a);
		if(value == 1)
			g.drawString("My life is getting worse and worse...why even bother...I hope someone understands", 500,500);
			
		else
			g.drawString("eh", 1,1);
			
		}
}
		
class Nedv extends JPanel{
	String plan = " ";
	JTextArea i;
	
	public Nedv(){
	String plan = "From the studies, suicides are 2nd most deaths out of teenage deaths. our lives matter. we only get one life. What good will it do seeing someone suffer??? Please. Stop.";
	i = new JTextArea(plan, 10, 20);
		i.setLineWrap(true);
		i.setWrapStyleWord(true);
		i.setEnabled(false);
		add(i);
	}
}
}