#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100
#define MAX_REG 10

typedef struct {
    char data[TAM];
    float valor;
    char tipo[TAM];
    char nome[TAM];
} informacoes_financeiras;

typedef struct {
    char titular[TAM];
    informacoes_financeiras investimentos[MAX_REG];
    int qtd_investimentos;
} informacoes_conta;

void imprimir(informacoes_conta conta) {
    printf("\nTitular: %s\n", conta.titular);

    for (int i = 0; i < conta.qtd_investimentos; i++) {
        printf("\nInvestimento [%d]", i + 1);
        printf("\n\tData: %s", conta.investimentos[i].data);
        printf("\tValor: R$ %.2f", conta.investimentos[i].valor);
        printf("\n\tTipo: %s", conta.investimentos[i].tipo);
        printf("\tNome: %s", conta.investimentos[i].nome);
    }
}

void ordenarPorValor(informacoes_conta *conta) {
    for (int i = 0; i < conta->qtd_investimentos - 1; i++) {
        for (int j = i + 1; j < conta->qtd_investimentos; j++) {
            if (conta->investimentos[i].valor > conta->investimentos[j].valor) {
                informacoes_financeiras temp = conta->investimentos[i];
                conta->investimentos[i] = conta->investimentos[j];
                conta->investimentos[j] = temp;
            }
        }
    }
}

void ordenarPorData(informacoes_conta *conta) {
    for (int i = 0; i < conta->qtd_investimentos - 1; i++) {
        for (int j = i + 1; j < conta->qtd_investimentos; j++) {
            if (strcmp(conta->investimentos[i].data, conta->investimentos[j].data) > 0) {
                informacoes_financeiras temp = conta->investimentos[i];
                conta->investimentos[i] = conta->investimentos[j];
                conta->investimentos[j] = temp;
            }
        }
    }
}

void ordenarPorTipo(informacoes_conta *conta) {
    for (int i = 0; i < conta->qtd_investimentos - 1; i++) {
        for (int j = i + 1; j < conta->qtd_investimentos; j++) {
            if (strcmp(conta->investimentos[i].tipo, conta->investimentos[j].tipo) > 0) {
                informacoes_financeiras temp = conta->investimentos[i];
                conta->investimentos[i] = conta->investimentos[j];
                conta->investimentos[j] = temp;
            }
        }
    }
}

void agruparPorTipoEOrdenar(informacoes_conta *conta, int ordenarPorValorFlag) {

    ordenarPorTipo(conta);


    int inicio = 0;
    while (inicio < conta->qtd_investimentos) {
        int fim = inicio + 1;
        while (fim < conta->qtd_investimentos &&
               strcmp(conta->investimentos[inicio].tipo, conta->investimentos[fim].tipo) == 0) {
            fim++;
        }

        for (int i = inicio; i < fim - 1; i++) {
            for (int j = i + 1; j < fim; j++) {
                int comparar;
                if (ordenarPorValorFlag)
                    comparar = conta->investimentos[i].valor > conta->investimentos[j].valor;
                else
                    comparar = strcmp(conta->investimentos[i].data, conta->investimentos[j].data) > 0;

                if (comparar) {
                    informacoes_financeiras temp = conta->investimentos[i];
                    conta->investimentos[i] = conta->investimentos[j];
                    conta->investimentos[j] = temp;
                }
            }
        }

        inicio = fim;
    }
}

void menuOrdenacao(informacoes_conta *conta) {
    int opcao;
    printf("\nEscolha a forma de ordenação:\n");
    printf("1. Ordenar por Data\n");
    printf("2. Ordenar por Tipo\n");
    printf("3. Ordenar por Valor\n");
    printf("4. Agrupar por Tipo e Ordenar por Data\n");
    printf("5. Agrupar por Tipo e Ordenar por Valor\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar(); 

    switch (opcao) {
        case 1:
            ordenarPorData(conta);
            break;
        case 2:
            ordenarPorTipo(conta);
            break;
        case 3:
            ordenarPorValor(conta);
            break;
        case 4:
            agruparPorTipoEOrdenar(conta, 0); 
            break;
        case 5:
            agruparPorTipoEOrdenar(conta, 1); 
            break;
        default:
            printf("Opção inválida.\n");
            return;
    }

    imprimir(*conta);
}


int main() {
    informacoes_conta conta;

    printf("Digite o nome do titular da conta: ");
    fgets(conta.titular, TAM, stdin);

    printf("Quantos investimentos deseja cadastrar (max %d)? ", MAX_REG);
    scanf("%d", &conta.qtd_investimentos);
    getchar();

    if (conta.qtd_investimentos > MAX_REG) {
        printf("Erro: número máximo de investimentos excedido.\n");
        return 1;
    }

    for (int i = 0; i < conta.qtd_investimentos; i++) {
        printf("\n--- Investimento %d ---\n", i + 1);

        printf("Digite a data: ");
        fgets(conta.investimentos[i].data, TAM, stdin);

        printf("Digite o valor: ");
        scanf("%f", &conta.investimentos[i].valor);
        getchar();

        printf("Digite o tipo do investimento: ");
        fgets(conta.investimentos[i].tipo, TAM, stdin);

        printf("Digite o nome do papel/ativo: ");
        fgets(conta.investimentos[i].nome, TAM, stdin);
    }

    imprimir(conta);
    menuOrdenacao(&conta);
    
}
