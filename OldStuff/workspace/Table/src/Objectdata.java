import java.util.ArrayList;
import java.util.Scanner;


public class Objectdata {
	Object[][] data;
	CarData clist;
	Objectdata(){
		
			clist= new CarData(10,"potato","potato","potato","p0t4t0",23567);
		
		
			data[0][0]=clist.idvehicle;
			data[0][1]=clist.make;
			data[0][2]=clist.model;
			data[0][3]=clist.color;
			data[0][4]=clist.licensePlate;
			data[0][5]=clist.mileage;
	}
	Object[][] port(Object[][] data1){
		for(int i=0;i<6;i++)
			data1[0][i]=data[0][i];
		return data1;
		

	}
}
