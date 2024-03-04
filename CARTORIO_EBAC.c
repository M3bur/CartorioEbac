#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para exibir mensagens de erro
void exibirErro(const char *mensagem) {
    printf("Erro: %s\n", mensagem);
    system("pause");
}

// Função para solicitar uma entrada de string não vazia
void obterEntradaNaoVazia(const char *mensagem, char *destino, int tamanho) {
    do {
        printf("%s", mensagem);
        fgets(destino, tamanho, stdin);
        destino[strcspn(destino, "\n")] = '\0';
    } while (strlen(destino) == 0);
}

// Função para realizar o registro de informações
void registro() {
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    // Solicitação do CPF ao usuário
    obterEntradaNaoVazia("Digite o CPF a ser cadastrado: ", cpf, sizeof(cpf));

    // Copiando o CPF para o nome do arquivo
    strcpy(arquivo, cpf);

    // Criação do arquivo no modo de escrita ("w")
    FILE *file = fopen(arquivo, "w");

    if (file == NULL) {
        exibirErro("Erro ao abrir o arquivo.");
        return;
    }

    // Salva o CPF no arquivo
    fprintf(file, "%s", cpf);

    // Fecha o arquivo
    fclose(file);

    // Reabre o arquivo no modo de anexar ("a") para adicionar informações
    file = fopen(arquivo, "a");

    if (file == NULL) {
        exibirErro("Erro ao abrir o arquivo para anexar informações.");
        return;
    }

    // Adiciona uma vírgula após o CPF
    fprintf(file, ",");

    // Fecha o arquivo novamente
    fclose(file);

    // Solicitação do nome ao usuário
    obterEntradaNaoVazia("Digite o nome a ser cadastrado: ", nome, sizeof(nome));

    // Reabre o arquivo para adicionar o nome
    file = fopen(arquivo, "a");
    if (file == NULL) {
        exibirErro("Erro ao abrir o arquivo para anexar o nome.");
        return;
    }

    fprintf(file, "%s", nome);
    fclose(file);

    // Solicitação do sobrenome ao usuário
    obterEntradaNaoVazia("Digite o sobrenome a ser cadastrado: ", sobrenome, sizeof(sobrenome));

    // Reabre o arquivo para adicionar o sobrenome
    file = fopen(arquivo, "a");
    if (file == NULL) {
        exibirErro("Erro ao abrir o arquivo para anexar o sobrenome.");
        return;
    }

    fprintf(file, "%s", sobrenome);
    fclose(file);

    // Solicitação do cargo ao usuário
    obterEntradaNaoVazia("Digite o cargo a ser cadastrado: ", cargo, sizeof(cargo));

    // Reabre o arquivo para adicionar o cargo
    file = fopen(arquivo, "a");
    if (file == NULL) {
        exibirErro("Erro ao abrir o arquivo para anexar o cargo.");
        return;
    }

    fprintf(file, "%s", cargo);

    // Fecha o arquivo
    fclose(file);

    // Mensagem de sucesso após o registro
    printf("Registro realizado com sucesso!\n");
    system("pause");
}

// Função para realizar a consulta de informações
void consulta() {
    char cpf[40];
    char conteudo[100];

    // Solicitação do CPF ao usuário para consulta
    obterEntradaNaoVazia("Digite o CPF a ser consultado: ", cpf, sizeof(cpf));

    // Abertura do arquivo no modo de leitura
    FILE *file = fopen(cpf, "r");

    if (file == NULL) {
        printf("Não foi possível abrir o arquivo. Usuário não localizado!\n");
    } else {
        // Exibição das informações do arquivo
        while (fgets(conteudo, sizeof(conteudo), file) != NULL) {
            printf("\nEssas são as informações do usuário:\n%s\n\n", conteudo);
        }

        // Fechamento do arquivo
        fclose(file);
    }

    system("pause");
}

// Função para realizar a exclusão de informações
void deletar() {
    char cpf[40]; // Declaração da variável para armazenar o CPF a ser deletado
    char confirmacao; // Variável para armazenar a confirmação do usuário

    // Solicitação do CPF ao usuário
    printf("Digite o CPF a ser deletado:");
    scanf("%s", cpf);

    FILE *file;
    file = fopen(cpf, "r+"); // Abre o arquivo para leitura e escrita

    // Verifica se houve erro na abertura do arquivo
    if (file == NULL) {
        printf("Usuário não encontrado!\n");
        return; // Encerra a função caso o usuário não seja encontrado
    }

    // Solicitação de confirmação ao usuário
    printf("Tem certeza que deseja deletar este usuário? (S/N): ");
    scanf(" %c", &confirmacao); // Lê a confirmação do usuário

    // Verifica se o usuário confirmou a exclusão
    if (confirmacao == 'S' || confirmacao == 's') {
        fclose(file); // Fecha o arquivo
        remove(cpf); // Deleta o arquivo
        printf("Usuário deletado com sucesso!\n");
    } else {
        fclose(file); // Fecha o arquivo
        printf("Operação de exclusão cancelada.\n");
    }
}

int main() {
    int opcao = 0;
    int laco = 1;

    // Loop principal do programa
    while (laco == 1) {
        system("cls");

        setlocale(LC_ALL, "Portuguese");

        // Menu principal
        printf("### Cartório da EBAC ###\n\n");
        printf("Escolha a opção desejada do menu\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t4 - Cadastrar mais usuários ou voltar ao menu\n\n");
        printf("\t5 - Sair do sistema\n\n");
        printf("Opção: ");

        // Armazenando a escolha do usuário
        scanf("%d", &opcao);

        system("cls");

        // Switch para opções do menu
        switch (opcao) {
            case 1:
                registro();
                break;

            case 2:
                consulta();
                break;

            case 3:
                deletar();
                break;

            case 4:
                // Caso 4: Cadastrar mais usuários ou voltar ao menu principal
                printf("Opções:\n");
                printf("\t1 - Cadastrar mais usuários\n");
                printf("\t2 - Voltar ao menu principal\n\n");
                printf("Opção: ");
                int opcao_submenu;
                scanf("%d", &opcao_submenu);

                switch (opcao_submenu) {
                    case 1:
                        // Cadastrar mais usuários
                        registro();
                        break;

                    case 2:
                        // Voltar ao menu principal
                        break;

                    default:
                        printf("Opção inválida!\n");
                        break;
                }
                break;

            case 5:
                // Sair do sistema
                printf("Saindo do sistema...\n");
                laco = 0;
                break;

            default:
                printf("Essa opção não está disponível!\n");
                system("pause");
                break;
        }
    }
    return 0;
}
