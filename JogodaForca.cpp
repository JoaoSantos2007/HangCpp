#include <iostream>
using namespace std;

//Declarar Funções
int verif_tamanho(string palavra);
bool desenhar(string tem,int nivel,bool final,string palavra, int tamanho);
bool verif_ganhar(bool final,string palavra, int tamanho);
void desenhar_ganhou();
void desenhar_perdeu();

char letras_usadas[27];
bool partida;

//Começo
int main(){
    //Declaração de Variáveis
    bool final=true, repetido = true;
    string word;
    string tema = "UNDEFINED";
    int p = 0,tam,nivel = 0,status = 0;
    char letra;

    //Perguntas
    cout<<"Digite o tema: ";
    getline(cin, tema);
    cout<<"Digite a palavra: ";
    getline(cin, word);  

    //Transformar String word em char Palavras
    tam = verif_tamanho(word);
    char palavras[tam];
    for(int i = 0;i<tam;i++){
        palavras[i]=word[i];
        cout<<palavras[i]<<endl;
    }


    while(final){
        final = desenhar(tema,nivel,final,word,tam);
        cout<<"Digite uma letra: ";
        cin>>letra;

        //Verifica se a letra é repetida
        repetido = false;
        for(int i = 0;i<27;i++){
            if(letras_usadas[i] != '\0' && letra == letras_usadas[i]){
                repetido = true;
            }
        }
        while(repetido){
            repetido = false;
            cout<<endl<<"Letra repetida"<<endl;
            cout<<"Digite uma letra: ";
            cin>>letra;
            for(int i = 0;i<27;i++){
                if(letras_usadas[i] != '\0' && letra == letras_usadas[i]){
                    repetido = true;
                }
            }
        }

        //Verifica se a letra é corresponde a palavra chave
        for(int i = 0;i<tam;i++){
            if(palavras[i] == letra){
                status = 1;
            }
        }
        if(status == 0){
            nivel++;                
        }

        letras_usadas[p] = letra;
        status = 0;
        p++;
        final = desenhar(tema,nivel,final,word,tam);
        final = verif_ganhar(final,word,tam);
    }
    system("clear");
    if(partida){
        cout<<"Voce ganhou!!!"<<endl;
    }else{
        desenhar_perdeu();
    }           
}

//Funções

bool desenhar(string tem,int nivel,bool final,string palavra, int tamanho){
    system("clear");
    bool ok;
    cout<<"========================="<<endl;
    cout<<"     Jogo da Forca       "<<endl;
    cout<<"========================="<<endl<<endl;
    cout<<"                         Tema: "<<tem<<endl;
    

    //Imprimir letras usadas
    cout<<"                         Letras Usadas:";
    for(int i = 0;i<27;i++){
        if(letras_usadas[i] != '\0')cout<<letras_usadas[i];
        if(letras_usadas[i+1]!='\0')cout<<" - ";
    }
    cout<<endl;


    //Imprimir Forca
    cout<<"________________ "<<endl;
    cout<<"|            |     "<<endl;
    //Nivel 1
    if(nivel >= 1){
        cout<<"|           ( )"<<endl;
    }else{
        cout<<"|               "<<endl;
    }

    //Nivel 2,3,4
    if(nivel == 2){
        cout<<"|            | "<<endl;
    }else if(nivel == 3){
        cout<<"|           /| "<<endl;
    }else if(nivel >= 4){
        cout<<"|           /|\\"<<endl;
    }

    //Nivel 5   
    if(nivel >= 5){
        cout<<"|            |"<<endl;
    }else{
        cout<<"|             "<<endl;
    }


    //Nivel 6 e 7
    if(nivel == 6){
        cout<<"|           /  "<<endl;
    }else if(nivel >= 7){
        cout<<"|           / \\"<<endl;
    }else{
        cout<<"|             "<<endl;
    }  
    cout<<"|             "<<endl<<endl;
    cout<<"         ";
    for(int posicao = 0;posicao < tamanho; posicao++){
        ok = true;
        for(int i = 0;i < 27; i++){
            if(letras_usadas[i] == palavra[posicao]){
                cout<<palavra[posicao];
                ok = false;
            }else if(letras_usadas[i] == '\0' && letras_usadas[i+1] != '\0'){
                cout<<" - ";
                ok = false;
            }            
        }
        if(ok){
            cout<<"_ ";
        }else{
            cout<<" ";
        }
    }
    cout<<""<<endl<<endl;

    //Verificar se usuário perdeu partida
    if(nivel > 7){
        final = false;
        partida = false;
    }
    return(final);

}

int verif_tamanho(string palavra){
    int i = 0,tamanho = 0;
    bool fim = true;
    while(fim){
        if(palavra[i] == '\0'){
            tamanho = i;
            fim = false;
        }
        i++;
    }
    return(tamanho);
}

bool verif_ganhar(bool final,string palavra, int tamanho){
    int contagem = 0;
    for(int posicao = 0;posicao<tamanho;posicao++){
        for(int i = 0;i<27;i++){
            if(letras_usadas[i] == palavra[posicao]){
                contagem++;
            }
        }
    }
    if(contagem == tamanho){
        final = false;
        partida = true;
    }
    return(final);
}


void desenhar_perdeu(){
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀"<<endl;//Linha 1
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⠟⠛⠛⠛⠛⠛⣛⣻⣿⣿⣿⣿⣿⣟⣛⣛⣛⠛⠒⠲⠶⠦⣤⣤⣤⣀⡀"<<endl;//Linha 2
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠏⠁⠀⠀⢀⣤⠶⣛⣩⣥⠤⠤⠤⠤⢤⣤⣤⣭⣭⣉⣉⣛⣛⣻⣭⣥⠬⡍⠛⢶⣄⡀"<<endl;//Linha 3
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⠃⠀⠀⣠⡶⢋⡵⢛⡩⠵⠒⠒⠒⠒⠢⡀⠀⠀⠀⠀⠀⢀⣠⠤⠤⠤⢤⣄⠀⠀⠀⠉⠻⣆"<<endl;//Linha 4
    cout<<"⠀⠀⠀⠀⠀⠀⠀⢀⣿⠃⠀⠀⠘⢁⡴⢋⣴⢿⠒⠈⠉⣏⠉⠐⠒⡾⣄⠀⠀⠀⠀⠀⡠⠀⠀⢀⣀⣈⣙⣆⡀⠀⠀⢹⡆"<<endl;//Linha 5
    cout<<"⠀⠀⠀⠀⠀⠀⣠⣾⠃⠀⠀⠀⠀⠀⢀⠟⣁⠀⠁⢀⣤⣦⣤⡀⠘⠀⢈⣷⡄⠀⠀⠀⣇⠖⠉⠙⠅⠀⠀⠉⠉⠑⢦⡈⣷⡀"<<endl;//Linha 6
    cout<<"⠀⠀⠀⠀⢠⣾⢿⣧⠤⠤⠤⠄⠀⠖⣿⠀⠃⠀⠀⣿⣿⣿⣿⡗⠀⠐⠁⢸⡇⠀⣀⣰⠉⠠⠀⠀⣰⣶⣷⣶⠀⠀⠀⢱⡈⢻⣦"<<endl;//Linha 7
    cout<<"⠀⠀⠀⣠⡿⣱⠋⢀⣴⠶⠚⠻⢶⣤⡘⢧⣄⠆⠂⠀⡉⠉⣉⣀⣀⠉⣠⡟⠁⠀⠉⢻⣆⠀⠀⠀⠘⠛⠟⠛⠀⠀⢈⡿⢍⢢⢹⡇"<<endl;//Linha 8
    cout<<"⠀⠀⢠⣿⠁⡇⢠⣿⠁⠀⢰⣦⡀⠉⠉⠀⠈⠙⠲⠾⠾⠶⠶⠶⠚⠋⠉⠀⠀⠀⠀⢸⣯⡑⠢⢤⣀⣂⣀⣨⠤⠒⠛⠃⠘⡆⡇⡧"<<endl;//Linha 9
    cout<<"⠀⠀⢸⣿⠀⡇⢸⡇⢠⣴⣾⠋⠛⢷⣦⣀⠀⠀⠀⠠⠤⠤⠴⢠⠶⠒⠀⠀⠀⠀⠀⠀⠉⢿⣦⡀⠀⠀⠀⠀⢸⣷⠀⠀⡼⢡⢣⡇"<<endl;//Linha 10
    cout<<"⠀⠀⠀⢿⡇⣧⠘⠿⠀⠀⠸⣧⡀⠀⠈⢻⡿⢶⣦⣄⡀⠀⠀⠸⣆⠐⠟⠻⠷⠀⠀⠀⢀⣾⠛⠃⠑⠤⠀⢀⣼⣿⡇⢀⠤⢂⣾⠃"<<endl;//Linha 11
    cout<<"⠀⠀⠀⠈⢻⣌⠑⠦⠀⠀⠀⢿⣿⣷⣤⣸⣷⡀⠀⠈⠙⠻⢿⣶⣤⣄⣀⡀⠀⠀⠙⠿⠟⠁⠀⠀⢀⣠⡴⣿⠉⣿⣿⠀⠀⣼⠁"<<endl;//Linha 12
    cout<<"⠀⠀⠀⠀⠀⠙⣷⡀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣶⣤⣀⣀⣼⠁⠀⠈⠉⠙⣿⠛⠛⠻⢿⠿⠛⠛⢻⡇⠀⢸⡀⣹⣿⠀⠀⡏"<<endl;//Linha 13
    cout<<"⠀⠀⠀⠀⠀⠀⠈⢿⡀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣤⣄⣀⣿⣄⣀⣀⣸⣄⣀⣠⣴⣿⣶⣿⣿⣿⣿⡇⠀⡇"<<endl;//Linha 14
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠈⢷⡄⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⡇"<<endl;//Linha 15
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣦⠀⠘⣿⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣷"<<endl;//Linha 16
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢷⣄⠘⢷⡀⠘⡟⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣿⠀"<<endl;//Linha 17
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣧⡀⠻⣾⡃⠀⠀⠈⠙⢿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣿"<<endl;//Linha 18
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣄⠈⠻⣦⡀⠀⠀⡼⠀⠀⠈⠙⠻⣿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⢿⡿⣹⠇⠀⣿"<<endl;//Linha 19
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⣄⠈⠛⠷⣼⣇⡀⠀⠀⠀⠀⣿⠀⠀⠀⢸⡇⠀⠀⡿⠀⢸⠇⣘⣧⠟⠀⢀⡿"<<endl;//Linha 20
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢷⣄⡀⠀⠙⠻⠷⠶⣶⣾⣿⣤⣀⣠⣿⣄⣀⣴⠷⠶⠿⠿⠟⠋⠀⢀⣾⠃⠀"<<endl;//Linha 21
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⣶⣤⣤⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⣤⡤⠞⠁"<<endl;//Linha 22
    cout<<"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠋⠉⠀⠀⠀"<<endl<<endl;//Linha 23
    cout<<"Ahh! Voce perdeu, tente mais uma vez!"<<endl;
}

void desenhar_ganhou(){

}