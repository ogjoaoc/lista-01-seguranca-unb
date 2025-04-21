#include <bits/stdc++.h>

using namespace std;

// string removeEspacos(string &mensagem) {
//     string retorno = "";
//     for(char &letra : mensagem) {
//         if(letra != ' ') {
//             retorno += letra;
//         }
//     }
//     return retorno;
// }

map<string,double> TRIGRAFOS = {
    {"que", 72.29}, {"ent", 70.23}, {"nte", 55.08}, {"ado", 51.16},
    {"ade", 50.04}, {"ode", 45.43}, {"ara", 45.37}, {"est", 43.90},
    {"res", 43.08}, {"con", 41.73}
};

map<string,double> DIGRAFOS = {
    {"de", 3.25}, {"es", 2.89}, {"en", 2.59}, {"nt", 2.44},
    {"te", 2.38}, {"er", 2.28}, {"el", 2.05}, {"ra", 1.98}
};

double calculaScore(string &texto) {
    map<string,int> contagem;
    for(int i = 0; i < texto.length() - 1; i++) {
        if(i < texto.length() - 2) {
            string trigrafo = texto.substr(i, 3);
            contagem[trigrafo]++;
        }
        string digrafo = texto.substr(i, 2);
        contagem[digrafo]++;
    }
    double score = 0;
    for(auto &[trigrafo, freq] : TRIGRAFOS) {
        if(contagem[trigrafo]) {
            score += contagem[trigrafo] * freq;
        }
    }
    for(auto &[digrafo, freq] : DIGRAFOS) {
        if(contagem[digrafo]) {
            score += contagem[digrafo] * freq;
        }
    }
    return score;
}

vector<pair<string,pair<double,vector<int>>>> ataqueFrequencia(string mensagem_criptografada, int TAM_CHAVE) {
    vector<int> permutacao(TAM_CHAVE);
    vector<pair<string,pair<double,vector<int>>>> possibilidades;
    for(int i = 0; i < TAM_CHAVE; i++) {
        permutacao[i] = i + 1;
    }
    do {
        int colunas = TAM_CHAVE;
        int linhas = mensagem_criptografada.length() / colunas;
        vector<int> ordem_original(colunas);
        for(int i = 0; i < colunas; i++) {
            ordem_original[permutacao[i] - 1] = i;
        }
        vector<string> blocos(colunas);
        for(int i = 0; i < colunas; i++) {
            int inicio = ordem_original[i] * linhas;
            blocos[i] = mensagem_criptografada.substr(inicio, linhas);
        }
        // cout << "DEBUG\n";
        // for(auto &x : blocos) cout << x << '\n';
        // cout << '\n';
        string mensagem_decifrada;
        for(int i = 0; i < linhas; i++) {
            for(int j = 0; j < colunas; j++) {
                if(i < blocos[j].size()) {
                    mensagem_decifrada += blocos[j][i];
                }
            }
        }
        double score = calculaScore(mensagem_decifrada);
        possibilidades.push_back({mensagem_decifrada, {score, permutacao}});
    } while(next_permutation(begin(permutacao), end(permutacao)));
    sort(begin(possibilidades), end(possibilidades), [&](auto a, auto b) {
       return a.second.first > b.second.first;
    });
    return possibilidades;
}


vector<pair<char,int>> geraPermutacao(string &chave) {
    vector<pair<char,int>> contagem;
    for(int i = 0; i < chave.size(); i++) {
        contagem.push_back({chave[i], i + 1});
    }
    sort(contagem.begin(), contagem.end());
    return contagem;
}

string codificaTransposicao(string mensagem, string chave) {
    // mensagem = removeEspacos(mensagem);
    int linhas = (mensagem.length() + chave.length() - 1) / chave.length(); 
    int colunas = chave.size();
    vector<vector<char>> matriz(linhas, vector<char> (colunas));
    int indice = 0;
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            if(indice < mensagem.length()) {
                matriz[i][j] = mensagem[indice++];
            } else {
                matriz[i][j] = 'X';
            }
        }
    }
    string mensagem_codificada = "";
    vector<string> auxiliar;
    for(int j = 0; j < colunas; j++) {
        string aux = "";
        for(int i = 0; i < linhas; i++) {
            aux += matriz[i][j];
        }
        auxiliar.push_back(aux);
    }
    vector<pair<char, int>> permutacao = geraPermutacao(chave);
    for(auto &x : permutacao) cout << x.second << ' '; cout << '\n';
    for(int i = 0; i < colunas; i++) {
        mensagem_codificada += auxiliar[permutacao[i].second - 1];
    }
    return mensagem_codificada;
}

string decodificaTransposicao(string mensagem_criptografada, string chave) {
    int colunas = chave.size();
    int linhas = mensagem_criptografada.length() / colunas;
    vector<pair<char,int>> colunas_ordenadas = geraPermutacao(chave);
    vector<int> ordem_original(colunas);
    for(int i = 0; i < colunas; i++) {
        ordem_original[colunas_ordenadas[i].second - 1] = i;
    }
    vector<string> blocos(colunas);
    for(int i = 0; i < colunas; i++) {
        int inicio = ordem_original[i] * linhas;
        blocos[i] = mensagem_criptografada.substr(inicio, linhas);
    }
    // cout << "DEBUG\n";
    // for(auto &x : blocos) cout << x << '\n';
    // cout << '\n';
    string mensagem_decifrada;
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            if(i < blocos[j].size()) {
                mensagem_decifrada += blocos[j][i];
            }
        }
    }
    return mensagem_decifrada;
}

vector<pair<string,vector<int>>> ataqueForcaBruta(string mensagem_criptografada, int TAM_CHAVE) {
    vector<int> permutacao(TAM_CHAVE);
    vector<pair<string,vector<int>>> possibilidades;
    for(int i = 0; i < TAM_CHAVE; i++) {
        permutacao[i] = i + 1;
    }
    do {
        int colunas = TAM_CHAVE;
        int linhas = mensagem_criptografada.length() / colunas;
        vector<int> ordem_original(colunas);
        for(int i = 0; i < colunas; i++) {
            ordem_original[permutacao[i] - 1] = i;
        }
        string mensagem_decifrada;
        for(int i = 0; i < linhas; i++) {
            for(int &j : ordem_original) {
                int pos = j  * linhas + i;
                if(pos < mensagem_criptografada.size()) {
                    mensagem_decifrada += mensagem_criptografada[pos];
                }
            }
        }
        possibilidades.push_back({mensagem_decifrada, permutacao});
    } while(next_permutation(begin(permutacao), end(permutacao)));
    return possibilidades;
}

void geraResultadosForcaBruta(vector<pair<string,vector<int>>> possibilidades) {
    for(auto &[mensagem, permutacao] : possibilidades) {
        cout << '\n';
        cout << "Resultado : " << mensagem << " \n\n | " << " Permutacao utilizada  : ";
        for(int &i : permutacao) {
            cout << i << ' ';
        }
        cout << '\n';
    } 
}
