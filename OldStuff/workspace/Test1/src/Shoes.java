

public class Shoes {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Complex x=new Complex(2,3);
		x.print();
		System.out.println("Magnitude of x = " +x.mag());
	}
}
class Complex{
	double real, imag;
	
	Complex(double a,double b){
		real=a;
		imag=b;
	}
	double mag(){
		return(Math.sqrt(real*real+imag*imag));
	}
	void print(){
		System.out.println(real + "+" + imag + "i");
	
	}
}
