#include <bits/stdc++.h>
#include "cifra_transposicao.cpp"

using namespace std;

void LIMPA() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void PAUSA() {
    cout << "\nPressione Enter para continuar...\n";
    cin.ignore(); cin.get();
}
string LER_ARQUIVO() {
    ifstream arquivo("input2.txt");
    string conteudo((istreambuf_iterator<char>(arquivo)), istreambuf_iterator<char>());
    arquivo.close();
    return conteudo;
}
void AVISO() {
    LIMPA();
    cout << "ATENCAO:\n";
    cout << "O texto salvo no arquivo input2.txt sera utilizado para as seguintes operacoes.\n";
    cout << "Caso deseje alterar o plaintext, faca isso antes de prosseguir.";
    PAUSA();
}
void CRIPTOGRAFAR() {
    AVISO();
    string original = LER_ARQUIVO();
    string chave;
    cout << "Digite a chave de transposicao (Recomendada: ""GAME""): ";
    cin >> chave;
    string cifrado = codificaTransposicao(original, chave);
    cout << '\n';
    cout << "\nMensagem criptografada:\n";
    cout << cifrado << '\n';
}
void DECRIPTOGRAFAR() {
    AVISO();
    string mensagem = LER_ARQUIVO();
    string chave;
    cout << "Digite a chave utilizada: ";
    cin >> chave;
    // debug cerr << "chave lida = " << chave << '\n';
    string decifrado = decodificaTransposicao(mensagem, chave);
    cout << '\n';
    cout << "\nMensagem descriptografada:\n\n";
    cout << decifrado << '\n';
}
void BRUTEFORCE() {
    AVISO();
    string mensagem = LER_ARQUIVO();
    int tamanho;
    cout << "Digite o tamanho fixo da chave de transposicao: ";
    cin >> tamanho;
    cout << "\nRealizando ataque brute-force...\n";
    auto possibilidades = ataqueForcaBruta(mensagem, tamanho);
    geraResultadosForcaBruta(possibilidades); 
}
void DISFREQ() {
    AVISO();
    string mensagem = LER_ARQUIVO();
    int tamanho;
    cout << "Digite o tamanho fixo da chave de transposicao: ";
    cin >> tamanho;
    vector<pair<string,pair<double,vector<int>>>> resultado = ataqueFrequencia(mensagem, tamanho);
    cout << '\n';
    cout << "\nMelhor score pela analise: " << resultado[0].second.first << '\n';
    cout << "Mensagem decifrada:\n\n";
    cout << resultado[0].first << '\n';
    cout << "\nPermutacao utilizada : ";
    for(int &i : resultado[0].second.second) {
        cout << i << ' ';
    }
    cout << '\n';
}
int main() {
    ifstream teste("input2.txt");
    if (!teste.good()) {
        ofstream criar("input2.txt");
        criar << "Texto padrao para testes. Substitua este conteudo.\n";
        criar.close();
    }
    teste.close();
    int OPCAO;
    do {
        LIMPA();
        cout << "       SIMULADOR DE CIFRA POR TRANSPOSICAO \n\n";
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