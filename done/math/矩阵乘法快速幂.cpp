/*
	MATN为矩阵大小
	MOD为模数
	调用pamt(a,k)返回a^k
*/
struct mat{
	int c[MATN][MATN];
	mat(){SET(c,0);}
};
mat cheng(const mat &a, const mat &b){
	mat w = mat();
	rep(i,0,MATN-1)rep(j,0,MATN-1)rep(k,0,MATN-1){
		w.c[i][j] += (ll)a.c[i][k] * b.c[k][j] % MOD;
		if(w.c[i][j]>=MOD)w.c[i][j]-=MOD;
	}
	return w;
}
mat pmat(mat a, ll k){
	mat i = mat();
	rep(j,0,MATN-1)
		i.c[j][j] = 1;
	if(k<0)return i;
	while(k){
		if(k&1)
			i=cheng(i,a);
		a=cheng(a,a);
		k>>=1;
	}
	return i;
}