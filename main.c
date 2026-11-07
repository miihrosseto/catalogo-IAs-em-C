//Bibliotecas------
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//definindo-----------
#define qtdIA 50
#define tamNome 81
#define tamPrompt 1001

//protótipos de funções----------------------------------------------------------------------------
int menuGeral();
int menuLocal();
int menuSetores();
int lerTexto();
int lerInt();
void cadastro(int ids[], char nomesIA[][tamNome], int setor[], int notas[], char prompts[][tamPrompt], int *qtdCadastradas);
void listarIA(int ids[], char nomesIA[][tamNome], int setor[], int notas[], char prompts[][tamPrompt], int qtdCadastradas);
void buscarSetor(int setor[], char nomesIA[][tamNome], int ids[], int notas[], char prompts[][tamPrompt], int qtdCadastradas);
void buscarId(int x[], char z[][tamNome], int a[], char p[][tamPrompt], int b);
void buscarNome(int ids[], char nomesIA[][tamNome], int notas[], char prompts[][tamPrompt], int qtdCadastradas);
void carregarCatalogo(int ids[], char nomesIA[][tamNome], int setor[], int notas[], char prompts[][tamPrompt], int *qtdCadastradas);
void terminarLinha(FILE *arq);
void verificarArq();


//variáveis globais------------
char nomesIA[qtdIA][tamNome];
int notas[qtdIA];
int setor[qtdIA];
int ids[qtdIA];
char prompts[qtdIA][tamPrompt];
int qtdCadastradas = 0;
FILE *arquivoIA;


//função principal
int main(){
    int escolha;   // declarada FORA do do-while para poder ser usada na condicao
    do{
        escolha = menuGeral();

        switch (escolha) {

            case 1:
                cadastro(ids,nomesIA,setor,notas,prompts,&qtdCadastradas);
                break;

            case 2:
                listarIA(ids, nomesIA, setor, notas, prompts, qtdCadastradas);
                break;

            case 3:
                printf("buscar id");
                break;

            case 4:
                printf("buscar nome");
                break;

            case 5:
                printf("buscarSetor");
                break;

            case 6:
                printf("==================================   AVISO!   ============================================\n");
                printf("|  Este programa foi feito com base na LGPD, com o objetivo de conectar e ajudar pessoas.|\n");
                printf("|  Ao cadastrar ou editar nosso sistema, sempre se lembre que outros o usarao.           |\n");
                printf("|  Sempre leve em conta os direitos humanos ao adicionar IAs e seus prompts.             |\n");
                printf("|  Ass: Margareth <3                                                                     |\n");
                printf("==========================================================================================\n");
                break;

            case 7:
                printf("Encerrando o programa...\n");
                break;

            case 0:
                printf("Entrada invalida! Digite um numero.\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;


}}while (escolha != 7);
return 0;
}


int menuGeral() {

    printf("\n|================ BEM - VINDO =================|\n");
    printf("|          Ola! Eu sou a Margareth!            |\n");
    printf("|  Estou aqui para te ajudar a achar I.A's!    |\n");
    printf("|==============================================|\n");
    printf("1 - Cadastrar IA\n");
    printf("2 - Listar IAs\n");
    printf("3 - Buscar por ID\n");
    printf("4 - Buscar por nome\n");
    printf("5 - Buscar por setor\n");
    printf("6 - LEIA-ME\n");
    printf("7 - Sair\n");
    printf("Escolha uma opcao: ");

    return lerInt();

}

int menuSetores(){

    printf("Agora, digite o numero desejado!\n");
    printf("1 - TI\n");
    printf("2 - Cozinha\n");
    printf("3 - Recursos Humanos\n");
    printf("4 - Financeiro\n");
    printf("5 - Estoque\n");
    printf("6 - Outros\n");
    printf("7 - voltar ao menu Geral\n");
    printf("Escolha o setor: ");

    return lerInt();
}

//função usada pra verificar se os numeros são válidos e ajuda a evitar quebras
int lerInt() {
    int valor;

    if(scanf("%d", &valor) != 1){
        valor = 0;
    }
    terminarLinha(stdin);
    return valor;
}

// termina a linha de forma segura
void terminarLinha(FILE *arq){
    int c;
    while ((c = fgetc(arq)) != '\n' && c != EOF);
}

//cadastrando um agente
void cadastro(int ids[], char nomesIA[][tamNome], int setor[], int notas[], char prompts[][tamPrompt], int *qtdCadastradas){

    int posicao = *qtdCadastradas;
    int s;
    int n;
    ids[posicao] = posicao + 1;


    if (posicao >= qtdIA) {
        printf("Limite de IAs cadastradas atingido.\n");
        return;
    }
    printf("Digite o nome da IA:\n");
    lerTexto(nomesIA[posicao], tamNome);

    if (nomesIA[posicao][0] == '\0') {
        printf("O nome nao pode ficar vazio.\n");
        return;
    }

    printf("Digite o prompt da IA (uma descricao do que ela faz, ate %d caracteres):\n", tamPrompt - 1); //-1 pq desconta o caractere '\0'

    lerTexto(prompts[posicao], tamPrompt);

    if (prompts[posicao][0] == '\0') {
        printf("O prompt nao pode ficar vazio.\n");
        return;
    }

    // setor: repete ate ser valido (1 a 6) ou o usuario voltar (7)
    do {
        s = menuSetores();

        if (s == 7) {
            printf("Cadastro cancelado.\n");
            return;}
        if (s < 1 || s > 6) {
            printf("Setor invalido! Escolha de 1 a 6.\n");}
    } while (s < 1 || s > 6);
            setor[posicao] = s; //tem que ser depois do do-while pq se não retorna o endereço pro arquivo


    // nota: repete ate ser valida (1 a 5)
    do {

        printf("Digite a nota da IA (0 - 5):\n");
        n = lerInt();
        if (n < 0 || n > 5) {
            printf("Nota invalida! Escolha de 0 a 5.\n");
        }
    } while (n < 0 || n > 5);
    notas[posicao] = n;

    //abrindo o arquivo pra salvar a ia
    arquivoIA = fopen("catalogo.txt", "a");
    //verifica se tem erro
    if (arquivoIA == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    fprintf(arquivoIA,"============================================\n");
    fprintf(arquivoIA, "ID: %d\n", ids[posicao]);
    fprintf(arquivoIA, "NOME: %s\n", nomesIA[posicao]);
    fprintf(arquivoIA, "SETOR: %d\n", setor[posicao]);
    fprintf(arquivoIA, "NOTA: %d\n", notas[posicao]);
    fprintf(arquivoIA, "PROMPT: %s\n", prompts[posicao]);
    fprintf(arquivoIA,"============================================\n\n");
    fclose(arquivoIA);

    (posicao)++;

    printf("IA cadastrada com sucesso! <3\n");
}


void verifArq(){
    arquivoIA = fopen("catalogo.txt","a");
    int escolhaCriarARQ = 0;
    if(arquivoIA == NULL){
        printf("Margaret: Este arquivo não existe. Gostaria de criar um?");
        printf("1 - SIM");
        printf("2 - NAO");
        scanf("%d", &escolhaCriarARQ);
        if(escolhaCriarARQ == 1){
            arquivoIA = fopen("catalogo.txt","w");
            printf("Arquivo criado com sucesso!! <3");}
        else if(escolhaCriarARQ == 2){
            printf("Arquivo não criado ;)");
            }
        else{
            printf("Entrada inválida. Tente novamente :(");
            }
        }printf("Arquivo abreto com sucesso! <3");
        fclose(arquivoIA);
}
//função pra excluir o ultimo '\n' e substitui por '\0'
int lerTexto(char onde[], int tam) {

    if (fgets(onde, tam, stdin) == NULL) {
        onde[0] = '\0';
        return 0;}

    if (strchr(onde, '\n') != NULL) {
        onde[strcspn(onde, "\n")] = '\0';}
    else {
        terminarLinha(stdin);}   // linha maior que o buffer

    return 1;
}

//Lista todos os agentes e suas caracteristicas
void listarIA(int ids[], char nomesIA[][tamNome], int setor[], int notas[],char prompts[][tamPrompt], int qtdCadastradas) {
    fopen("catalogo.txt", "r");
    if (qtdCadastradas == 0) {
        printf("Nenhuma IA cadastrada.\n");
        return;
    }

    printf("\n--- Lista de IAs Cadastradas ---\n");

    for (int i = 0; i < qtdCadastradas; i++) {
        int s = setor[i];
        if (s < 1 || s > 6) s = 0;  // setor invalido vira "Desconhecido"

        printf("ID: %d\n", ids[i]);
        printf("Nome: %s\n", nomesIA[i]);
        printf("Setor: %d\n", setor[i]);
        printf("Nota: %d\n", notas[i]);
        printf("Prompt: %s\n", prompts[i]);
        printf("-----------------------------\n");
    }
    fclose(arquivoIA);
}
