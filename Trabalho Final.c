#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char proprietario[76];
    char modelo[40];
    char combustivel[20];
    char cor[15];
    int ano;
    char chassi[21];
    char placa[8];
} Carro;

typedef struct Node {
    Carro data;
    struct Node* next;
} Node;

void displayProprietarios2010Diesel(Node* prox) {
    printf("carros do ano de 2010 ou posterior e que sao movidos a diesel:\n");
    while (prox != NULL) {
        if (prox->data.ano >= 2010 && strcmp(prox->data.combustivel, "diesel") == 0) {
            printf("%s\n", prox->data.proprietario);
        }
        prox = prox->next;
    }
}

void insertCarro(Node** prox, Carro Carro) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = Carro;
    newNode->next = *prox;
    *prox = newNode;
}

void displayModeloCorPlacasVogalSomaPar(Node* prox) {
    printf("Modelo e cor dos Carros cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numericos fornece um numero par:\n");
    while (prox != NULL) {
        if (strchr("aeiouAEIOU", toupper(prox->data.placa[1])) != NULL) {
            int somaNumeros = 0;
            for (int i = 0; i < 7; i++) {
                if (isdigit(prox->data.placa[i])) {
                    somaNumeros += prox->data.placa[i] - '0';
                }
            }
            if (somaNumeros % 2 == 0) {
                printf("Modelo: %s, Cor: %s\n", prox->data.modelo, prox->data.cor);
            }
        }
        prox = prox->next;
    }
}


void displayPlacasJ(Node* prox) {
    printf("Placas que comecam com 'J' e terminam com 0, 2, 4 ou 7, com seus respectivos proprietarios:\n");
    while (prox != NULL) {
        if (prox->data.placa[0] == 'J' && (prox->data.placa[7] == '0' || prox->data.placa[7] == '2' ||
                                           prox->data.placa[7] == '4' || prox->data.placa[7] == '7')) {
            printf("Placa: %s, Proprietario: %s\n", prox->data.placa, prox->data.proprietario);
        }
        prox = prox->next;
    }
}

void changeProprietarioWithoutZero(Node** prox, char chassi[17], char novoProprietario[100]) {
    Node* current = *prox;
    while (current != NULL) {
        if (strcmp(current->data.chassi, chassi) == 0 && strpbrk(current->data.placa, "0") == NULL) {
            strcpy(current->data.proprietario, novoProprietario);
            printf("Proprietario atualizado com sucesso!\n");
            return;
        }
        current = current->next;
    }
    printf("Carro nao encontrado ou placa possui digito zero.\n");
}

void freeListMemory(Node* prox) {
    while (prox != NULL) {
        Node* temp = prox;
        prox = prox->next;
        free(temp);
    }
}

int main() {
    Node* vehicleList = NULL;

    int numCarros;
    printf("Quantos Carros deseja cadastrar? ");
    scanf("%d", &numCarros);

    for (int i = 0; i < numCarros; i++) {
        Carro novoCarro;
        printf("\nInforme os dados do Carro %d:\n", i + 1);
        printf("Proprietario: ");
        scanf(" %[^\n]s", novoCarro.proprietario);
        printf("Cor");
        printf("Combustivel diesel, acool ou gasolina");
        scanf("%s", novoCarro.combustivel);
        scanf("%s", novoCarro.cor);
        printf("Modelo");
        scanf("%s", novoCarro.modelo);
        printf("Ano");
        scanf("%d", &novoCarro.ano);
        printf("Placa");
        scanf("%s", novoCarro.placa);
        printf("Chassi");
        scanf("%s", novoCarro.chassi);

        insertCarro(&vehicleList, novoCarro);
    }

    displayProprietarios2010Diesel(vehicleList);
    displayPlacasJ(vehicleList);
    displayModeloCorPlacasVogalSomaPar(vehicleList);

    char chassiTroca[17];
    char novoProprietario[100];
    printf("\nInforme o chassi para troca de proprietario: ");
    scanf("%s", chassiTroca);
    printf("Informe o novo proprietario: ");
    scanf(" %[^\n]s", novoProprietario);
    changeProprietarioWithoutZero(&vehicleList, chassiTroca, novoProprietario);

    freeListMemory(vehicleList);

    return 0;
}
