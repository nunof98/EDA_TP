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
    struct registo *anterior;
    struct registo *seguinte;
} * Lista;

//Protótipos
int Menu();
int InserirOrdemCrescente(Lista *endereco, int codigo, int velocidade, int tempo);
Lista PesquisarCenario(Lista inicio, int codigo);
void Listar(Lista endereco);
void ListarInversa(Lista inicio);
int AlterarCenario(Lista *endereco, int codigo, int velocidade, int tempo);
int RemoverCenario(Lista *inicio, int codigo);
void SimularCenario(Lista inicio, int codigo);
int GuardarLista(Lista inicio, char path[]);
int LerFicheiro(Lista *inicio, char path[]);

int main()
{
    //Variaveis
    int codigo, velocidade, tempo, opcaoAlterar, opcaoMenu;
    char path[STRING_SIZE] = "";
    char resposta;
    Lista lista = NULL;
    Lista temp;

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
            temp = PesquisarCenario(lista, codigo);
            if (temp == NULL)
            {
                //Verificar se o cenario foi inserido
                if (InserirOrdemCrescente(&lista, codigo, velocidade, tempo))
                    puts("Cenerario Inserido!");
                else
                    puts("O cenerario nao foi inserido!");
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
            temp = PesquisarCenario(lista, codigo);
            if (temp == NULL)
                puts("here");
            if (temp != NULL)
            {
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
            //Fazer print da lista
            Listar(lista);
            break;
#pragma endregion Listar Cenarios Crescente

        case 4:
#pragma region Listar Cenarios Decrescente
            puts("\n=====Listar cenarios por ordem decrescente=====");
            //Fazer print da lista inversa
            ListarInversa(lista);
            break;
#pragma endregion Listar Cenarios Decrescente

        case 5:
#pragma region Alterar Cenario
            puts("\n=====Alterar cenario=====");
            //Pedir ao utilizar o codigo do cenario
            printf("Codigo do cenario: ");
            scanf("%d", &codigo);
            temp = PesquisarCenario(lista, codigo);
            if (temp != NULL)
            {
                //Imprimir dados do cenario
                puts("Cenario Encontrado:");
                printf("Codigo: %d; ", temp->codigo);
                printf("Velocidade: %d (m/s); ", temp->velocidade);
                printf("Tempo: %d (s);\n", temp->tempo);

                //Perguntar se o utilizador quer mudar algum dado
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
                    if (AlterarCenario(&lista, codigo, velocidade, tempo))
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

            if (RemoverCenario(&lista, codigo))
                puts("Cenerario Removido!");
            else
                puts("O cenerario nao foi removido!");

            break;
#pragma endregion Remover Cenario

        case 7:
#pragma region Simulacao de Cenario
            puts("\n=====Simulacao de cenario=====");
            //Pedir ao utilizar o codigo do cenario
            printf("Codigo do cenario: ");
            scanf("%d", &codigo);
            SimularCenario(lista, codigo);
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
                puts("Escreva o path do ficheiro: ");
                scanf("%s", path);
                strcat(path, ".txt");
            }
            //Default path
            else
                strcpy(path, "ListaDuplamenteLigadaCircular.txt");

            if (GuardarLista(lista, path))
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
                strcpy(path, "ListaDuplamenteLigadaCircular.txt");

            if (LerFicheiro(&lista, path))
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

//Funcao para inserir registos numa lista duplamente ligada circular, por ordem crescente
int InserirOrdemCrescente(Lista *inicio, int codigo, int velocidade, int tempo)
{
    //Alocar memória
    Lista novo = (Lista)malloc(sizeof(struct registo));
    Lista atual = *inicio;

    //Preencher novo registo
    if (novo != NULL)
    {
        novo->codigo = codigo;
        novo->velocidade = velocidade;
        novo->tempo = tempo;

        //Inserir numa lista vazia
        if (*inicio == NULL)
        {
            novo->seguinte = novo;
            novo->anterior = novo;
            *inicio = novo;
            return 1;
        }
        //Inserir novo inicio
        else if ((*inicio)->codigo > novo->codigo)
        {
            ((*inicio)->anterior)->seguinte = novo;
            novo->anterior = (*inicio)->anterior;
            novo->seguinte = *inicio;
            (*inicio)->anterior = novo;
            *inicio = novo;
            return 1;
        }
        else
        {
            while (atual->codigo < codigo)
            {
                //Inserir no fim da lista
                if (atual->seguinte == *inicio)
                {
                    novo->seguinte = *inicio;
                    novo->anterior = atual;
                    atual->seguinte = novo;
                    (*inicio)->anterior = novo;
                    return 1;
                }
                else
                    atual = atual->seguinte;
            }

            //Inserir no meio da lista
            atual->anterior->seguinte = novo;
            novo->anterior = atual->anterior;
            atual->anterior = novo;
            novo->seguinte = atual;
            return 1;
        }
    }

    return 0;
}

//Funcao para encontrar um registo de uma lista ligada circular
Lista PesquisarCenario(Lista inicio, int codigo)
{
    //Verificar se lista está vazia
    if (inicio != NULL)
    {
        Lista temp = inicio;
        //Ciclo para percorrer a lista
        do
        {
            if (temp->codigo == codigo)
                return temp;

            temp = temp->seguinte;
        } while (temp != inicio);
        puts("");
    }

    return NULL;
}

/*
Funcao para imprimir na consola todos os registos de uma lista ligada circular
a comecar no registo inicial e com direcao para a direita.
*/
void Listar(Lista inicio)
{
    //Variaveis
    int i = 0;

    //Verificar se lista está vazia
    if (inicio != NULL)
    {
        Lista temp = inicio;
        puts("");
        //Ciclo para percorrer a lista
        do
        {
            i++;
            //Print código na consola
            printf("%d\tCenario: %d     Velocidade: %d (m/s)     Tempo: %d (s)\n", i, temp->codigo, temp->velocidade, temp->tempo);
            puts("--------------------------------------------------------------");
            temp = temp->seguinte;
        } while (temp != inicio);
        puts("");
    }
    else
        puts("Lista esta vazia\n");
}

/*
Funcao para imprimir na consola todos os registos de uma lista ligada circular
a comecar no registo inicial e com direcao para a esquerda.
*/
void ListarInversa(Lista inicio)
{
    //Variaveis
    int i = 0;

    //Verificar se lista está vazia
    if (inicio != NULL)
    {
        Lista temp = inicio->anterior;
        puts("");
        //Ciclo para percorrer a lista
        do
        {
            i++;
            //Print código na consola
            printf("%d\tCenario: %d     Velocidade: %d (m/s)    Tempo: %d (s)\n", i, temp->codigo, temp->velocidade, temp->tempo);
            puts("--------------------------------------------------------------");
            temp = temp->anterior;
        } while (temp != inicio->anterior);
        puts("");
    }
    else
        puts("Lista esta vazia\n");
}

//Funcao para alterar dados de um registo de uma lista ligada circular
int AlterarCenario(Lista *endereco, int codigo, int velocidade, int tempo)
{
    //Verificar se lista está vazia
    if (*endereco != NULL)
    {
        Lista inicio = *endereco;
        //Ciclo para percorrer a lista
        do
        {
            if ((*endereco)->codigo == codigo)
            {
                //Alterar valores do cenario
                //Só altera se o valor for positivo ou 0
                if (velocidade >= 0)
                    (*endereco)->velocidade = velocidade;
                if (tempo >= 0)
                    (*endereco)->tempo = tempo;

                //Voltar ao inicio da lista
                *endereco = inicio;
                return 1;
            }

            *endereco = (*endereco)->seguinte;
        } while (*endereco != inicio);
        puts("");
    }

    return 0;
}

//Funcao para remover um registo de uma lista duplamente ligada circular
int RemoverCenario(Lista *inicio, int codigo)
{
    //Variaveis
    Lista enderecoAtual = *inicio, enderecoAnterior = NULL;

    //Verificar se a lista está vazia
    if (*inicio == NULL)
        return 0;

    //Ciclo para percorrer lista
    while (enderecoAtual->codigo != codigo)
    {
        //Codigo não existe
        if (enderecoAtual->seguinte == *inicio)
        {
            printf("Nao existe nenhum cenario com codigo = %d\n", codigo);
            return 0;
        }

        enderecoAnterior = enderecoAtual;
        enderecoAtual = enderecoAtual->seguinte;
    }

    //Se a lista só tiver um registo
    if (enderecoAtual->seguinte == *inicio && enderecoAnterior == NULL)
    {
        *inicio = NULL;
        free(enderecoAtual);
        return 1;
    }
    //Se a lista tiver mais do que um registo
    else
    {
        //Verificar se é o primeiro registo
        if (enderecoAtual == *inicio)
        {
            //Colocar enderecoAnterior como último registo da lista
            enderecoAnterior = (*inicio)->anterior;
            //Atualizar inicio da lista
            *inicio = (*inicio)->seguinte;
            //Atualizar apontadores
            enderecoAnterior->seguinte = *inicio;
            (*inicio)->anterior = enderecoAnterior;
            free(enderecoAtual);
            return 1;
        }
        //Verificar se é o último registo
        else if (enderecoAtual->seguinte == *inicio)
        {
            //Atualizar apontadores
            enderecoAnterior->seguinte = *inicio;
            (*inicio)->anterior = enderecoAnterior;
            free(enderecoAtual);
            return 1;
        }
        else
        {
            //Variavel temporária
            Lista temp = enderecoAtual->seguinte;
            //Atualizar apontadores
            enderecoAnterior->seguinte = temp;
            temp->anterior = enderecoAnterior;
            free(enderecoAtual);
            return 1;
        }
    }

    return 0;
}

//Funcao para fazer a simulação de um cenario, apresentando os valores através de tabelas
void SimularCenario(Lista inicio, int codigo)
{
    //Variaveis
    int velocidade, tempo;
    Lista temp;

    //Inicializar variaveis
    temp = PesquisarCenario(inicio, codigo);
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

//Funcao para guardar uma lista num ficheiro de texto
int GuardarLista(Lista inicio, char path[])
{
    FILE *fp = fopen(path, "w");

    if (fp != NULL)
    {
        if (inicio != NULL)
        {
            Lista temp = inicio;
            //Ciclo para percorrer a lista
            do
            {
                //Escrever dados da lista no ficheiro
                fprintf(fp, "%d %d %d\n", temp->codigo, temp->velocidade, temp->tempo);

                temp = temp->seguinte;
            } while (temp != inicio);
        }

        fclose(fp);
        return 1;
    }
    else
        return 0;
}

//Funcao para ler uma lista de um ficheiro de texto
int LerFicheiro(Lista *inicio, char path[])
{
    //Variaveis
    int codigo, velocidade, tempo, resultado;
    Lista temp;

    FILE *fp = fopen(path, "r");

    if (fp != NULL)
    {
        while (!feof(fp))
        {
            resultado = fscanf(fp, "%d %d %d\n", &codigo, &velocidade, &tempo);
            if (resultado == 3)
            {
                //Só adicionar cenários que ainda nao existam
                temp = PesquisarCenario(*inicio, codigo);
                if (temp == NULL)
                    InserirOrdemCrescente(inicio, codigo, velocidade, tempo);
            }
        }
        return 1;
    }
    else
        return 0;
}
