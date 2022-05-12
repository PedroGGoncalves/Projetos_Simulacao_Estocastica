#include <stdio.h>
#include <math.h>

void simulador(int i, float TS, float TEC, float *tempo_chegada, float *tempo_inicio,float *tempo_fim, float *tempo_fila,float *tempo_sistema,float *tempo_livre, float *somatempos_servico, float *somatempo_sistema, float *somatempo_caixa,float *somatempos_espera, float *t_fim)
{
	*tempo_chegada=TEC+*tempo_chegada;
		if(*tempo_fim>*tempo_chegada)
		{
			*tempo_inicio=*tempo_fim;
			*tempo_fila=*tempo_fim-*tempo_chegada;
			*tempo_livre=0;
			*tempo_sistema=TS+*tempo_fila;
		}
		else
		{
			*tempo_inicio=*tempo_chegada;
			*tempo_fila=0;
			*tempo_livre=*tempo_inicio-*tempo_fim;
			*tempo_sistema=TS+*tempo_fila;
		}
		*tempo_fim=*tempo_inicio+TS;
		*somatempos_servico=*somatempos_servico+*tempo_fim-*tempo_inicio;
		*somatempo_sistema=*somatempo_sistema+*tempo_sistema;
		*somatempo_caixa=*somatempo_caixa+*tempo_livre;
		*somatempos_espera=*somatempos_espera+*tempo_fila;
		*t_fim=*tempo_fim;
		printf("%2.f|%2.f|%2.f|%.f|%2.f|%.f|\n",*tempo_chegada,*tempo_inicio,*tempo_fim,*tempo_fila,*tempo_sistema,*tempo_livre);
		printf("-------------------------\n");
}

int main()
{
	int num_clientes=100;
	double xn,x,mod,resto,TEC[num_clientes],TS[num_clientes];
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
	//	printf("3 ln x/mod %10.2f\n",x/mod);
		resto= (fmod(xn,mod)); //xn mod(2^31 - 1)
		TS[cont]=-3*log(x/mod);
		cont++;
	}while(cont<num_clientes);
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
	//	printf("2 ln x/mod:%10.2f\n",x/mod);
		resto= (fmod(xn,mod)); //xn mod(2^31 - 1)
		TEC[cont]=-2*log(x/mod);
		cont++;
	}while(cont<num_clientes);

	int N=5;//Numero de caixas funcionando
	float tempo_chegada[N],tempo_inicio[N],tempo_fim[N],tempo_fila[N],tempo_sistema[N],tempo_livre[N],t_fim,somatempos_espera=0,somatempos_servico=0,somatempo_sistema=0,somatempo_caixa=0;;
	
	cont=0;
	for (int i=0;i<N;i++)//zerando variavies
	{
		tempo_chegada[i]=0;
		tempo_inicio[i]=0;
		tempo_fim[i]=0;
		tempo_fila[i]=0;
		tempo_sistema[i]=0;
		tempo_livre[i]=0;
	}
	
	for (int i=0;i<num_clientes;i++)
	{
		if(N==1)
		{
			printf("Fila [0] Cliente %d\n",i);
			printf("|%2.f|%2.f|",TEC[i],TS[i]);
			int num=0;
			simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
		}
		else if(N==2)
		{
			if(tempo_fim[0]<=tempo_fim[1])
			{
				printf("Fila [0] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=0;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else
			{
				printf("Fila [1] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=1;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);	
			}
		}
		else if(N==3)
		{
			if(tempo_fim[0]<=tempo_fim[1] && tempo_fim[0]<=tempo_fim[2])
			{
				printf("Fila [0] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=0;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else if (tempo_fim[1]<=tempo_fim[2])
			{
				printf("Fila [1] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=1;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else
			{
				printf("Fila [2] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=2;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
		}
		else if(N==4)
		{
			if(tempo_fim[0]<=tempo_fim[1] && tempo_fim[0]<=tempo_fim[2]&&tempo_fim[0]<=tempo_fim[3])
			{
				printf("Fila [0] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=0;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else if(tempo_fim[1]<=tempo_fim[2]&&tempo_fim[1]<=tempo_fim[3])
			{
				printf("Fila [1] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=1;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else if(tempo_fim[2]<=tempo_fim[3])
			{
				printf("Fila [2] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=2;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else
			{
				printf("Fila [3] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=3;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
		}
		else if(N==5)
		{
			if(tempo_fim[0]<=tempo_fim[1]&&tempo_fim[0]<=tempo_fim[2]&&tempo_fim[0]<=tempo_fim[3]&&tempo_fim[0]<=tempo_fim[4])
			{
				printf("Fila [0] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=0;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else if(tempo_fim[1]<=tempo_fim[2]&&tempo_fim[1]<=tempo_fim[3]&&tempo_fim[1]<=tempo_fim[4])
			{
				printf("Fila [1] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=1;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else if(tempo_fim[2]<=tempo_fim[3]&&tempo_fim[2]<=tempo_fim[4])
			{
				printf("Fila [2] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=2;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else if(tempo_fim[3]<=tempo_fim[4])
			{
				printf("Fila [3] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=3;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
			else
			{
				printf("Fila [4] Cliente %d\n",i);
				printf("|%2.f|%2.f|",TEC[i],TS[i]);
				int num=4;
				simulador(num,TS[i], TEC[i], &tempo_chegada[num], &tempo_inicio[num],&tempo_fim[num], &tempo_fila[num],&tempo_sistema[num],&tempo_livre[num],&somatempos_servico,&somatempo_sistema,&somatempo_caixa,&somatempos_espera,&t_fim);
			}
		}
	}		
	printf("Tempo medio de espera na fila:%.2f\n",(float)somatempos_espera/num_clientes);
	printf("Tempo medio despendido no sistema:%.2f\n",(float)somatempo_sistema/num_clientes);
}
