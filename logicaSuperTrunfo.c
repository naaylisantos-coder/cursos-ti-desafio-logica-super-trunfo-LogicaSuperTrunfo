#include <stdio.h>

typedef struct {
    char estado[20]; // ex.: "SP"
    char codigo[10]; // ex.: "A01"
    char cidade[50]; // ex.: "São Paulo"
    int populacao; // habitantes
    float area; // km^2
    float pib; // use uma unidade fixa (ex.: milhões)
    int pontos_turisticos;
    float densidade; // calculado
    float pib_per_capita; // calculado
} Carta;

typedef enum {
    POPULACAO,
    AREA,
    PIB_TOTAL,
    DENSIDADE,
    PIB_PER_CAPITA
} Atributo;

// >>> ALTERE AQUI O ATRIBUTO ESCOLHIDO (apenas UM) <<<
const Atributo ATRIBUTO = POPULACAO; // troque para AREA, PIB_TOTAL, DENSIDADE ou PIB_PER_CAPITA

void lerLinha(const char *rotulo, char *buf, int max) {
    printf("%s", rotulo);
    // lê até a quebra de linha (inclui espaços)
    scanf(" %[^\\n]%*c", buf); // lê até '\n' e consome o '\n'
}

void lerCarta(Carta *c, int idx) {
    printf("\n=== Cadastro da Carta %d ===\n", idx);

    lerLinha("Estado: ", c->estado, sizeof(c->estado));
    lerLinha("Codigo: ", c->codigo, sizeof(c->codigo));
    lerLinha("Cidade: ", c->cidade, sizeof(c->cidade));

    printf("Populacao (inteiro): ");
    scanf(" %d", &c->populacao);

    printf("Area (float): ");
    scanf(" %f", &c->area);

    printf("PIB (float - use mesma unidade nas duas cartas): ");
    scanf(" %f", &c->pib);

    printf("Numero de pontos turisticos (inteiro): ");
    scanf(" %d%*c", &c->pontos_turisticos); // consome '\n' ao final

    // Cálculos derivados
    c->densidade = (c->area > 0.0f) ? (c->populacao / c->area) : 0.0f;
    c->pib_per_capita = (c->populacao > 0) ? (c->pib / c->populacao) : 0.0f;
}

float valorDoAtributo(const Carta *c, Atributo a) {
    switch (a) {
        case POPULACAO: return (float)c->populacao;
        case AREA: return c->area;
        case PIB_TOTAL: return c->pib;
        case DENSIDADE: return c->densidade;
        case PIB_PER_CAPITA:return c->pib_per_capita;
        default: return 0.0f;
    }
}

const char* nomeAtributo(Atributo a) {
    switch (a) {
        case POPULACAO: return "Populacao";
        case AREA: return "Area";
        case PIB_TOTAL: return "PIB";
        case DENSIDADE: return "Densidade Populacional";
        case PIB_PER_CAPITA: return "PIB per capita";
        default: return "Atributo";
    }
}

int main(void) {
    Carta c1, c2;

    lerCarta(&c1, 1);
    lerCarta(&c2, 2);

    float v1 = valorDoAtributo(&c1, ATRIBUTO);
    float v2 = valorDoAtributo(&c2, ATRIBUTO);

    printf("\n=== Comparacao de Cartas (Atributo: %s) ===\n", nomeAtributo(ATRIBUTO));
    printf("Carta 1 - %s (%s) | %s: %.2f\n", c1.cidade, c1.estado, nomeAtributo(ATRIBUTO), v1);
    printf("Carta 2 - %s (%s) | %s: %.2f\n", c2.cidade, c2.estado, nomeAtributo(ATRIBUTO), v2);

    int vencedora = 0; // 1 = carta1, 2 = carta2, 0 = empate

    // Regra: para DENSIDADE vence o MENOR; para os outros vence o MAIOR
    if (ATRIBUTO == DENSIDADE) {
        if (v1 < v2) vencedora = 1;
        else if (v2 < v1) vencedora = 2;
    } else {
        if (v1 > v2) vencedora = 1;
        else if (v2 > v1) vencedora = 2;
    }

    if (vencedora == 1) {
        printf("Resultado: Carta 1 (%s) venceu!\n", c1.cidade);
    } else if (vencedora == 2) {
        printf("Resultado: Carta 2 (%s) venceu!\n", c2.cidade);
    } else {
        printf("Resultado: Empate!\n");
    }

    return 0;
}
