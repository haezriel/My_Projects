
public class Test1A {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Rect r=new Rect(5);
		Rect r2=new Rect(10,11);
		System.out.println(r.area() +" " +r2.area());
		r.setDims(1, 2);
		System.out.println(r.area());
	}

}

class Rect{
	private int height;
	private int width;
	
	Rect(int h,int w)
	{
		height=h;
		width=w;
	}
	Rect(int side){
		height=side;
		width=side;
	}
	int area()
	{
		return(height*width);
	}
	static double inchToCm(int v){
		return(v*2.54);
	}
	void setDims(int h,int w)
	{
		height=h;
		width=w;
	}
}