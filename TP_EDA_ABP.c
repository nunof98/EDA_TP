#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 200

//Estrutura
typedef struct registo
{
    int codigo;
    int velocidade; //(m/s)
    int tempo;
    struct registo *esquerda;
    struct registo *direita;
} * ABP;

//Protótipos
int Menu();
ABP InserirCenario(ABP abp, int codigo, int velocidade, int tempo);
ABP PesquisarCenario(ABP abp, int codigo);
void ListarOrdemCrescente(ABP abp, int i);
void ListarOrdemDecrescente(ABP abp, int i);
int AlterarCenario(ABP abp, int codigo, int velocidade, int tempo);
ABP RemoverCenario(ABP abp, int codigo);
ABP ArvoreMaisEsquerda(ABP abp);
void SimularCenario(ABP abp, int codigo);
int GuardarArvore(ABP abp, char path[]);
int GuardarArvoreAux(ABP abp, FILE *fp);
int LerFicheiro(ABP *abp, char path[]);

int main()
{
    //Variaveis
    int codigo, velocidade, tempo, opcaoAlterar, opcaoMenu;
    char path[STRING_SIZE] = "";
    char resposta;
    ABP abp = NULL;
    ABP temp;

    do
    {
        opcaoMenu = Menu();

        switch (opcaoMenu)
        {
        case 1:
#pragma region Inserir Cenario
            puts("\n=====Inserir novo cenario=====");
            //Pedir ao utilizar o codigo do cenario
            printf("Codigo do cenario: ");
            scanf("%d", &codigo);
            //Pedir ao utilizar a velocidade do objeto
            printf("Velocidade (m/s): ");
            scanf("%d", &velocidade);
            //Pedir ao utilizar o tempo total do cenario
            printf("Tempo total (s): ");
            scanf("%d", &tempo);

            //Verificar se já existe algum cenario com o mesmo codigo, para evitar cenarios repetidos
            temp = PesquisarCenario(abp, codigo);
            if (temp == NULL)
            {
                //Inserir Cenario na arvore
                abp = InserirCenario(abp, codigo, velocidade, tempo);
                puts("Cenerario Inserido!");
            }
            else
                puts("Ja existe um cenario com esse codigo!");

            break;
#pragma endregion Inserir Cenario

        case 2:
#pragma region Pesquisar Cenario
            puts("\n=====Pesquisar cenario=====");
            //Pedir ao utilizar o codigo do cenario
            printf("Codigo do cenario: ");
            scanf("%d", &codigo);
            //Encontrar cenario e mostrá-lo ao utilizador
            temp = PesquisarCenario(abp, codigo);
            if (temp != NULL)
            {
                //Imprimir dados do cenario
                puts("Cenario Encontrado:");
                printf("Codigo: %d; ", temp->codigo);
                printf("Velocidade: %d (m/s); ", temp->velocidade);
                printf("Tempo: %d (s);\n", temp->tempo);
            }
            else
                puts("O cenerario nao foi encontrado");

            break;
#pragma endregion Pesquisar Cenario

        case 3:
#pragma region Listar Cenarios Crescente
            puts("\n=====Listar cenarios por ordem crescente=====");
            //Fazer print da arvore binaria (ordem crescente)
            ListarOrdemCrescente(abp, 0);
            break;
#pragma endregion Listar Cenarios Crescente

        case 4:
#pragma region Listar Cenarios Decrescente
            puts("\n=====Listar cenarios por ordem decrescente=====");
            //Fazer print da arvore binaria (ordem decrescente)
            ListarOrdemDecrescente(abp, 0);
            break;
#pragma endregion Listar Cenarios Decrescente

        case 5:
#pragma region Alterar Cenario
            puts("\n=====Alterar cenario=====");
            //Pedir ao utilizar o codigo do cenario
            printf("Codigo do cenario: ");
            scanf("%d", &codigo);

            temp = PesquisarCenario(abp, codigo);
            if (temp != NULL)
            {
                //Imprimir dados do cenario
                puts("Cenario Encontrado:");
                printf("Codigo: %d; ", temp->codigo);
                printf("Velocidade: %d (m/s); ", temp->velocidade);
                printf("Tempo: %d (s);\n", temp->tempo);

                //Perguntar se o utilizador quer mudar algum dado do cenario
                puts("\nDeseja alterar a: ");
                puts("\t1 - Velocidade");
                puts("\t2 - Tempo");
                puts("\t3 - Velocidade e Tempo");
                puts("\t4 - Nada");

                //Ciclo para garantir que o utilizador escolhe uma opcao valida
                do
                {
                    fflush(stdin);
                    printf("\tOpcao: ");
                    scanf("%d", &opcaoAlterar);
                } while (opcaoAlterar < 1 || opcaoAlterar > 4);

                switch (opcaoAlterar)
                {
                //Alterar Velocidade
                case 1:
                    //Pedir ao utilizar a nova velocidade
                    printf("Nova velocidade: ");
                    scanf("%d", &velocidade);
                    //Colocar tempo com valor negativo, para este não ser alterado
                    tempo = -1;
                    break;

                //Alterar Tempo
                case 2:
                    //Pedir ao utilizar o novo tempo
                    printf("Novo tempo: ");
                    scanf("%d", &tempo);
                    //Colocar velocidade com valor negativo, para este não ser alterado
                    velocidade = -1;
                    break;

                //Alterar Velocidade e Tempo
                case 3:
                    //Pedir ao utilizar a nova velocidade
                    printf("Nova velocidade: ");
                    scanf("%d", &velocidade);
                    //Pedir ao utilizar o novo tempo
                    printf("Novo tempo: ");
                    scanf("%d", &tempo);
                    break;

                default:
                    puts("\nCenario nao alterado!");
                    break;
                }

                //Só chama a função AlterarCenario() se o utilizador quiser alterar algum valor
                if (opcaoAlterar >= 1 && opcaoAlterar <= 3)
                {
                    //Verificar se o cenario foi alterado
                    if (AlterarCenario(abp, codigo, velocidade, tempo))
                        puts("Cenerario Alterado!");
                    else
                        puts("O cenerario nao foi alterado!");
                }
            }
            else
                puts("O cenerario nao foi encontrado");

            break;
#pragma endregion Alterar Cenario

        case 6:
#pragma region Remover Cenario
            puts("\n=====Remover cenario=====");
            //Pedir ao utilizar o codigo do cenario
            printf("Codigo do cenario: ");
            scanf("%d", &codigo);

            abp = RemoverCenario(abp, codigo);
            puts("Operacao Concluida!");
            break;
#pragma endregion Remover Cenario

        case 7:
#pragma region Simulacao de Cenario
            puts("\n=====Simulacao de cenario=====");
            //Pedir ao utilizar o codigo do cenario
            printf("Codigo do cenario: ");
            scanf("%d", &codigo);
            SimularCenario(abp, codigo);
            break;
#pragma endregion Simulacao de Cenario

        case 8:
#pragma region Armazenar cenarios
            puts("\n=====Armazenar cenarios=====");

            //Pedir path para o ficheiro ao utilizador
            fflush(stdin);
            printf("Quer escolher um nome para o ficheiro (y/n)? ");
            scanf("%c", &resposta);
            fflush(stdin);
            if (resposta == 'y' || resposta == 'Y')
            {
                puts("Escreva o nome: ");
                scanf("%s", path);
                strcat(path, ".txt");
            }
            //Default path
            else
                strcpy(path, "ArvoreBinariaProcura.txt");

            if (GuardarArvore(abp, path))
                puts("Cenarios guardados!");
            else
                puts("Os cenerarios nao foram guardados!");
            break;
#pragma endregion Armazenar cenarios

        case 9:
#pragma region Carregar cenarios
            puts("\n=====Carregar cenarios=====");

            //Pedir path do ficheiro ao utilizador
            fflush(stdin);
            printf("Quer escolher o ficheiro a abrir (y/n)? ");
            scanf("%c", &resposta);
            fflush(stdin);
            if (resposta == 'y' || resposta == 'Y')
            {
                puts("Escreva o path do ficheiro: ");
                scanf("%s", path);
                strcat(path, ".txt");
            }
            //Ler default path
            else
                strcpy(path, "ArvoreBinariaProcura.txt");

            if (LerFicheiro(&abp, path))
                puts("Cenarios carregados!");
            else
                puts("Os cenerarios nao foram carregados!");
            break;
#pragma endregion Carregar cenarios

        default:
            puts("\n=====Sair=====");
            break;
        }

    } while (opcaoMenu != 0);

    return 0;
}

//Funcao para imprimir menu na consola e devolver a opcao escolhida pelo utilizador
int Menu()
{
    //Variaveis
    int opcao;

    //Opcoes
    puts("\n=====MENU=====");
    puts("1 - Inserir novo cenario");
    puts("2 - Pesquisar cenario");
    puts("3 - Listar cenarios por ordem crescente");
    puts("4 - Listar cenarios por ordem decrescente");
    puts("5 - Alterar cenario");
    puts("6 - Remover cenario");
    puts("7 - Simulacao de cenario");
    puts("8 - Armazenar cenarios");
    puts("9 - Carregar cenarios");
    puts("0 - Sair\n");

    //Ciclo para garantir que o utilizador escolhe uma opcao valida
    do
    {
        fflush(stdin);
        printf("Opcao: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 9);

    return opcao;
}

/*
Funcao para inserir registos numa arvore binaria de procura
Codigos maiores à direita e codigos menores à esquerda
*/
ABP InserirCenario(ABP abp, int codigo, int velocidade, int tempo)
{
    ABP novo;

    //Verificar se arvore está vazia
    if (abp == NULL)
    {
        novo = (ABP)malloc(sizeof(struct registo));
        novo->codigo = codigo;
        novo->velocidade = velocidade;
        novo->tempo = tempo;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return (novo);
    }
    //Se codigo for maior ir para sub arvore direita
    else if (abp->codigo < codigo)
    {
        abp->direita = InserirCenario(abp->direita, codigo, velocidade, tempo);
        return (abp);
    }
    //Se codigo for menor ir para sub arvore esquerda
    else
    {
        abp->esquerda = InserirCenario(abp->esquerda, codigo, velocidade, tempo);
        return (abp);
    }
}

//Funcao para pesquisar um registo numa arvore binaria de procura
ABP PesquisarCenario(ABP abp, int codigo)
{
    //Verificar se arvore está vazia
    if (abp == NULL)
        return NULL;
    //Cenario encontrado
    else if (abp->codigo == codigo)
        return abp;
    //Se codigo é maior, avançar para a sub arvore direita
    else if (abp->codigo < codigo)
        return (PesquisarCenario(abp->direita, codigo));
    //Se codigo é menor, avançar para a sub arvore esquerda
    else
        return (PesquisarCenario(abp->esquerda, codigo));
}

//Funcao para imprimir na consola todos os registos de uma arvore binaria de procura por ordem crescente
void ListarOrdemCrescente(ABP abp, int i)
{
    //Verificar se arvore não está vazia
    if (abp != NULL)
    {
        //Incrementar nivel
        i++;
        //Percorrer arvore recursivamente
        ListarOrdemCrescente(abp->esquerda, i);
        printf("Nivel: %d\tCenario: %d     Velocidade: %d (m/s)     Tempo: %d (s)\n", i, abp->codigo, abp->velocidade, abp->tempo);
        puts("---------------------------------------------------------------------");
        ListarOrdemCrescente(abp->direita, i);
    }
}

//Funcao para imprimir na consola todos os registos de uma arvore binaria de procura por ordem decrescente
void ListarOrdemDecrescente(ABP abp, int i)
{
    if (abp != NULL)
    {
        //Incrementar nivel
        i++;
        //Percorrer arvore recursivamente
        ListarOrdemDecrescente(abp->direita, i);
        printf("Nivel: %d\tCenario: %d     Velocidade: %d (m/s)     Tempo: %d (s)\n", i, abp->codigo, abp->velocidade, abp->tempo);
        puts("---------------------------------------------------------------------");
        ListarOrdemDecrescente(abp->esquerda, i);
    }
}

//Funcao para alterar dados de um registo de uma arvore binaria de procura
int AlterarCenario(ABP abp, int codigo, int velocidade, int tempo)
{
    //Verificar se arvore não está vazia
    if (abp != NULL)
    {
        //Cenario encontrado
        if (abp->codigo == codigo)
        {
            //Alterar valores do cenario
            //Só altera se o valor for positivo ou 0
            if (velocidade >= 0)
                abp->velocidade = velocidade;
            if (tempo >= 0)
                abp->tempo = tempo;

            return 1;
        }

        //Percorrer arvore recursivamente
        AlterarCenario(abp->esquerda, codigo, velocidade, tempo);
        AlterarCenario(abp->direita, codigo, velocidade, tempo);
    }

    return 0;
}

//Funcao para remover um registo de uma arvore binaria de procura
ABP RemoverCenario(ABP abp, int codigo)
{
    ABP temp;

    //Verificar se a arvore está vazia
    if (abp == NULL)
        return NULL;

    //Codigo está na sub arvore esquerda
    if (codigo < abp->codigo)
        abp->esquerda = RemoverCenario(abp->esquerda, codigo);
    //Codigo está na sub arvore direita
    else if (codigo > abp->codigo)
        abp->direita = RemoverCenario(abp->direita, codigo);
    else
    {
        //Registo é uma folha
        if (abp->esquerda == NULL && abp->direita == NULL)
        {
            free(abp);
            abp = NULL;
        }
        //Registo só tem uma sub arvore à direita
        else if (abp->esquerda == NULL)
        {
            temp = abp;
            abp = abp->direita;
            free(temp);
        }
        //Registo só tem uma sub arvore à esquerda
        else if (abp->direita == NULL)
        {
            temp = abp;
            abp = abp->esquerda;
            free(temp);
        }
        //Registo tem 2 sub arvores
        else
        {
            temp = ArvoreMaisEsquerda(abp->direita);                   //Encontrar o valor mais baixo da sub arvore direita
            abp->codigo = temp->codigo;                                //Copiar registo
            abp->direita = RemoverCenario(abp->direita, temp->codigo); //Remover registo duplicado
        }
    }

    //Retornar raiz
    return abp;
}

/*
Funcao para encontrar o registo mais à esquerda de uma arvore binaria de procura
Funcao auxiliar à funcao RemoverCenario
*/
ABP ArvoreMaisEsquerda(ABP abp)
{
    //Verificar nulidade e se existe registos à esquerda
    if (abp && abp->esquerda)
        return ArvoreMaisEsquerda(abp->esquerda);
    else
        return abp;
}

//Funcao para fazer a simulação de um cenario, apresentando os valores através de tabelas
void SimularCenario(ABP abp, int codigo)
{
    //Variaveis
    int velocidade, tempo;
    ABP temp;

    //Inicializar variaveis
    temp = PesquisarCenario(abp, codigo);
    if (temp != NULL)
    {
        velocidade = temp->velocidade;
        tempo = temp->tempo;

        //Imprimir tabela na consola
        puts(" ____________________________");
        printf("| Tempo (s)|  Distancia (m/s)|\n");
        puts("|__________|_________________|");

        for (int i = 0; i <= tempo; i++)
        {
            printf("|%10d|%17d|\n", i, i * velocidade);
            puts("|__________|_________________|");
        }

        //Imprimir valores maximos na consola
        printf("\nTempo total: %d (s)\n", tempo);
        printf("Velocidade maxima: %d (m/s)\n", velocidade);
        printf("Distancia percorrida: %d (m)\n", tempo * velocidade);
    }
    else
        printf("Nao existe nenhum cenario com codigo = %d\n", codigo);
}

//Funcao para guardar uma arvore binaria de procura num ficheiro de texto
int GuardarArvore(ABP abp, char path[])
{
    FILE *fp;
    fp = fopen(path, "w");

    if (fp != NULL)
    {
        GuardarArvoreAux(abp, fp);
        fclose(fp);
        return 1;
    }

    return 0;
}

//Funcao auxiliar de GuardarArvore()
int GuardarArvoreAux(ABP abp, FILE *fp)
{
    if (abp != NULL)
    {
        //Imprimir dados do registo num ficheiro de texto
        fprintf(fp, "%d %d %d\n", abp->codigo, abp->velocidade, abp->tempo);
        //Percorrer a arvore recursivamente
        GuardarArvoreAux(abp->esquerda, fp);
        GuardarArvoreAux(abp->direita, fp);
    }
}

//Funcao para ler uma lista de um ficheiro de texto
int LerFicheiro(ABP *abp, char path[])
{
    //Variaveis
    int codigo, velocidade, tempo, resultado;
    ABP temp;

    FILE *fp = fopen(path, "r");

    if (fp != NULL)
    {
        while (!feof(fp))
        {
            resultado = fscanf(fp, "%d %d %d\n", &codigo, &velocidade, &tempo);
            if (resultado == 3)
            {
                //Só adicionar cenários que ainda nao existam
                temp = PesquisarCenario(*abp, codigo);
                if (temp == NULL)
                    *abp = InserirCenario(*abp, codigo, velocidade, tempo);
            }
        }
        return 1;
    }
    else
        return (0);
}
