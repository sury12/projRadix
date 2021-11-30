#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

//Uma váriavel para contar o numero de ocorrencias de cada substring em cada arquivo.
int nr_occurrences = 0;

// /////////////////////////////////
//FUNCOES DO RADIX SORT INICIAM AQUI

int get_max(vector <string> vec, int n){
    int max = vec[0].size();
    for (int i = 1; i < n; i++){
        if (vec[i].size()>max){
            max = vec[i].size();
        }
    }
    return max;
}//end of get_max(vector <string> vec, int n)


void count_sort(vector <string> &vec, int size, int k){
    string *b = NULL; int *c = NULL;
    b = new string[size];
    c = new int[257];

    for (int i = 0; i <257; i++){
        c[i] = 0;
    }

    for (int j = 0; j <size; j++){
        c[k < vec[j].size() ? (int)(unsigned char)vec[j][k] + 1 : 0]++;
    }

    for (int f = 1; f <257; f++){
        c[f] += c[f - 1];
    }

    for (int r = size - 1; r >= 0; r--){
        b[c[k < vec[r].size() ? (int)(unsigned char)vec[r][k] + 1 : 0] - 1] = vec[r];
        c[k < vec[r].size() ? (int)(unsigned char)vec[r][k] + 1 : 0]--;
    }

    for (int l = 0; l < size; l++){
        vec[l] = b[l];
    }

    delete[] b,c;

}//end of count_sort(vector <string> &vec, int size, int k)


void radix_sort(vector <string> &vec, int n){
    int max = get_max(vec, n);
    for (int digit = max; digit > 0; digit--){
        count_sort(vec, n, digit - 1);
    }
}//end of radix_sort(vector <string> &vec, int n)


//FUNCOES DO RADIX SORT TERMINAM AQUI
// /////////////////////////////////

//insertion sort para fazer os testes iniciais. Não está sendo utilizado no momento.
void insertion_sort( vector<string> &vec){
    string element, temp;

    for (int r = 1; r<vec.size(); r++){
        element.clear();
        element += vec[r];
        for (int t = (r - 1) ; t>=0; t--){
            if(element<vec[t]){
                temp.clear();
                temp += vec[t];
                vec[t].assign(element);
                vec[t + 1].assign(temp);
            }
        }
    }
}// end of insertion_sort( vector<int> &C, int tam)


string read_input_file(char* filename){
    static string line;
    ifstream myfile (filename);
    if (myfile.is_open()){
        getline (myfile,line);
        myfile.close();
    }
    else cout << "Unable to open file\n";
    return line;
}//end of read_input_file(char* filename)



void generate_output_file(char* filename, vector<string> &vec){
    ofstream outfile (filename);

    //ALGORITMO DE ORDENACAO RADIX SORT
    radix_sort(vec, vec.size());

    for(int i =0;i<vec.size(); i++){
        outfile << vec[i] << " ";
    }

    outfile.close();
}//end of generate_output_file(char* filename){

void generate_occurrences_file(char* filename, vector<string> vec){
    ofstream outfile (filename);
    int i, j;
    i = j = 0;

    while(i<vec.size()){
        while(vec[i]==vec[j]){
            nr_occurrences++;
            j++;
        }
        outfile << vec[i] << ": " << nr_occurrences << " ocorrência(s)" << "\n";
        i=j;
        nr_occurrences = 0;
    }

    outfile.close();
}//end of generate_occurrences_file(char* filename, vector<string> vec)

void str_to_vec(string input_file, vector<string> &vec){
    int i=0;
    string tmp;
    string last_tmp;

    while (input_file[i] != '\0'){
        if(input_file[i] != ' '){
            tmp += input_file[i];
            i++;
        }else{
            vec.push_back(tmp);
            tmp.clear();
            i++;
        }

        //A ultima substring é salva em uma outra variavel, pois
        //o laço while nao deixaria que essa ultima substring fosse registrada no vetor.
        if(input_file[i] == '\0'){
            last_tmp += tmp;
        }
    }//end of while (input_file[i] != '\0')

    //A ultima substring é, enfim, registrada no vetor.
    vec.push_back(last_tmp);

}//end of str_to_vec(string input_file, vector<string> &vec)


int main(int argc, const char * argv[]){

    //Each string will receive the whole content of its namesake
    string string_frankestein;
    string string_war_and_peace;
    //string string_test_input; //TESTING PURPOSES

    //Through the strings above, each vector will contain the individual substrings of its namesake
    vector<string>  vec_frankestein;
    vector<string> vec_war_and_peace;
    //vector<string> vec_test_input; //TESTING PURPOSES

    //Writing the whole file content of each file into strings;
    string_frankestein.assign(read_input_file("entradas/frankestein_clean.txt"));
    string_war_and_peace.assign(read_input_file("entradas/war_and_peace_clean.txt"));
    //string_test_input.assign(read_input_file("entradas/test_input_clean.txt")); //TESTING PURPOSES

    //Separating the string into substrings and placing them into a vector
    str_to_vec(string_frankestein, vec_frankestein);
    str_to_vec(string_war_and_peace, vec_war_and_peace);
    //str_to_vec(string_test_input, vec_test_input); //TESTING PURPOSES

    //Output files
    generate_output_file("saidas/frankestein_ordenado.txt", vec_frankestein);
    generate_output_file("saidas/war_and_peace_ordenado.txt", vec_war_and_peace);
    //generate_output_file("saidas/test_input_ordenado.txt", vec_test_input); //TESTING PURPOSES

    //Occurrences files
    generate_occurrences_file("ocorrencias/frankestein_ordenado.txt", vec_frankestein);
    generate_occurrences_file("ocorrencias/war_and_peace_ordenado.txt", vec_war_and_peace);
    //generate_occurrences_file("ocorrencias/test_input_ordenado.txt", vec_test_input); //TESTING PURPOSES


    return 0;
}//end of main(int argc, const char * argv[])
