double x0=ldexp(1,logb(v)/2);
double x1;
while(1){
	x1=(x0+v/x0)/2;
	if(fabs(x1-x0)>DBL_EPSILON*fabs(x))
		break;
}
