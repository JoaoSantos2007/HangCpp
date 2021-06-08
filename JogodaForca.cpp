#include <iostream>
#include <ctype.h>
using namespace std;

#ifdef __unix__

#elif defined(_WIN32) || defined(WIN32)
#include <stdlib.h>
#define OS_Windows
#endif

bool jogo = true;
bool inicio = false;

//Variáveis Globais
char letras_usadas[27];
bool partida;

//Declarar Funções
int verif_tamanho(string palavra);
bool desenhar(string tem, int nivel, bool final, string palavra, int tamanho);
bool verif_ganhar(bool final, string palavras, int tamanho, int menos);
void desenhar_ganhou();
void desenhar_perdeu();
void reset();
void limpar_tela();

//Começo
int main()
{
    while (jogo)
    {
        //Declaração de Variáveis
        bool final = true, repetido = true, continuar = true;
        string word, resp;
        string tema;
        int p = 0, tam, nivel = 0, status = 0, menos = 0;
        char letra;
        string nada;

        //Perguntas
        cout << "Digite o tema: ";
        if (inicio)
        {
            getline(cin, nada);
        }
        getline(cin, tema);
        // cin>>tema;
        cout << "Digite a palavra: ";
        // getline(cin, word);
        cin >> word;

        //Transformar String word em char Palavras
        tam = verif_tamanho(word);
        for (int i = 0; i < tam; i++)
        {
            if(word[i] != '-'){
                word[i] = toupper(word[i]);
            }else{
                menos++;
            }
        }

        while (final)
        {
            final = desenhar(tema, nivel, final, word, tam);
            cout << "Digite uma letra: ";
            cin >> letra;
            letra = toupper(letra);
            
            //Verifica se a letra é repetida
            repetido = false;
            for (int i = 0; i < 27; i++)
            {
                if (letras_usadas[i] != '\0' && letra == letras_usadas[i])
                {
                    repetido = true;
                }
            }
            while (repetido)
            {
                repetido = false;
                cout << endl
                     << "Letra repetida" << endl;
                cout << "Digite uma letra: ";
                cin >> letra;
                letra = toupper(letra);
                for (int i = 0; i < 27; i++)
                {
                    if (letras_usadas[i] != '\0' && letra == letras_usadas[i])
                    {
                        repetido = true;
                    }
                }
            }

            //Verifica se a letra é corresponde a palavra chave
            for (int i = 0; i < tam; i++)
            {
                if (word[i] == letra)
                {
                    status = 1;
                }
            }
            if (status == 0)
            {
                nivel++;
            }

            letras_usadas[p] = letra;
            status = 0;
            p++;
            final = desenhar(tema, nivel, final, word, tam);
            final = verif_ganhar(final, word, tam, menos);
        }
        limpar_tela();
        if (partida)
        {
            desenhar_ganhou();
        }
        else
        {
            desenhar_perdeu();
        }
        while (continuar)
        {
            cout<<endl<<"A palavra chave era: "<<word<<endl;
            cout<<endl<<"Voce quer continuar[s/n]: " << endl;
            cin >> resp;
            if (resp == "sim" || resp == "Sim" || resp == "s" || resp == "S")
            {
                continuar = false;
                jogo = true;
                reset();
            }
            else if (resp == "nao" || resp == "Nao" || resp == "n" || resp == "N")
            {
                continuar = false;
                jogo = false;
            }
        }
        inicio = jogo;
        limpar_tela();
    }
}

//Funções

bool desenhar(string tem, int nivel, bool final, string palavra, int tamanho)
{
    limpar_tela();
    bool ok;
    cout << "=========================" << endl;
    cout << "     Jogo da Forca       " << endl;
    cout << "=========================" << endl
         << endl;
    cout << "                         Tema: " << tem << endl;

    //Imprimir letras usadas
    cout << "                         Letras Usadas:";
    for (int i = 0; i < 27; i++)
    {
        if (letras_usadas[i] != '\0')
            cout << letras_usadas[i];
        if (letras_usadas[i + 1] != '\0' && letras_usadas[i])
            cout << " - ";
    }
    cout << endl;

    //Imprimir Forca
    cout << "________________ " << endl;
    cout << "|            |     " << endl;
    //Nivel 1
    if (nivel >= 1)
    {
        cout << "|           ( )" << endl;
    }
    else
    {
        cout << "|               " << endl;
    }

    //Nivel 2,3,4
    if (nivel == 2)
    {
        cout << "|            | " << endl;
    }
    else if (nivel == 3)
    {
        cout << "|           /| " << endl;
    }
    else if (nivel >= 4)
    {
        cout << "|           /|\\" << endl;
    }

    //Nivel 5
    if (nivel >= 5)
    {
        cout << "|            |" << endl;
    }
    else
    {
        cout << "|             " << endl;
    }

    //Nivel 6 e 7
    if (nivel == 6)
    {
        cout << "|           /  " << endl;
    }
    else if (nivel >= 7)
    {
        cout << "|           / \\" << endl;
    }
    else
    {
        cout << "|             " << endl;
    }
    cout << "|             " << endl
         << endl;
    cout << "         ";
    for (int posicao = 0; posicao < tamanho; posicao++)
    {
        ok = true;
        if (palavra[posicao] == '-')
        {
            cout << palavra[posicao];
            ok = false;
        }
        if (ok)
        {
            for (int i = 0; i < 27; i++)
            {
                if (letras_usadas[i] == palavra[posicao] && palavra[posicao] != '-')
                {
                    cout << palavra[posicao];
                    ok = false;
                }
            }
            if (ok)
            {
                cout << "_ ";
            }
            else if (palavra[posicao] != '-')
            {
                cout << " ";
            }
        }
    }
    cout << "" << endl
         << endl;

    //Verificar se usuário perdeu partida
    if (nivel > 7)
    {
        final = false;
        partida = false;
    }
    return (final);
}

int verif_tamanho(string palavras)
{
    int i = 0, tamanho = 0;
    bool fim = true;
    while (fim)
    {
        if (palavras[i] == '\0')
        {
            tamanho = i;
            fim = false;
        }
        i++;
    }
    return (tamanho);
}

bool verif_ganhar(bool final, string palavra, int tamanho, int menos)
{
    int contagem = 0;
    int tamanhos = tamanho - menos;
    // cout<<tam;
    // cin>>contagem;
    for (int posicao = 0; posicao < tamanho; posicao++)
    {
        if(palavra[posicao] != '-'){
            for (int i = 0; i < 27; i++)
            {
                if (letras_usadas[i] == palavra[posicao])
                {
                    contagem++;
                }
            }            
        }
    }
    if (contagem >= (tamanhos))
    {
        final = false;
        partida = true;
    }
    return (final);
}

void desenhar_perdeu()
{
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀" << endl;                         //Linha 1
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⠟⠛⠛⠛⠛⠛⣛⣻⣿⣿⣿⣿⣿⣟⣛⣛⣛⠛⠒⠲⠶⠦⣤⣤⣤⣀⡀" << endl;         //Linha 2
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠏⠁⠀⠀⢀⣤⠶⣛⣩⣥⠤⠤⠤⠤⢤⣤⣤⣭⣭⣉⣉⣛⣛⣻⣭⣥⠬⡍⠛⢶⣄⡀" << endl;      //Linha 3
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⠃⠀⠀⣠⡶⢋⡵⢛⡩⠵⠒⠒⠒⠒⠢⡀⠀⠀⠀⠀⠀⢀⣠⠤⠤⠤⢤⣄⠀⠀⠀⠉⠻⣆" << endl;     //Linha 4
    cout << "⠀⠀⠀⠀⠀⠀⠀⢀⣿⠃⠀⠀⠘⢁⡴⢋⣴⢿⠒⠈⠉⣏⠉⠐⠒⡾⣄⠀⠀⠀⠀⠀⡠⠀⠀⢀⣀⣈⣙⣆⡀⠀⠀⢹⡆" << endl;    //Linha 5
    cout << "⠀⠀⠀⠀⠀⠀⣠⣾⠃⠀⠀⠀⠀⠀⢀⠟⣁⠀⠁⢀⣤⣦⣤⡀⠘⠀⢈⣷⡄⠀⠀⠀⣇⠖⠉⠙⠅⠀⠀⠉⠉⠑⢦⡈⣷⡀" << endl;   //Linha 6
    cout << "⠀⠀⠀⠀⢠⣾⢿⣧⠤⠤⠤⠄⠀⠖⣿⠀⠃⠀⠀⣿⣿⣿⣿⡗⠀⠐⠁⢸⡇⠀⣀⣰⠉⠠⠀⠀⣰⣶⣷⣶⠀⠀⠀⢱⡈⢻⣦" << endl;  //Linha 7
    cout << "⠀⠀⠀⣠⡿⣱⠋⢀⣴⠶⠚⠻⢶⣤⡘⢧⣄⠆⠂⠀⡉⠉⣉⣀⣀⠉⣠⡟⠁⠀⠉⢻⣆⠀⠀⠀⠘⠛⠟⠛⠀⠀⢈⡿⢍⢢⢹⡇" << endl; //Linha 8
    cout << "⠀⠀⢠⣿⠁⡇⢠⣿⠁⠀⢰⣦⡀⠉⠉⠀⠈⠙⠲⠾⠾⠶⠶⠶⠚⠋⠉⠀⠀⠀⠀⢸⣯⡑⠢⢤⣀⣂⣀⣨⠤⠒⠛⠃⠘⡆⡇⡧" << endl; //Linha 9
    cout << "⠀⠀⢸⣿⠀⡇⢸⡇⢠⣴⣾⠋⠛⢷⣦⣀⠀⠀⠀⠠⠤⠤⠴⢠⠶⠒⠀⠀⠀⠀⠀⠀⠉⢿⣦⡀⠀⠀⠀⠀⢸⣷⠀⠀⡼⢡⢣⡇" << endl; //Linha 10
    cout << "⠀⠀⠀⢿⡇⣧⠘⠿⠀⠀⠸⣧⡀⠀⠈⢻⡿⢶⣦⣄⡀⠀⠀⠸⣆⠐⠟⠻⠷⠀⠀⠀⢀⣾⠛⠃⠑⠤⠀⢀⣼⣿⡇⢀⠤⢂⣾⠃" << endl; //Linha 11
    cout << "⠀⠀⠀⠈⢻⣌⠑⠦⠀⠀⠀⢿⣿⣷⣤⣸⣷⡀⠀⠈⠙⠻⢿⣶⣤⣄⣀⡀⠀⠀⠙⠿⠟⠁⠀⠀⢀⣠⡴⣿⠉⣿⣿⠀⠀⣼⠁" << endl;  //Linha 12
    cout << "⠀⠀⠀⠀⠀⠙⣷⡀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣶⣤⣀⣀⣼⠁⠀⠈⠉⠙⣿⠛⠛⠻⢿⠿⠛⠛⢻⡇⠀⢸⡀⣹⣿⠀⠀⡏" << endl;   //Linha 13
    cout << "⠀⠀⠀⠀⠀⠀⠈⢿⡀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣤⣄⣀⣿⣄⣀⣀⣸⣄⣀⣠⣴⣿⣶⣿⣿⣿⣿⡇⠀⡇" << endl;   //Linha 14
    cout << "⠀⠀⠀⠀⠀⠀⠀⠈⢷⡄⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⡇" << endl;   //Linha 15
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣦⠀⠘⣿⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣷" << endl;   //Linha 16
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢷⣄⠘⢷⡀⠘⡟⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣿⠀" << endl;  //Linha 17
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣧⡀⠻⣾⡃⠀⠀⠈⠙⢿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣿" << endl;   //Linha 18
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣄⠈⠻⣦⡀⠀⠀⡼⠀⠀⠈⠙⠻⣿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⢿⡿⣹⠇⠀⣿" << endl;   //Linha 19
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⣄⠈⠛⠷⣼⣇⡀⠀⠀⠀⠀⣿⠀⠀⠀⢸⡇⠀⠀⡿⠀⢸⠇⣘⣧⠟⠀⢀⡿" << endl;   //Linha 20
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢷⣄⡀⠀⠙⠻⠷⠶⣶⣾⣿⣤⣀⣠⣿⣄⣀⣴⠷⠶⠿⠿⠟⠋⠀⢀⣾⠃⠀" << endl;  //Linha 21
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⣶⣤⣤⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⣤⡤⠞⠁" << endl;    //Linha 22
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠋⠉⠀⠀⠀" << endl
         << endl; //Linha 23
    cout << "Ahh! Voce perdeu, tente mais uma vez!" << endl;
}

void desenhar_ganhou()
{
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⢀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⢀⡀⣀⣀⠀⠀" << endl; //linha 1
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⢿⣿⠀" << endl;  //linha 2
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣷⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⣾⡟⠀" << endl;  //linha 3
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣇⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣸⣿⠃⠀" << endl;  //linha 4
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣧⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⣼⣿⠋⠀⠀⠀" << endl; //linha 5
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠁⠀⠀⠀⠀" << endl; //linha 6
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀" << endl; //linha 7
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl; //linha 8
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl; //linha 9
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl; //linha 10
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣤⣤⣿⣿⣿⣿⣤⣤⡄⠀⠀⠀⠀⠀⠀⠀⠀" << endl; //linha 11
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⡦⠀⠀⠀⠀⠀⠀" << endl; //linha 12
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⠀⠀⠀⠀⠀⠀" << endl; //linha 13
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡗⠀⠀" << endl
         << endl; //linha 14
    cout << "Ebaaa! Voce ganhou!" << endl;
}

void reset()
{
    for (int i = 0; i < 27; i++)
    {
        letras_usadas[i] = '\0';
    }
}

void limpar_tela()
{
#ifdef OS_Windows
    system("cls");
#else
    system("clear");
#endif
}