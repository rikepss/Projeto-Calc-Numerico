#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ao_quadrado(double base, int expoente) {
    int i;
    double sum = 1;
    for(i = 0; i < expoente; i++) {
        sum = base*sum;
    }
    return sum;
}

int main() {
    FILE *f;
    int i = 0, j, k;
    int qtd_pontos, grau;
    char nome[30];

    printf("Digite o nome do arquivo a ser lido: ");
    scanf("%s",nome);
    if (fopen(nome,"r") == NULL) {
        printf("Arquivo invalido ou inexistente");
        exit(0);
    }

    printf("Entre com o numero de pontos a ser inserido:\n");
    scanf("%d",&qtd_pontos);
    printf("Digite o grau do polinomio a ser aproximado:\n");
    scanf("%d", &grau);


    f = fopen(nome,"r");

    double pontos[grau + 2][qtd_pontos];

    while(i < qtd_pontos) {
        fscanf(f,"%lf    %lf", &pontos[2][i], &pontos[0][i]);
        pontos[1][i] = 1;
        i++;
    }

    for(i = 3; i < grau + 2; i++) {
        for(j = 0; j < qtd_pontos; j++){
            pontos[i][j] = pow(pontos[2][j], i-1);
        }
    }

    //zera a matriz
    double sist_linear[grau+2][grau+2];

    for(i = 0; i < grau + 2; i++) {
        for(j = 0; j < grau + 2; j++){
            sist_linear[i][j] = 0.0;
        }
    }

    //(ui,uj)
    for(i = 1; i < grau + 2; i++) {
        for(j = 1; j < grau + 2; j++){
            for(k = 0; k < qtd_pontos; k++){
                sist_linear[i][j] += pontos[i][k]*pontos[j][k];
            }
        }
    }

    //(y,ui)
    for(i = 1; i < grau + 2; i++){
        for(k = 0; k < qtd_pontos; k++){
            sist_linear[0][i] += pontos[0][k]*pontos[i][k];
        }
    }

    for(i = 0; i < grau + 2; i++) {
        for(j = 1; j < grau + 2; j++){
            printf("%.0lf	\t",sist_linear[i][j]);
        }
        printf("\n");
    }

    double Q = 0.0;
    double linear[2];
    double quadr[3];
    double grau3[4];
    //CALCULA Q DO GRAU 1
    if (grau == 1) {


        linear[0] = -43109341.765961502;
        linear[1] = 22174.41585668;
        for(i = 0; i < qtd_pontos; i++) {
            Q += pow(pontos[0][i] - (linear[0] + (linear[1]*pontos[2][i])),2);
        }
        printf("\nQ = %lf\n\n", Q);

        //calcula estimativa
        printf("Y(2018) = %lf\n\n\n",linear[0] + linear[1]*2018.0);
    }

    //CALCULA Q DO GRAU 2
    else if (grau == 2) {

        Q = 0.0;
        quadr[0] = 1202817491.505279312;
        quadr[1] = -1232296.798835075;
        quadr[2] = 315.749110167;
        for(i = 0; i < qtd_pontos; i++) {
            Q += pow(pontos[0][i] - (quadr[0] + (quadr[1]*pontos[2][i]) + quadr[2]*pontos[3][i]),2);
        }
        printf("\nQ = %lf\n\n", Q);

        //calcula estimativa
        printf("Y(2018) = %lf\n\n\n",quadr[0] + quadr[1]*2018.0 + quadr[2]*2018.0*2018.0);
    }


    //CALCULA Q DO GRAU 3
    else if (grau == 3) {

        Q = 0.0;
        grau3[0] = 764629081.413502344;
        grau3[1] = -8132976.886461636;
        grau3[2] = 3789.665475162;
        grau3[3] = -0.582920777;
        for(i = 0; i < qtd_pontos; i++) {
            Q +=  ao_quadrado(pontos[0][i] - (grau3[0] + (grau3[1]*pontos[2][i]) + grau3[2]*pontos[3][i] + grau3[3]*pontos[4][i]),2.0);
            //printf("grau3[3]*pontos[4][i]= %lf|| pontos[4][%d] = %lf\n",grau3[3]*pontos[4][i],i,pontos[4][i]);
        }
        printf("\nQ = %lf\n\n", Q);

        //calcula estimativa
        printf("Y(2018) = %lf\n\n\n",grau3[0] + grau3[1]*2018.0 + grau3[2]*2018.0*2018.0 + grau3[3]*2018.0*2018.0*2018.0);
    }

    return 0;
}
