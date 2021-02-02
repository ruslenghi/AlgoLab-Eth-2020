//DISCLAIMER: I did not write this solution myself, i have found it on the internet

#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<map>
#include<cmath>

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> status;

int n, k, m, M;
vector<int> fighters;//This will store the types of the fighters
vector<int> POW_2;//This will store powers of 2, such that we will not need to compute them twice

//In short: variety ti decodifica un intero che ti dice gli ultimi m-1 fighters!
int variety(int v){
  VI vis(k+1, 0);//Credo che mettiamo lo 0 per considerare il "tipo in +"
  //cioè quello in cui non c'è nessun combattente
  
  //Il prossimo while non capisco perchè lo fa...
  while(v != 0){
    vis[v % 10] = 1;
    v /= 10;
  }
  
  int sum = 0;
  for(int elem : vis){
    sum += elem;
  }
  return sum;
}

//E un bel po' di righe sono andate

//Questa funzione serve a rishiftare le cose una volta usata variety
int cut(int q){
  return q % M;
}

//Direi che l'approccio a questa sol è bottom up

void testcase(){
  cin >> n >> k >> m;
  M = (int)pow(10, m-1);
  fighters.clear();
  fighters.push_back(0);
  for(int i=0; i<n; i++){
    int type; cin >> type;
    type++;//Credo che questo lo faccia sempre per la storia del tipo 0 in + 
    fighters.push_back(type);
  }
  
  //DP[i][j][status] rappresenta lo score dopo aver settato l'i-esimo
  //combattente con status (?) mentre j = numero di combattenti nella
  //queue di sinistra - numero combattenti nella queue di destra + 11
  //per cui j puo essere al piu 22 in effetti
  
  //La scelta del +11 non è casuale, ma è dovuta all'attenta osservazione
  //per cui, dovendo essere tutte le rewards > 0, non si puo mai avere piu di
  //11 combattenti di dislivello tra sinistra e destra, xkè 2^11 > 3000
  
  //23 = 2*11 + 1, è un caso? o è piuttosto una questione di bit encoding?
  //Non è un caso! E' piuttosto che j puo essere un numero da -11 a 11 -> cioè 23 possibilità!
  vector<vector<map<status, int>>> DP(n+1, vector<map<status,int>>(23));
  //Non avendo ancora mandato nessuno nella arena la score è nulla
  DP[0][11][make_pair(0,0)] = 0;
  
  //Per tutti i combattenti, vediamo che succede...
  for(int i=0; i<n; i++){
    int next_type = fighters[i+1];
    for(int j=0; j<23; j++){
      //Per tutti gli elementi nella map(i,j) ....
      //prendine la key, che è un pair, e poi 
      //prendi il primo elemento di questa pair
      for(auto p : DP[i][j]){
        int l, r;
        int inc;
        
        //if add the next fighter to the left queue
        //Praticamente cosi sta aggiornando lo stato!
        //Poi immagino che userà cut(l) per scalarlo e tornare alla info degli m-1 pezzi
        l = 10*p.first.first + next_type;
        //L'incremento giustamente è dato cosi
        inc = 1000*variety(l) - POW_2[abs(j-11+1)];
        //Se l'incremento è negativo ciaone... non possiamo accettarlo perchè poi se no c'è il RIOT!
        if(inc >= 0){
          //tmp è il valore attuale che ho facendo questa scelta
          //Chiaramente è dato dal vecchio guadagno + l'incremento appena preso
          int tmp = inc + p.second;

          //Il secondo pezzo in make_pair p riferito allo stato in cui si trova 
          //l'entrata SUD dell'arena. Ora, tra l'altro, ho finalmente capito perchè usa una map il dude!
          //Lo fa perchè se no il grado di libertà del densore DP, relativo agli stati di nord e sud
          //sarebbe dovuto essere preparato con una dimensione adeguata. E magari sarebbe anche stata gigante..
          //rallentando molto tutto.
          
          //Evidentemente è possibile che si ricapiti piu volte nello stesso stato complessivo. 
          //In tal caso si aggiorna al meglio possibile!
          if(tmp > DP[i+1][j+1][make_pair(cut(l), p.first.second)]){
            DP[i+1][j+1][make_pair(cut(l), p.first.second)] = tmp;
          }
        }
        
        r = 10 * p.first.second + next_type;
        inc = 1000 * variety(r) - POW_2[abs(j - 11 - 1)];
        if (inc >= 0) {
            int tmp = inc + p.second;
            if (tmp > DP[i + 1][j - 1][make_pair(p.first.first, cut(r))]) {
                DP[i + 1][j - 1][make_pair(p.first.first, cut(r))] = tmp;
                // cout << "DP[" << i + 1 << "][" << j - 1 << "][(" << p.first.first  << ", " << r << ")] = " 
                //     << p.second << " + " << 1000 * variety(r) << " - " << (int)pow(2, abs(j - 12 - 1)) << endl;
            }
        }
      }
    }
  }
  
  int result = 0;
  for(int j=0; j<23; j++){
    for(auto p : DP[n][j]){
      if(p.second > result){
        result = p.second;
      }
    }
  }
  
  cout << result << "\n";
  
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    int curr = 1;
    for (int i = 0; i <= 12; i++) {
        POW_2.push_back(curr);
        curr *= 2;
    }
    while(t--) {
        testcase();
    }
}
