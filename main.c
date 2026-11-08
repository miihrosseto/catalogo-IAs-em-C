//Bibliotecas------
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//definindo-----------
#define qtdIA 50
#define tamNome 81
#define tamPrompt 1001
#define tamLinha 1200

//prot�tipos de fun��es----------------------------------------------------------------------------
int menuGeral();
int menuLocal();
int menuSetores();
int menuBuscaSetores();
int lerTexto();
int lerInt();
void listarIA();
void cadastro(int ids[], char nomesIA[][tamNome], int setor[], int notas[], char prompts[][tamPrompt], int *qtdCadastradas);
void buscarSetor();
void buscarId();
void buscarNome();
void carregarCatalogo(int ids[], char nomesIA[][tamNome], int setor[], int notas[], char prompts[][tamPrompt], int *qtdCadastradas);
void terminarLinha(FILE *arq);



//vari�veis globais------------
char nomesIA[qtdIA][tamNome];
int notas[qtdIA];
int setor[qtdIA];
int ids[qtdIA];
char prompts[qtdIA][tamPrompt];
int qtdCadastradas = 0;
FILE *arquivoIA;


//fun��o principal
int main(){
    int escolha;   // declarada FORA do do-while para poder ser usada na condicao
    do{
        escolha = menuGeral();

        switch (escolha) {

            case 1:
                cadastro(ids,nomesIA,setor,notas,prompts,&qtdCadastradas);

                break;

            case 2:
                listarIA();
                break;

            case 3:
                buscarId();
                break;

            case 4:
                buscarNome();
                break;

            case 5:
                buscarSetor();
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

    printf("Agora,escolha o setor digitando o numero desejado!\n");
    printf("1 - TI\n");
    printf("2 - Cozinha\n");
    printf("3 - Recursos Humanos\n");
    printf("4 - Financeiro\n");
    printf("5 - Estoque\n");
    printf("6 - Outros\n");
    printf("7 - voltar ao menu Geral\n");
    printf("Escolha o setor:  ");

    return lerInt();
}

int menuBuscaSetores(){

    printf("Qual setor gostaria de buscar? \n");
    printf("1 - TI\n");
    printf("2 - Cozinha\n");
    printf("3 - Recursos Humanos\n");
    printf("4 - Financeiro\n");
    printf("5 - Estoque\n");
    printf("6 - Outros\n");
    printf("7 - voltar ao menu Geral\n");
    printf("Escolha o setor:  ");

    return lerInt();
}
//fun��o usada pra verificar se os numeros s�o v�lidos e ajuda a evitar quebras
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

    int s;
    int n;
    int posicao = 0; //
    int maiorId = 0;
    int idLido;
    char linha[tamLinha];

    // le o arquivo e descobre o maior ID ja cadastrado
    arquivoIA = fopen("catalogo.txt", "r");
    if (arquivoIA != NULL) {
        while (fgets(linha, sizeof(linha), arquivoIA) != NULL) {
            if (sscanf(linha, "ID: %d", &idLido) == 1 && idLido > maiorId) {
                maiorId = idLido;
            }
        }
        fclose(arquivoIA);
    }

    ids[posicao] = maiorId + 1;   // proximo ID, antes de gravar

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
            setor[posicao] = s; //tem que ser depois do do-while pq se n�o retorna o endere�o pro arquivo


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

    (*qtdCadastradas)++;
 
    printf("IA cadastrada com sucesso! <3\n");
}


//fun��o pra excluir o ultimo '\n' e substitui por '\0'
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
void listarIA() {
    char linha[tamLinha]; //soma dos caracteres de nome, prompt, id, setor e nota
    arquivoIA = fopen("catalogo.txt", "r");

    if (arquivoIA == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    printf("\n========= Lista de IAs Cadastradas ==========\n");

    while (fgets(linha, sizeof(linha), arquivoIA) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivoIA);
}


void buscarId() {
    int idBusca;
    int idArquivo;
    int encontrado = 0;
    char linha[tamLinha];

    arquivoIA = fopen("catalogo.txt", "r");

    if (arquivoIA == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    printf("Qual ID deseja buscar? :) ");
    idBusca = lerInt();

    while (fgets(linha, sizeof(linha), arquivoIA) != NULL) {

        if (sscanf(linha, "ID: %d", &idArquivo) == 1) { //sscanf � tipo scanf, mas l� informa��o de uma string, em vez de ler do teclado. retorna 1 pra mostrar que deu certo
            if(idBusca == idArquivo){

            printf("IA encontrada!\n");
            printf("============================================\n");
            printf("%s", linha); // Mostra o ID

            for (int i = 0; i < 4; i++) {
                if (fgets(linha, sizeof(linha), arquivoIA) != NULL) {
                printf("%s", linha);
        }}
        printf("============================================\n");
    encontrado = 1;
    break;
}}}}


void buscarNome() {
    char linha[tamLinha];
    char nomeBusca[tamNome];
    char nomeMin[tamNome];
    char nomeArquivo[tamNome];
    char atualMin[tamNome];

    int encontrado = 0;
    int j;
    int i;

    printf("Qual nome gostaria de buscar? ");
    lerTexto(nomeBusca, tamNome);

    // converte o nome pesquisado para minusculas
    for (j = 0; nomeBusca[j] != '\0'; j++) {
        nomeMin[j] = tolower((unsigned char)nomeBusca[j]);
    }
    nomeMin[j] = '\0';

    if (nomeMin[0] == '\0') {
        printf("Digite um nome para buscar.\n");
        return;
    }

    arquivoIA = fopen("catalogo.txt", "r");

    if (arquivoIA == NULL) {
        printf("Nao foi possivel abrir o arquivo!\n");
        return;
    }

    // Le o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivoIA) != NULL) {

        // verifica a linha
        if (strncmp(linha, "NOME: ", 6) == 0 &&
            sscanf(linha, "NOME: %80[^\n]", nomeArquivo) == 1) {

            // Converte o nome do arquivo para minusculas
            for (j = 0; nomeArquivo[j] != '\0'; j++) {
                atualMin[j] = tolower((unsigned char)nomeArquivo[j]);
            }
            atualMin[j] = '\0';

            // Compara os nomes
            if (strcmp(atualMin, nomeMin) == 0) {
                encontrado = 1;

                printf("\nAgente encontrado! ;D\n");
                printf("NOME: %s\n", nomeArquivo);

                // 3 pq faz mostrar nota, setor, prompt...
                for (j = 0; j < 3; j++) {
                    if (fgets(linha, sizeof(linha), arquivoIA) != NULL) {
                        printf("%s", linha);
                    }
                }
            }
        }
    }

    fclose(arquivoIA);

    if (encontrado == 0) {
        printf("\nNenhuma IA encontrada com esse nome.\n");
    }
}

void buscarSetor(){
    int buscaSetor;
    int setorArquivo;
    int encontrado = 0;
    char linha[tamLinha];
    char linhaAnterior[tamLinha]; //guarda a linha que passou antes
    
    
    buscaSetor = menuBuscaSetores();

    if (buscaSetor == 7 || buscaSetor < 1 || buscaSetor > 7){
        printf("Busca cancelada ou setor invalido\n");
        return;
    }
    
    arquivoIA = fopen("catalogo.txt", "r");

    if (arquivoIA == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    printf("\n========= IAs encontradas no setor ==========\n");

    // Lê o arquivo linha por linha procurando o setor
    while (fgets(linha, sizeof(linha), arquivoIA) != NULL) {

        if (sscanf(linha, "SETOR: %d", &setorArquivo) == 1) {
            if (buscaSetor == setorArquivo) {

                printf("%s", linhaAnterior); //imprime o nome que estava na linha anterior
                printf("%s", linha); // Imprime a linha do setor
                
                // Imprime as linhas restantes do bloco (nota, prompt e divisória final)
                for (int i = 0; i < 3; i++) {
                    if (fgets(linha, sizeof(linha), arquivoIA) != NULL) {
                        printf("%s", linha);
                    }
                }
                
                encontrado = 1;
            }
        }
        //atualiza a linha anterior no final de cada volta do while
        strcpy(linhaAnterior, linha);
    }

    fclose(arquivoIA);

    if (!encontrado) {
        printf("\nNenhuma IA encontrada nesse setor\n");
    }


}
