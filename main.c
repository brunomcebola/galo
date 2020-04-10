#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tabuleiro(char tab[3][3]);
int compara(char tab[3][3]);
void game(int mode, char tab[3][3]);

int main(){
    setlocale(LC_ALL,"");
    int mode,keep=2;
    do{
        keep=2;
        char tab[3][3]={{'_','_','_'},{'_','_','_'},{' ', ' ', ' '}};
        printf("Bem vindo ao seu jogo do galo!\n\n");
        printf("Regras:\n");
        printf(" - O primeiro jogador e o X e o segundo a O\n");
        printf(" - Nao jogue numa casa ja ocupada\n");
        printf(" - DIVIRTA-SE\n\n");
        printf("Deseja jogar com:\n");
        printf(" 1) o computador\n");
        printf(" 2) um adversario\n\n");
        printf("Opcao: ");
        scanf("%d",&mode);
        switch(mode){
        case 1:
            game(1,tab);
            break;
        case 2:
            game(2,tab);
            break;
        default:
            printf("Modo de jogo invalido\n");
        }
        while(keep!=0 && keep!=1){
            printf("Jogar novamente? (1 para sim; 0 para nao)\n");
            printf("Resposta: ");
            scanf("%d",&keep);
            printf("\n");
        }
    } while(keep==1);

    return 0;
}

void tabuleiro(char tab[3][3]){
    for(int i=0;i<3;i++){printf(" %c|%c|%c\n",tab[i][0],tab[i][1],tab[i][2]);}
}

void game(int mode, char tab[3][3]){
    int c,l,j=1,end=0,t=0,check;
    time_t tempo;
    if(mode==1){
        while(end==0){
            if(j==1){
                tabuleiro(tab);
                printf("Indique a linha e a coluna onde deseja jogar\n");
                printf("Linha: ");
                scanf("%d",&l);
                l--;
                printf("Coluna: ");
                scanf("%d",&c);
                c--;
                if(l<0 || l>=3 || c<0 || c>=3){printf("Casa invalida\n");}
                else{
                    if(tab[l][c]=='_' || !tab[l][c] || tab[l][c]==' '){
                        tab[l][c]='X';
                        check=compara(tab);
                        if(check==1){end=1;}
                        else if(check==2){end=1;t=1;}
                        else if(check==0){j++;}
                    }
                    else{printf("A casa ja esta ocupada\n");}
                }
            }
            else if(j==2){
                srand((unsigned) time(&tempo));
                do{
                    c = rand()%3;
                    l = rand()%3;
                }while(l<0 || l>=3 || c<0 || c>=3);
                if(tab[l][c]=='_' || !tab[l][c] || tab[l][c]==' '){
                    tab[l][c]='O';
                    check=compara(tab);
                    if(check==1){end=1;}
                    else if(check==2){end=1;t=1;}
                    else if(check==0){j--;}
                }
            }
        }
        tabuleiro(tab);
        if(t==1){printf("Jogo empatado\n");}
        else{printf("O jogador %d ganhou!\n",j);}
    }
    else if(mode==2){
        while(end==0){
            tabuleiro(tab);
            printf("Indique a linha e a coluna onde deseja jogar\n");
            printf("Linha: ");
            scanf("%d",&l);
            l--;
            printf("Coluna: ");
            scanf("%d",&c);
            c--;
            if(l<0 || l>=3 || c<0 || c>=3){printf("Casa invalida\n");}
            else{
                if(tab[l][c]=='_' || !tab[l][c] || tab[l][c]==' '){
                    if(j==1){tab[l][c]='X';}
                    else{tab[l][c]='O';}
                    check=compara(tab);
                    if(check==1){end=1;}
                    else if(check==2){end=1;t=1;}
                    else if(check==0){
                        if(j==1){j++;}
                        else{j--;}
                    }
                }
                else{printf("A casa ja esta ocupada\n");}
            }
        }
        tabuleiro(tab);
        if(t==1){printf("Jogo empatado\n");}
        else{printf("O jogador %d ganhou!\n",j);}
    }
}

int compara(char tab[3][3]){
    int z=0;
    for(int a=0;a<3;a++){
        for(int b=0;b<3;b++){
            if(tab[a][b]=='X' || tab[a][b]=='O'){z++;}
        }
    }
    if(z==9){return(2);}


    for(int l=0;l<3;l++){
        if((tab[l][0]=='X'&&tab[l][1]=='X'&&tab[l][2]=='X')||(tab[l][0]=='O'&&tab[l][1]=='O'&&tab[l][2]=='O')){return 1;}
        else if((tab[0][l]=='X'&&tab[1][l]=='X'&&tab[2][l]=='X')||(tab[0][l]=='O'&&tab[1][l]=='O'&&tab[2][l]=='O')){return 1;}
    }
    if((tab[0][0]=='X'&&tab[1][1]=='X'&&tab[2][2]=='X')||(tab[0][0]=='O'&&tab[1][1]=='O'&&tab[2][2]=='O')){return 1;}
    else if((tab[0][2]=='X'&&tab[1][1]=='X'&&tab[2][0]=='X')||(tab[0][2]=='O'&&tab[1][1]=='O'&&tab[2][0]=='O')){return 1;}
    return 0;
}
