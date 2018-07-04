double **createMatrix(int N){
	double **A = (double **) malloc(N*sizeof(double*));
    for (int i=0;i<N;i++)
        A[i]=(double *) calloc(N,sizeof(double));
    for(int i=0;i<N;i++)
        A[i][i]=1.0;
    return A;
}
void destroyMatrix(int N, double **A){
for (int i=N-1;i>=0;i--)
    free(A[i]);
free(A);
}

double **cloneMatrix(int N, double **A){
double **B = createMatrix(N);
for(int i=0;i<N;i++)
    for(int j = 0;j<N;j++)
        B[i][j]=A[i][j];
return B;

}
void multMatrixVector(int N, double **A, double x[],double Ax[]){
//STUFF
}

void gauss(int N, double **A, double b[], double x[]){
for (int i=0;i<N;i++){
	for(intj=i+1;j<N;j++){
		const double s=-A[j][i]/A[i][i];
		for(int k=i+1;k<N;k++)
			A[j][k]+= s*A[i][k];
		b[j]+=s*b[i];
		}
	}
	
x[N-1]=b[N-1]/A[N-1][N-1];
	for(int i=N-2;i>=0;i--){
		double sum=0.0;
		for(int j=i+1;j<N;j++)
			sum+=A[i][j]*x[j];
		x[i]=(b[i]-sum)/A[i][i];
	}
}

int main(){
double **A=createMatrix(N);
const int N=5;
for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
        A[i][j]=10*drand48()-5;
double b[N];
for(int i=0;i<N;i++)
    b[i]=10*drand48()-5;
double x[N];
gauss(N,A,b,x);
return 0;
}
