/*
CCP230 - Projeto Exchange de Criptomoedas 

ARQUIVOS DE TEXTO:
{
investidores.txt  -> uma linha por investidor:
nome_sem_espacos cpf senha reais btc eth rip
    ex.: Gabriela 12345678900 123456 580.00 0.0158 1.03 200.35

cotacoes.txt      -> uma linha so:
btc eth rip
    ex.: 350000.00 16108.00 2.57

extrato_<cpf>.txt -> uma linha por operacao (append, usar "a"):
dia mes ano hora min sinal valor moeda cotacao taxa reais btc eth rip
    ex.: 1 10 2026 12 50 + 500.00 REAL 0.0 0.00 500.00 0.0 0.0 0.0
}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_INV 20

/* taxas de compra e venda em porcentagem */
#define TX_COMPRA_BTC 2.0
#define TX_VENDA_BTC  3.0
#define TX_COMPRA_ETH 1.0
#define TX_VENDA_ETH  2.0
#define TX_COMPRA_RIP 1.0
#define TX_VENDA_RIP  1.0

struct investidor {
    char nome[50];
    char cpf[12];      /* 11 digitos + '\0' */
    int senha;         /* 6 digitos */
    double reais;
    double btc;
    double eth;
    double rip;
};

/* ---------- variaveis globais simples: cotacoes atuais ---------- */
double cot_btc, cot_eth, cot_rip;

/* ---------- prototipos ---------- */
int  carregar_investidores(struct investidor lista[]);
void salvar_investidores(struct investidor lista[], int qtd);
void ler_cotacoes(void);
void salvar_cotacoes(void);

int  fazer_login(struct investidor lista[], int qtd);   /* devolve indice ou -1 */
int  pedir_senha(struct investidor *inv);               /* 1 = ok, 0 = errada   */
void registrar_extrato(struct investidor *inv, char sinal, double valor,
                       char moeda[], double cotacao, double taxa);

void consultar_saldo(struct investidor *inv);
void consultar_extrato(struct investidor *inv);
void depositar(struct investidor *inv);
void sacar(struct investidor *inv);
void comprar(struct investidor *inv);
void vender(struct investidor *inv);
void atualizar_cotacao(void);

/* =====================================================================
 * EXEMPLO PRONTO 1: ler um arquivo com fscanf e preencher um vetor de structs
 * (estude este padrao: voce vai repetir ele em outras funcoes)
 * ===================================================================== */
int carregar_investidores(struct investidor lista[])
{
    FILE *arq = fopen("investidores.txt", "r");
    int qtd = 0;

    if (arq == NULL) {
        printf("Erro: nao foi possivel abrir investidores.txt\n");
        return 0;
    }
    /* fscanf devolve quantos campos leu; 7 = linha completa */
    while (qtd < MAX_INV &&
           fscanf(arq, "%49s %11s %d %lf %lf %lf %lf",
                  lista[qtd].nome, lista[qtd].cpf, &lista[qtd].senha,
                  &lista[qtd].reais, &lista[qtd].btc,
                  &lista[qtd].eth, &lista[qtd].rip) == 7) {
        qtd++;
    }
    fclose(arq);
    return qtd;
}


/*Ler cotações */
 
void ler_cotacoes(void)
{
    FILE *arq = fopen("cotacoes.txt", "r");

    if (arq == NULL) {
        /* primeira execucao: valores iniciais */
        cot_btc = 350000.00;
        cot_eth = 16108.00;
        cot_rip = 2.57;
        return;
    }
    fscanf(arq, "%lf %lf %lf", &cot_btc, &cot_eth, &cot_rip);
    fclose(arq);
}


/* TODO: reescrever investidores.txt inteiro ("w") com os dados atuais da lista.
 * Chame depois de QUALQUER operacao que mude saldo (deposito, saque, compra, venda). */
void salvar_investidores(struct investidor lista[], int qtd)
{
    /* fopen "w" -> for i < qtd -> fprintf com o mesmo formato do fscanf acima */
}

/* TODO: gravar cot_btc, cot_eth e cot_rip em cotacoes.txt ("w") */
void salvar_cotacoes(void)
{
}

/* TODO: pedir CPF e senha; percorrer a lista comparando com strcmp (CPF) e ==
 * (senha). Devolver o indice do investidor ou -1. Limite de tentativas: 3. */
int fazer_login(struct investidor lista[], int qtd)
{
    return -1;
}

/* TODO: pedir a senha de 6 digitos e comparar com inv->senha (use ->).
 * Devolver 1 se correta, 0 se errada. */
int pedir_senha(struct investidor *inv)
{
    return 0;
}

/* abrir "extrato_<cpf>.txt" em modo "a" (monte o nome com sprintf),
 * pegar data/hora com time() + localtime() e gravar uma linha no formato do
 * cabecalho. Os saldos gravados sao os de DEPOIS da operacao.
 * sinal: '+' ou '-' ; moeda: "REAL", "BTC", "ETH" ou "XRP". */
void registrar_extrato(struct investidor *inv, char sinal, double valor,
                       char moeda[], double cotacao, double taxa)
{
}

/* pedir senha; se ok, mostrar Nome, CPF, Reais, Bitcoin, Ethereum, Ripple
 * (inv->reais, inv->btc, inv->eth, inv->rip). */
void consultar_saldo(struct investidor *inv)
{
}

/* TODO: pedir senha; se ok, abrir o extrato em "r" e imprimir linha a linha
 * (fscanf dos 14 campos e printf formatado, em um while). */
void consultar_extrato(struct investidor *inv)
{
}

/* TODO: pedir valor (> 0), somar em inv->reais, registrar no extrato
 * (sinal '+', moeda "REAL", cotacao 0.0, taxa 0.0), mostrar saldos. */
void depositar(struct investidor *inv)
{
}

/* TODO: pedir valor; se valor > inv->reais, recusar (saldo nao pode ficar
 * negativo). Senao subtrair, registrar (sinal '-'), mostrar saldos. */
void sacar(struct investidor *inv)
{
}

/* TODO: pedir senha; mostrar cotacoes; escolher moeda (1=btc 2=eth 3=rip)
 * com switch; pedir quanto quer gastar em reais.
 * Olhando o exemplo do enunciado (100 reais -> REAL cai 101): a taxa e
 * calculada sobre o valor e COBRADA POR CIMA:
 *     taxa  = valor * percentual / 100;
 *     total = valor + taxa;          -> precisa ser <= inv->reais
 *     qtd   = valor / cotacao;       -> soma em btc/eth/rip
 * Registrar no extrato e mostrar saldos. */
void comprar(struct investidor *inv)
{
}

/* TODO: parecido com comprar, mas ao contrario: pedir quanto da moeda quer
 * vender (nao pode passar do que tem), valor = qtd * cotacao, taxa de venda
 * descontada do valor que volta em reais. */
void vender(struct investidor *inv)
{
}

/* TODO: variar cada cotacao entre -5% e +5% com rand().
 * Dica: variacao = ((rand() % 1001) / 1000.0) * 0.10 - 0.05;   (de -0.05 a +0.05)
 *       cot_btc = cot_btc * (1 + variacao);
 * Faca uma variacao DIFERENTE para cada moeda e chame srand(time(NULL)) uma
 * unica vez no main. Depois chame salvar_cotacoes(). */
void atualizar_cotacao(void)
{
}

/* =====================================================================
 * main: menu em laco (do/while + switch). Ja esta montado, so complete.
 * ===================================================================== */
int main(void)
{
    struct investidor lista[MAX_INV];
    int qtd, pos, opcao;

    srand(time(NULL));
    qtd = carregar_investidores(lista);
    ler_cotacoes();

    pos = fazer_login(lista, qtd);
    if (pos == -1) {
        printf("Login invalido.\n");
        return 0;
    }

    do {
        printf("\n1. Consultar saldo\n2. Consultar extrato\n3. Depositar\n"
               "4. Sacar\n5. Comprar criptomoedas\n6. Vender criptomoedas\n"
               "7. Atualizar cotacao\n8. Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: consultar_saldo(&lista[pos]);  break;
            case 2: consultar_extrato(&lista[pos]); break;
            case 3: depositar(&lista[pos]);        break;
            case 4: sacar(&lista[pos]);            break;
            case 5: comprar(&lista[pos]);          break;
            case 6: vender(&lista[pos]);           break;
            case 7: atualizar_cotacao();           break;
            case 8: printf("Ate logo!\n");         break;
            default: printf("Opcao invalida.\n");
        }
        /* TODO: salvar_investidores(lista, qtd); depois de cada operacao */
    } while (opcao != 8);

    return 0;
}
