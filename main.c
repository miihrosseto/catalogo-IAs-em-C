#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definindo-----------
#define qtdIA 50
#define tamNome 81
#define tamPrompt 1001



//protótipos de funções
int carregarIAS(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt]);
int salvarIAS(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i);
int cadastrarIAS(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i);
void listarIAS(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i);
void buscarNome(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i);
void buscarID(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i);
void buscarSetor(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i);
int editarIA(int ids[qtdIA], char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i);
void menuGeral();
int menuSetores();
void terminarLinha(FILE *arq);
void limparBuffer();
FILE *arquivo;





//função principal
int main(){
char nomesIA[qtdIA][tamNome];
int notas[qtdIA];
int setor[qtdIA];
int ids[qtdIA];
char prompts[qtdIA][tamPrompt];
int qtdCadastradas = 0;
qtdCadastradas = carregarIAS(ids, nomesIA, setor, notas, prompts);
int opcao = 0;

do{
menuGeral();
if (scanf("%d", &opcao) != 1){
limparBuffer();
opcao = 0;
}


switch (opcao){
case 1://antes de completar a ação de cadastro, verifica se existe espaço pra uma nova ia
if (qtdCadastradas < qtdIA){
if (cadastrarIAS(ids, nomesIA, setor, notas, prompts, qtdCadastradas) == 1){
qtdCadastradas++;
printf("Cadastro Realizado!\n");
} else {
printf("Inconsistencia verificada. Cadastro não realizado!\n");
}
} else {
printf("Maximo de %d IA's atingido!\n", qtdCadastradas);
}
break;

case 2:
if (qtdCadastradas > 0){// primeiro ve se existem IAs cadastradas pra listar.
listarIAS(ids, nomesIA, setor, notas, prompts, qtdCadastradas);
}
else{
printf("Nenhuma IA cadastrada! :(\n");
}
break;

case 3://verifica o retorno da função de salvar no .txt. Se retorna 1 é pq deu certo.
if (salvarIAS(ids, nomesIA, setor, notas, prompts, qtdCadastradas) == 1){
printf("Dados salvos! ;)\n");
} else {
printf("Erro ao salvar os dados!:(\n");
}
break;

case 4:
buscarNome(ids, nomesIA, setor, notas, prompts,qtdCadastradas);
break;

case 5:
buscarID(ids, nomesIA, setor, notas, prompts, qtdCadastradas);
break;

case 6:
buscarSetor(ids, nomesIA, setor, notas, prompts, qtdCadastradas);
    break;

case 7:
    qtdCadastradas = editarIA(ids, nomesIA, setor, notas, prompts, qtdCadastradas);
    break;

case 8://aviso de direitos humanos
    printf("==================================   AVISO!   ============================================\n");
    printf("|  Este programa foi feito com base na LGPD, com o objetivo de conectar e ajudar pessoas.|\n");
    printf("|  Ao cadastrar ou editar nosso sistema, sempre se lembre que outros o usarao.           |\n");
    printf("|  Sempre leve em conta os direitos humanos ao adicionar IAs e seus prompts.             |\n");
    printf("|  Ass: Margareth <3                                                                     |\n");
    printf("==========================================================================================\n");
    break;
case 9:
    printf("Saindo...");
    break;

default:
printf("Opcao invalida\n");
}

} while (opcao != 9);
return 0;
}








//funções

int cadastrarIAS(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i){
int maiorid = 0;

for (int j=0; j<i; j++){
    if(ids[j] > maiorid){
        maiorid = ids[j];
    }
} ids[i] = maiorid+1;
limparBuffer();


printf("Digite o nome da IA de ate 80 caracteres: ");
if (fgets(nomesIA[i], tamNome, stdin) == NULL){
return 0;}
if (strchr(nomesIA[i], '\n') == NULL){
limparBuffer();}
nomesIA[i][strcspn(nomesIA[i], "\n")] = '\0';


menuSetores();
printf("\n: ");
if(scanf("%d", &setor[i]) != 1){
limparBuffer();
return 0;}
limparBuffer();

printf("Digite a Nota de 0-5: ");
if(scanf("%d", &notas[i]) != 1){
    limparBuffer();
    return 0;}
limparBuffer();


printf("Digite o prompt de até 1000 caracteres: ");
if(fgets(prompts[i], tamPrompt,stdin)== NULL){
return 0;}
if (strchr(prompts[i], '\n') == NULL){
limparBuffer();}
prompts[i][strcspn(prompts[i], "\n")] = '\0';
printf("\n|============================== DICA ====================================|\n");
printf("|Dica da Margareth:                                                      |\n");
printf("|Depois de criar um agente, SEMPRE salve o arquivo no menu principal(3)  |\n");
printf("|========================================================================|\n\n");

system("PAUSE");
return 1;
}




int carregarIAS(int ids[qtdIA], char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt]){
    int i = 0;
    FILE *arquivo = fopen("catalogo.txt", "r");

    if (arquivo == NULL) return 0;

    while(i < qtdIA && fscanf(arquivo, "%d", &ids[i]) == 1){
        terminarLinha(arquivo);

        if (fgets(nomesIA[i], tamNome, arquivo) == NULL)
            break;
        nomesIA[i][strcspn(nomesIA[i], "\n")] = '\0';

        if (fscanf(arquivo, "%d", &setor[i]) != 1)
            break;
        terminarLinha(arquivo);

        if (fscanf(arquivo, "%d", &notas[i]) != 1)
            break;
        terminarLinha(arquivo);

        if (fgets(prompts[i], tamPrompt, arquivo) == NULL)
            break;
            if (strchr(prompts[i], '\n') == NULL){
            terminarLinha(arquivo);}
            prompts[i][strcspn(prompts[i], "\n")] = '\0';

        i++;
    }

    fclose(arquivo);
    return i;
}




void listarIAS(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i){
for(int j = 0; j < i; j++){
printf("\n||-------------------------------------------------------------||\n");
printf("IDS: %d\nNome: %s\nSetor: %d\nNota: %d\nPrompt: %s\n", ids[j], nomesIA[j], setor[j], notas[j],prompts[j]);
printf("||-------------------------------------------------------------||\n");
}
}




int salvarIAS(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i){
FILE *arquivo = fopen("catalogo.txt", "w");
if (arquivo == NULL) return 0;
for(int j = 0; j < i; j++){
fprintf(arquivo, "%d\n%s\n%d\n%d\n%s\n", ids[j], nomesIA[j], setor[j], notas[j], prompts[j]);
}
fclose(arquivo);
return 1;
}




void buscarID(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i){
int idbusca = 0;
int encontrado = 0;

printf("digite o id que gostaria de buscar:\n");
if(scanf("%d", &idbusca) != 1){
    limparBuffer();
    printf("ID invalido :/\n");
    return;
}
limparBuffer();

for (int j=0; j <i; j++){
    if(ids[j] == idbusca){
        printf("IA encontrada! :D\n");
        printf("%d\n%s\n%d\n%d\n%s\n", ids[j], nomesIA[j], setor[j], notas[j], prompts[j]);
        encontrado = 1;}
}
                if (encontrado == 0){
                printf("IA nao encontrada:(");}
}




void buscarNome(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i){
char nomebusca[tamNome];
int encontrado = 0;

limparBuffer();
printf("Digite o nome que gostaria de buscar:\n");

if (fgets(nomebusca, tamNome, stdin) == NULL){
    printf("Nome invalido... :/\n");
    return;}
if (strchr(nomebusca, '\n') == NULL){
    limparBuffer();}
nomebusca[strcspn(nomebusca, "\n")] = '\0';

if (nomebusca[0] == '\0'){
    printf("Nome invalido... :/\n");
    return;}

for (int j=0; j<i; j++){
    if (strcmp(nomesIA[j], nomebusca) == 0){
            printf("%d\n%s\n%d\n%d\n%s\n", ids[j], nomesIA[j], setor[j], notas[j], prompts[j]);
            encontrado = 1;}
}if (encontrado == 0){
    printf("Nome não encontrado :(");}
}




void buscarSetor(int ids[qtdIA],char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i){
int setorbusca = 0;
int encontrado = 0;
menuSetores();
printf("7 - voltar ao menu Geral\n");
printf("\nDigite o setor que gostaria de buscar:\n");

if(scanf("%d", &setorbusca) != 1){
    limparBuffer();
    printf("Setor invalido :/\n");
    return;
}limparBuffer();

if(setorbusca == 7){
   return;}

for (int j=0; j <i; j++){
    if(setor[j] == setorbusca){
        printf("IA encontrada! :D\n");
        printf("%d\n%s\n%d\n%d\n%s\n", ids[j], nomesIA[j], setor[j], notas[j], prompts[j]);
        encontrado = 1; }
}
                if (encontrado == 0){
                printf("IA nao encontrada:(");}



}




void terminarLinha(FILE *arq) {
int ch;
while ((ch = fgetc(arq)) != '\n' && ch != EOF);
}




void limparBuffer(){
int c;
while ((c = getchar()) != '\n' && c != EOF);
}




int menuSetores(){

    printf("\nAgora, escolha o setor a qual a IA pertence!\n");
    printf("1 - TI\n");
    printf("2 - Cozinha\n");
    printf("3 - Recursos Humanos\n");
    printf("4 - Financeiro\n");
    printf("5 - Estoque\n");
    printf("6 - Outros\n");

}




void menuGeral() {

    printf("\n|================ BEM - VINDO =================|\n");
    printf("|          Ola! Eu sou a Margareth!            |\n");
    printf("|  Estou aqui para te ajudar a achar I.A's!    |\n");
    printf("|==============================================|\n");
    printf("1 - Cadastrar IA\n");
    printf("2 - Listar IAs\n");
    printf("3 - Salvar IAS\n");
    printf("4 - Buscar por nome\n");
    printf("5 - Buscar por ID\n");
    printf("6 - Buscar por setor\n");
    printf("7 - Editar uma IA\n");
    printf("8 - LEIA-ME\n");
    printf("9 - Sair\n");
    printf("Escolha uma opcao: ");

}



int editarIA(int ids[qtdIA], char nomesIA[qtdIA][tamNome], int setor[], int notas[], char prompts[qtdIA][tamPrompt], int i){
    int escolha;
    int escolhaedicao;
    int idbusca;
    int j;
    char novonome[tamNome];
    char novoprompt[tamPrompt];

    printf("Voce gostaria de editar ou excluir uma IA? :|\n");
    printf("1 - Editar\n");
    printf("2 - Excluir\n");

    if (scanf("%d", &escolha) != 1 || (escolha != 1 && escolha != 2)){
        limparBuffer();
        printf("Opcao invalida :/\n");
        return i;
    }
    limparBuffer();

    printf("Qual o ID da IA?\n");
    if (scanf("%d", &idbusca) != 1){
        limparBuffer();
        printf("ID invalido :/\n");
        return i;
    }
    limparBuffer();

    for (j = 0; j < i; j++){
        if (ids[j] == idbusca){
            break;
        }
    }

    if (j == i){
        printf("IA nao encontrada :(\n");
        return i;
    }

    printf("IA encontrada! :D\n");
    printf("%d\n%s\n%d\n%d\n%s\n", ids[j], nomesIA[j], setor[j], notas[j], prompts[j]);

    if (escolha == 2){
        for (int k = j; k < i - 1; k++){
            ids[k] = ids[k + 1];
            strcpy(nomesIA[k], nomesIA[k + 1]);
            setor[k] = setor[k + 1];
            notas[k] = notas[k + 1];
            strcpy(prompts[k], prompts[k + 1]);
        }

        printf("IA excluida!\n");
        return i - 1;
    }

    printf("O que gostaria de editar?\n1 - Nome\n2 - Setor\n3 - Nota\n4 - Prompt\n");
    if (scanf("%d", &escolhaedicao) != 1){
        limparBuffer();
        printf("Opcao invalida :/\n");
        return i;
    }
    limparBuffer();

    switch (escolhaedicao){
        case 1:
            printf("\nDigite o novo nome: ");
            if (fgets(novonome, tamNome, stdin) == NULL){
                printf("Erro ao ler o nome.\n");
                break;
            }
            if (strchr(novonome, '\n') == NULL){
                limparBuffer();
            }
            novonome[strcspn(novonome, "\n")] = '\0';
            strcpy(nomesIA[j], novonome);
            printf("Nome alterado com sucesso!\n");
            break;

        case 2:
            printf("\nDigite o novo setor: ");
            if (scanf("%d", &setor[j]) == 1){
                printf("Setor alterado com sucesso!\n");
            } else {
                printf("Setor invalido :/\n");
            }
            limparBuffer();
            break;

        case 3:
            printf("\nDigite a nova nota: ");
            if (scanf("%d", &notas[j]) == 1){
                printf("Nota alterada com sucesso!\n");
            } else {
                printf("Nota invalida :/\n");
            }
            limparBuffer();
            break;

        case 4:
            printf("\nDigite o novo prompt: ");
            if (fgets(novoprompt, tamPrompt, stdin) == NULL){
                printf("Erro ao ler o prompt.\n");
                break;
            }
            if (strchr(novoprompt, '\n') == NULL){
                limparBuffer();
            }
            novoprompt[strcspn(novoprompt, "\n")] = '\0';
            strcpy(prompts[j], novoprompt);
            printf("Prompt alterado com sucesso!\n");
            break;

        default:
            printf("Opcao invalida :/\n");
    }

    return i;
}
