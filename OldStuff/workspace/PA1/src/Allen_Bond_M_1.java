//Main Program Block, Official comments in Rat.java

import java.util.Scanner;


public class Allen_Bond_M_1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

//This is just a scanner program I put together to take in rational number sets,
//and then perform all the functions. I used it for debugging, but it's self explanatory
//if you'd like to use it.
		Rat a=new Rat(1,2); // a=1/2
		Rat b=new Rat(4); // b=4
		Rat c,d,e;
		c=a.add(b); c.print(); // should print 9/2
		c=a.sub(b); c.print(); // should print -7/2
		c=b.sub(a); c.print(); // should print 7/2
		c=a.times(b); c.print(); // should print 2
		c.times(c).print(); // should print 4
		d=new Rat(3); // d=3
		e=new Rat(4); // e=4
		c=d.div(e); c.print(); // c=3/4; should print 3/4
		a=e.div(d); a.print(); // a=4/3; should print 4/3
		c=a.times(b); // c=16/3
		System.out.println(c.num() + " " + c.denom()); // should print “16 3”
		c.print(); // should print 16/3
		System.out.println("1/3=" + new Rat(1,3).toDouble()); // should print 1/3=0.333333…
		a=new Rat(1,0);a.print(); // should print 1/0
		a=new Rat(1,2); // a=1/2
		b=new Rat(1,2); // b=1/2
		c=a.sub(b); // c=0
		a=a.div(c); // a=1/0
		System.out.println(a.toDouble()); // should print infinity
		a=c.div(c); // a=0/0
		System.out.println(a.toDouble()); // should print NaN
		System.out.println(new Rat(-1,0).toDouble()); // should print -infinity
	
//This is just a scanner program I put together to take in rational number sets,
//and then perform all the functions. I used it for debugging, but it's self explanatory
//if you'd like to use it.		
		System.out.print("Enter your fractions as 'numerator denominator':");
		Scanner s=new Scanner(System.in);
		while(s.hasNextInt()){
			int test1=s.nextInt();
			int test2=s.nextInt();
			Rat test3=new Rat(test1,test2);
			test3.print();
			System.out.println("In decimal form ="+test3.toDouble());
			System.out.print("Now enter a second fraction for arithmetic testing:");
			int test4=s.nextInt();
			int test5=s.nextInt();
			Rat test6=new Rat(test4,test5);
			System.out.print("quotient =");
			Rat test7=test3.div(test6); test7.print();
			System.out.print("sum =");
			test7=test3.add(test6); test7.print();
			System.out.print("product =");
			test7=test3.times(test6); test7.print();
			System.out.print("difference =");
			test7=test3.sub(test6); test7.print();
			System.out.print("Enter your fractions as 'numerator denominator':");
		}
	}
}

