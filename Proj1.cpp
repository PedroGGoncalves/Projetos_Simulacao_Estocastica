#include <stdio.h>
#include <math.h>
int main()
{
	double xn,x,mod,resto,TEC[100],TS[100],vetTEC[100],vetTS[100];
	int cont;
	//LN3 - TS
	x=44; //semente
	mod=pow(2,31)-1; //mod(2^31 - 1)
	xn=(16807*x);	//16807*x(n-1)
	resto= fmod(xn,mod); //xn mod(2^31 - 1)

	do{

		x=resto;	//novo x
		xn=(16807*x); //16807*x(n-1)
		//printf("3ln:%10.0f\n",-3*log(x/mod));
		printf("3 ln x/mod %10.2f\n",x/mod);
		resto= (fmod(xn,mod)); //xn mod(2^31 - 1)
		TS[cont]=-3*log(x/mod);
		vetTS[cont]=x/mod;
		cont++;
	}while(cont<100);
	//LN2 - TEC
	xn=0;x=0;mod=0; cont=0;resto=0;
	x=10; //semente
	mod=pow(2,31)-1; //mod(2^31 - 1)
	xn=(16807*x);	//16807*x(n-1)
	resto= fmod(xn,mod); //xn mod(2^31 - 1)

	do{
		
		x=resto;	//novo x
		xn=(16807*x); //16807*x(n-1)
	//	printf("2ln:%10.0f\n",-2*log(x/mod));
		printf("2 ln x/mod:%10.2f\n",x/mod);
		resto= (fmod(xn,mod)); //xn mod(2^31 - 1)
		TEC[cont]=-2*log(x/mod);
		vetTEC[cont]=x/mod;
		cont++;
	}while(cont<100);
	//////
	float /*TEC[5]={2,5,1,2,12},TS[5]={3,4,6,3,2}*/t_chegada=0,t_inicio=0,t_fim=0,
	t_fila=0,t_sistema=0,t_livre=0,somatempos_espera=0,somatempos_servico=0,
	somatempo_sistema=0,somatempo_caixa=0;
	int tempos_espera[100],tempos_servico[100],tempo_sistema[100];
	
	for(int i=0;i<100;i++)
	{
		printf("|%2.f|%2.f|",TEC[i],TS[i]);
		t_chegada=TEC[i]+t_chegada;
		
		if(t_fim>t_chegada)
		{
			t_inicio=t_fim;
			t_fila=t_fim-t_chegada;
			t_livre=0;
			t_sistema=TS[i]+t_fila;
		}
		else
		{
			t_inicio=t_chegada;
			t_fila=0;
			t_livre=t_inicio-t_fim;
			t_sistema=TS[i]+t_fila;
		}
		t_fim=t_inicio+TS[i];
		tempos_servico[i]=t_fim-t_inicio;
		tempo_sistema[i]=t_sistema;
		tempos_espera[i]=t_fila;
		somatempos_servico=somatempos_servico+t_fim-t_inicio;
		somatempo_sistema=somatempo_sistema+t_sistema;
		somatempo_caixa=somatempo_caixa+t_livre;
		somatempos_espera=somatempos_espera+t_fila;
		printf("%2.f|%2.f|%2.f|%f|%2.f|%f|\n",t_chegada,t_inicio,t_fim,t_fila,t_sistema,t_livre);
		printf("-------------------------\n");
	}
	
	printf("Tempo medio de espera na fila:%.2f\n",(float)somatempos_espera/100);
	printf("Tempo medio de servico:%.2f\n",(float)somatempos_servico/100);
	printf("Tempo medio despendido no sistema:%.2f\n",(float)somatempo_sistema/100);
	printf("Probabilidade de encontrar o caixa livre:%.2f\n",(float)somatempo_caixa/t_fim);
	
	int desvio=0,desvio2=0,desvio3=0;
	for(cont=0;cont<100;cont++)
		{
			desvio=desvio+pow((tempos_espera[cont]-somatempos_espera/100),2);
			desvio2=desvio2+pow((tempos_servico[cont]-somatempos_servico/100),2);
			desvio2=desvio3+pow((tempo_sistema[cont]-somatempo_sistema/100),2);
		}
		desvio=desvio/100;
		desvio=sqrt(desvio);
		desvio2=desvio2/100;
		desvio2=sqrt(desvio2);
		desvio3=desvio3/100;
		desvio3=sqrt(desvio3);
	//	printf("%d %d %d\n",desvio,desvio2,desvio3);
		
	printf("Intervalo de confianca das medias do tempo na fila(+1.96):%f \n",(somatempos_espera/100)+1.96*(desvio/sqrt(100)));
	printf("Intervalo de confianca das medias do tempo de servico(+1.96):%f \n",(somatempos_servico/100)+1.96*(desvio2/sqrt(100)));
	printf("Intervalo de confianca das medias do tempo no sistema(+1.96):%f \n",(somatempo_sistema/100)+1.96*(desvio3/sqrt(100)));
	printf("Intervalo de confianca das medias do tempo na fila(-1.96):%f \n",(somatempos_espera/100)-1.96*(desvio/sqrt(100)));
	printf("Intervalo de confianca das medias do tempo de servico(-1.96):%f \n",(somatempos_servico/100)-1.96*(desvio2/sqrt(100)));
	printf("Intervalo de confianca das medias do tempo no sistema (-1.96):%f \n",(somatempo_sistema/100)-1.96*(desvio3/sqrt(100)));
	
	//media
	double media=0;
	for(cont=0;cont<100;cont++)
		media=media+vetTS[cont];
	media=media/100;
	printf("Media:%f\n",media);
	
	//desvio padrao
	double desvioP;
	for(cont=0;cont<100;cont++)
		desvioP=desvioP+pow((vetTS[cont]-media),2);
	desvioP=desvioP/100;
	desvioP=sqrt(desvioP);
	printf("Desvio Padrao:%f\n",desvioP);
	
	////////
	printf("--------------Uniforme\n");
	int b=1, a=0;
	double d[100];
	for (int i=0;i<100;i++)
		{
			d[i] = (b-a)*vetTS[i]+a;
		//	printf("%.10f\n",d[i]);
			double fUniforme=d[i]-a/(b-a);
		//	printf("%.10f\n",fUniforme);
		}
	printf("--------------Erlang\n");
	int  alfa=1,k=2;
	for (int i=0;i<100;i++)
		{
			for (int j=0; j<k;j++)
			{
				d[i]=d[i]+(log(vetTS[i]))/alfa;
			}
			d[i]=d[i]*(-1);
			double fE;
		//	fE= alfa*pow(0,5,alfa*(-1)*d[i])*pow(alfa*x,k-1)/1; //fatorial de k-1;
		//	printf("%.10f\n",d[i]);	
		}	
	printf("--------------Normal\n");
	double xNormal[100],pi=3.14,fNormal[100];
	int dteste;
	for(int i=0;i<100;i++)
	{
		xNormal[i]=(sqrt(-2*log(vetTEC[i])))*(cos(2*pi*vetTEC[i]));
		//printf("%f\n",xNormal[i]);
		dteste=1;
		fNormal[i]=(1/dteste*sqrt(2*pi))*pow(0.5,(pow(xNormal[i],2))/2*pow(dteste,2));
	//	printf("%f\n",fNormal[i]);
	}
}
