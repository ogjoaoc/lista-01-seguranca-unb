#include <bits/stdc++.h>
#include "cifra_cesar.cpp"

using namespace std;

void LIMPA() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void PAUSA() {
    cout << "\nPressione Enter para continuar...";
    cin.ignore(); cin.get();
}
string LER_ARQUIVO() {
    ifstream arquivo("input.txt");
    string conteudo((istreambuf_iterator<char>(arquivo)), istreambuf_iterator<char>());
    arquivo.close();
    return conteudo;
}
void AVISO() {
    LIMPA();
    cout << "ATENCAO:\n";
    cout << "O texto salvo no arquivo input.txt sera utilizado para as seguintes operacoes.\n";
    cout << "Caso deseje alterar o plaintext, faca isso antes de prosseguir.";
    PAUSA();
}
void CRIPTOGRAFAR() {
    AVISO();
    string original = LER_ARQUIVO();
    int chave;
    cout << "Digite a chave de deslocamento (1-25): ";
    cin >> chave;
    string cifrado = codificaCifraCesar(original, chave);
    cout << '\n';
    cout << "\nMensagem criptografada:\n";
    cout << cifrado << '\n';
}
void DECRIPTOGRAFAR() {
    AVISO();
    string mensagem = LER_ARQUIVO();
    int chave;
    cout << "Digite a chave de deslocamento (1-25): ";
    cin >> chave;
    string decifrado = decodificaCifraCesar(mensagem, chave);
    cout << '\n';
    cout << "\nMensagem descriptografada:\n";
    cout << decifrado << '\n';
}
void BRUTEFORCE() {
    AVISO();
    string mensagem = LER_ARQUIVO();
    cout << "\nRealizando ataque brute-force...\n";
    geraResultadosForcaBruta(ataqueForcaBruta(mensagem));
}
void DISFREQ() {
    AVISO();
    string mensagem = LER_ARQUIVO();
    int chave = encontrarChavePorFrequencia(mensagem);
    string decifrado = decodificaCifraCesar(mensagem, chave);
    cout << '\n';
    cout << "\nChave encontrada: " << chave << '\n';
    cout << "Mensagem decifrada:\n";
    cout << decifrado << '\n';
}
int main() {
    ifstream teste("input.txt");
    if (!teste.good()) {
        ofstream criar("input.txt");
        criar << "Texto padrao para testes. Substitua este conteudo.\n";
        criar.close();
    }
    teste.close();
    int OPCAO;
    do {
        LIMPA();
        cout << "       SIMULADOR DE CIFRA DE CESAR \n\n";
        cout << "1. Criptografar texto\n";
        cout << "2. Descriptografar texto\n";
        cout << "3. Ataque por brute-force\n";
        cout << "4. Ataque por distribuicao de frequencias\n";
        cout << "5. Sair\n";
        cout << "\nEscolha uma opcao: ";
        cin >> OPCAO;
        LIMPA();
        switch(OPCAO) {
            case 1: CRIPTOGRAFAR(); break;
            case 2: DECRIPTOGRAFAR(); break;
            case 3: BRUTEFORCE(); break;
            case 4: DISFREQ(); break;
            case 5: cout << "Encerrando programa...\n"; return 0;
            default: cout << "Opcao invalida!\n";
        }
        PAUSA();
    } while(1);
}