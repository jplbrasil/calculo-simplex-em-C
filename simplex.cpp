#include <iostream.h> //cout,cin,etc...
#include <iomanip.h> //outras funcoes do cout
#include <conio.h> //getch, clrscr,etc...

 /*
 x[0] - funcao objetivo
 x[1] - restricao 1
 x[2] - restricao 2
 x[3] - restricao 3
 x[4] - funcao objetivo auxiliar

 x[i][0] - Z
 x[i][1] - coeficiente de X1
 x[i][2] - coeficiente de X2
 x[i][3] - coeficiente de X3
 x[i][4] - coeficiente de XF1
 x[i][5] - coeficiente de XF2
 x[i][6] - coeficiente de XF3
 x[i][7] - coeficiente de XA1
 x[i][8] - coeficiente de XA2
 x[i][9] - coeficiente de XA3
 x[i][10] - resultado da funcao ou restricao

 operadores das equacoes:
 1 - > =
 2 - < =
 3 - =

 processos:
 max_min = 1 -> maximizar
 max_min = 2 -> minimizar

 */


//Funcoes do Programa
void  entrada_dados(float x[][11],int *qtde_var,int *qtde_res,int op[]);
void  mostra_tabela(float x[][11],int qtde_var,int qtde_res,int op[],int *aux);
 int  variavel_que_entra(float x[][11],int qtde_var,int aux);
 int  linha_pivo(float x[][11],int qtde_res,int col);
void  nova_linha_pivo(float x[][11],int qtde_var,int qtde_res,int lin,int col);
void  novas_linhas(float x[][11],int qtde_res,int lin,int col);
 int  coeficientes_negativos(float x[][11],int qtde_var,int aux);
void  main();

void main()
{
 int qtde_var,qtde_res,col,lin,op[5],aux=0,i;
 float x[5][11];

 entrada_dados(x,&qtde_var,&qtde_res,op);

 mostra_tabela(x,qtde_var,qtde_res,op,&aux);

 //Se o metodo for de duas fases, primeiro
 //trabalha a funcao objetivo auxiliar
 if(aux)
 {

  while(coeficientes_negativos(x,qtde_var,aux))
  {
   col=variavel_que_entra(x,qtde_var,aux);

   cout<<"\n\n\nVariavel que entra: "<<x[4][col]<<", coluna: X"<<col;

   lin=linha_pivo(x,qtde_res,col);

   cout<<"\n\nLinha pivo: "<<lin;

   getch();

   nova_linha_pivo(x,qtde_var,qtde_res,lin,col);

   novas_linhas(x,qtde_res,lin,col);

   mostra_tabela(x,qtde_var,qtde_res,op,&aux);

  }//Fim do while coef_negativos

  //Finaliza a primeira fase.
  //Garante que aux nao sera' mais setado como 1
  aux=0;
  //Para isso, seta todos os operadores = 2.
  //Os operadores nao fazem mais diferenca
  for(i=1;i<4;i++)
   op[i]=2;

  mostra_tabela(x,qtde_var,qtde_res,op,&aux);

 }//Fim do se aux

 //Para qualquer um dos metodos, realiza o simplex normal
 while(coeficientes_negativos(x,qtde_var,aux))
 {
  col=variavel_que_entra(x,qtde_var,aux);

  cout<<"\n\n\nVariavel que entra: "<<x[0][col]<<", coluna: X"<<col;

  lin=linha_pivo(x,qtde_res,col);

  cout<<"\n\nLinha pivo: "<<lin;

  getch();

  nova_linha_pivo(x,qtde_var,qtde_res,lin,col);

  novas_linhas(x,qtde_res,lin,col);

  mostra_tabela(x,qtde_var,qtde_res,op,&aux);
 }

 cout<<"\n\nFim!";

 getch();

}

void entrada_dados(float x[][11],int *qtde_var,int *qtde_res,int op[])
{
 int i,j,max_min,aux=0;//Este aux nao e' o mesmo usado no resto do programa
 float coef;
 char sinal,operador[2];

 //Inicializa toda a matriz
 for(i=0;i<5;i++)
 {
  for(j=0;j<11;j++)
   x[i][j]=0;
 }

 //Monta a funcao objetivo

 cout<<"\n\nInforme a quantidade de variaveis na funcao objetivo: ";
 cin>>*qtde_var;

 //Funcao objetivo Z=1
 x[0][0]=1;

 for(i=1;i<(*qtde_var+1);i++)
 {
  cout<<"\nInforme o coeficiente de x"<<i<<": ";
  cin>>x[0][i];
 }

 cout<<"\n(1) Maximizar ou (2) Minimizar: ";
 cin>>max_min;

 clrscr();

 //Monta as restricoes do problema

 cout<<"\nInforme a quantidade de restricoes: ";
 cin>>*qtde_res;

 for(i=1;i<(*qtde_res+1);i++) //i=1 e qtde_res+1 porque x[0][] e' fun. obj.
 {
  clrscr();

  cout<<"\nRestricao "<<i<<":\n";

  //Restricao Z=0
  x[i][0]=0;

  for(j=1;j<(*qtde_var+1);j++)
  {
   cout<<"\nInforme o coeficiente de x"<<j<<": ";
   cin>>x[i][j];
  }

  cout<<"\nOperador >= , <= , = : ";
  gets(operador);

  //Guarda o operador da restricao
  //Cria as variaveis de folga e auxiliar para esta restricao
  if(strcmp(operador,">=")==0)
  {
   op[i]=1;
   x[i][i+3]=-1;
   x[i][i+6]=1;
   aux=1;
  }
  else if(strcmp(operador,"<=")==0)
  {
   op[i]=2;
   x[i][i+3]=1;
  }
  else //operador =
  {
   op[i]=3;
   x[i][i+6]=1;
   aux=1;
  }

  cout<<"\nInforme o resultado: ";
  cin>>x[i][10];

 }

 //Calcula os valores da funcao objetivo auxiliar
 if(aux)
 {
  for(i=1;i<*qtde_res+1;i++)
  {
   //Apenas as linhas que possuem variavel auxiliar entram no calculo
   if(x[i][i+6])
   {
    for(j=1;j<7;j++)
     x[4][j]= x[4][j]+( x[i][j] * -1 );
   }
  }

  //Calcula o resultado da funcao objetivo auxiliar
  for(i=1;i<*qtde_res+1;i++)
  {
   //Apenas as linhas que possuem variavel auxiliar entram no calculo
   if(x[i][i+6])
    x[4][10]= x[4][10]+( x[i][10] * -1 );
  }

  //Seta a cabeca da funcao objetivo auxiliar
  if(max_min==1) //Maximizacao, inverte a fun. obj. aux.
   x[4][0]=x[0][0]*-1;
  else
   x[4][0]=x[0][0];

 }//Fim do se aux

 //Monta toda a parte informativa inicial
 clrscr();

 //Informa ao usuario como ficou a funcao objetivo
 cout<<"Z = ";
 for(i=1;i<(*qtde_var+1);i++)
 {
  //coef e' uma variavel auxiliar utilizada apenas para mostrar
  //os valores de forma mais amigavel
  coef=x[0][i];

  //Inverte os valores dos coeficientes da funcao objetivo
  //como se faz no algoritmo quando da montagem da tabela
  x[0][i]= x[0][i]*(-1);

  if(coef<0)
  {
   coef=coef*(-1);
   sinal='-';
  }
  else
   sinal='+';

  if(i>1 || sinal=='-')
   cout<<" "<<sinal<<" ";

  cout<<coef<<"X"<<i;
 }

 cout<<"\n\n";

 //Informa ao usuario como ficaram as restricoes

 for(i=1;i<(*qtde_res+1);i++)
 {
  cout<<"Restricao "<<i<<": ";
  for(j=1;j<(*qtde_var+1);j++)
  {
   coef=x[i][j];

   if(coef<0)
   {
    coef=coef*-1;
    sinal='-';
   }
   else
    sinal='+';

   if(j>1 || sinal=='-')
    cout<<" "<<sinal<<" ";

   cout<<coef<<"X"<<j;
  }

  if(op[i]==1)
   cout<<" >= "<<x[i][10]<<"\n\n";
  else if(op[i]==2)
   cout<<" <= "<<x[i][10]<<"\n\n";
  else
   cout<<"  = "<<x[i][10]<<"\n\n";

 }

 //Para minimizar no metodo de uma fase, inverte a funcao objetivo
 if( (max_min==2) && (!aux) )
 {
  for(j=0;j<11;j++)
  {
   if(x[0][j]!=0)
    x[0][j]=x[0][j]*-1;
  }
 }

 getch();

}

void mostra_tabela(float x[][11],int qtde_var,int qtde_res,int op[],int *aux)
{

 int i,j;

 //Verifica se devo exibir as variaveis e a funcao obj. auxiliar
 for(i=1;i<qtde_res+1;i++)
 {
  if(op[i]!=2)
   *aux=1;
 }

 clrscr();

 //Monta a tabela do problema de forma legivel
 cout<<"Tabela inicial:\n\n";

 //Exibe a tabela para o metodo duas fases
 if(*aux)
 {
  //Cabecalho
  cout<<"Z      X1     X2     X3     XF1    XF2    XF3    XA1    XA2    XA3    R\n\n";

  for(i=0;i<(qtde_res+1);i++) //qtde_res+1 = + fun. obj
  {
   for(j=0;j<11;j++)
    cout<<setprecision(2)<<setfill(' ')<<left<<setw(7)<<x[i][j];
   cout<<"\n\n";
  }

  //Cabecalho
  cout<<"\nFuncao Objetivo Auxiliar:\n\n";

  //Dados da funcao objetivo auxiliar
  for(j=0;j<11;j++)
   cout<<setprecision(2)<<setfill(' ')<<left<<setw(7)<<x[4][j];
 }
 //Exibe a tabela para o metodo de uma fase
 else
 {
  //Cabecalho
  cout<<"Z        X1       X2       X3       XF1      XF2      XF3      R\n\n";

  for(i=0;i<(qtde_res+1);i++) //qtde_res+1 = + fun. obj
  {
   for(j=0;j<7;j++)
    cout<<setprecision(2)<<setfill(' ')<<left<<setw(9)<<x[i][j];
   //Resultados
   cout<<setprecision(2)<<setfill(' ')<<left<<setw(9)<<x[i][10];
   cout<<"\n\n";
  }

 }

 getch();
 
}

int variavel_que_entra(float x[][11],int qtde_var,int aux)
{
 int i,col;
 float menor;

 //Se o metodo for de duas fases, verifica se a
 //funcao objetivo auxiliar esta ativa e busca
 //a variavel que entra nela
 if(aux)
 {

  menor=x[4][1];

  for(i=1;i<(qtde_var+1);i++)
  {
   if(x[4][i]<=menor)
   {
    menor=x[4][i];
    col=i;
   }
  }

 }

 //Busca na funcao objetivo auxiliar
 else
 {
  menor=x[0][1];

  for(i=1;i<(qtde_var+1);i++)
  {
   if(x[0][i]<=menor)
   {
    menor=x[0][i];
    col=i;
   }
  }

 }

 return col;

}

int linha_pivo(float x[][11],int qtde_res,int col)
{
 int i,lin;
 float menor,res_divisao[5];

 //Resultado da divisao recebe o resultado da restricao (x[i][10])
 //dividido pela variavel que entra da restricao (x[i][col])
 for(i=1;i<(qtde_res+1);i++)
 {
  if(x[i][col]>0)
   res_divisao[i]=x[i][10]/x[i][col];
  else
   res_divisao[i]=1000000; //seto com um no. grande p/ ele nao ser o menor
 }

 menor=res_divisao[1];

 //Define a linha pivo como a linha que possui o menor
 //resultado da divisao realizada acima
 for(i=1;i<(qtde_res+1);i++)
 {
  if(res_divisao[i]<=menor)
  {
   menor=res_divisao[i];
   lin=(i+1); //i+1 porque e' o no. da linha e nao da restricao
  }
 }

 return lin;

}

void  nova_linha_pivo(float x[][11],int qtde_var,int qtde_res,int lin,int col)
{
 int i;
 float div;

 lin=lin-1; //Agora vou usar como indice e nao no. de linha

 div=x[lin][col];

 //Novos coeficientes
 for(i=0;i<11;i++)
  x[lin][i]=x[lin][i]/div;

}

void  novas_linhas(float x[][11],int qtde_res,int lin,int col)
{
 int i,j;
 float mult,temp[11];

 lin=lin-1; //-1 porque agora vou usar como indice e nao no. de linha

 for(j=0;j<(qtde_res+2);j++) //+2 por causa da funcao obj. auxiliar
 {
  //A linha pivo nao passa pelo processo
  if(j!=lin)
  {
   mult=( x[j][col] * -1 );

   //temp recebe a nova linha pivo * a var que entra inv. da linha j
   for(i=0;i<11;i++)
    temp[i]=( x[lin][i] * mult );

   //nova linha j recebe o resultado da oper. anterior mais a linha j antiga
   for(i=0;i<11;i++)
    x[j][i]=x[j][i]+temp[i];
  }
 }

}

int coeficientes_negativos(float x[][11],int qtde_var,int aux)
{
 int i,neg=0;

 //Se o metodo for de duas fases, verifica se a
 //funcao objetivo auxiliar esta ativa e busca nela
 if(aux)
 {

  for(i=1;i<(qtde_var+1);i++)
  {
   if(x[4][i]<0)
    neg=1;
  }

 }

 //Busca a variavel que entra na funcao objetivo
 else
 {

  for(i=1;i<(qtde_var+1);i++)
  {
   if(x[0][i]<0)
    neg=1;
  }

 }

 return neg;
}