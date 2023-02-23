#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

void affichage(int* c[], int* f[], int n)
{
	cout << "c = " << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < (n-1); j++)
			cout << c[i][j] << "\t";
		cout << c[i][n-1] << endl;
	}


	cout << endl << "f = " << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < (n-1); j++)
			cout << f[i][j] << "\t";
		cout << f[i][n-1] << endl;
	}
}

/****************************************************/
/* Entrées :                                        */
/* c : matrice des capacités des arcs du réseau     */
/* f : matrice des flots sur les arcs               */
/* n : nombre de noeuds du réseau                   */
/* s : sommet source                                */
/* t : sommet destination                           */
/* visite : tableau permettant de marquer les       */
/* sommets visites				                          */
/****************************************************/
/* Sorties : 					                              */
/* - ch : chaîne augmentante de s à t        	      */
/* (s'il en existe)                                 */
/* - La fonction renvoie vrai si une chaîne 	      */
/* augmentante a été trouvée et faux sinon	        */
/****************************************************/
bool chaineaugmentante(int* c[], int* f[], int n, int ch[], int s, int t, bool visite[]) {

    if (s == t)
        return true;
    visite[s] = true;

    for (int i = 0; i < n; i++) {
        if (!visite[i] && c[s][i] - f[s][i] > 0) {
            ch[i] = s;

            if (chaineaugmentante(c, f, n, ch, i, t, visite))
                return true;
        }
    }

    return false;
}

/****************************************************/
/* Entrées :                                        */
/* c : matrice des capacités des arcs du réseau     */
/* f : matrice des flots sur les arcs               */
/* n : nombre de noeuds du réseau                   */
/* s : sommet source                                */
/* t : sommet destination                           */
/* ch : chaîne augmentante de s à t                 */
/* Sortie : valeur d'augmentation du flot           */
/****************************************************/
int increment(int* c[], int* f[], int n, int ch[], int s, int t)
{
    cout << "test increment" << endl;
    
    int incr = 999;

    int i = t;
    while (i != s) {
        int j = ch[i];
        incr = min(incr, c[j][i] - f[j][i]);
        i = j;
    }

    i = t;
    while (i != s) {
        int j = ch[i];
        f[j][i] += incr;
        f[i][j] -= incr;
        i = j;
    }
    return incr;
}


/****************************************************/
/* Entrées :                                        */
/* c : matrice des capacités des arcs du réseau     */
/* f : matrice des flots sur les arcs               */
/* n : nombre de noeuds du réseau                   */
/* s : sommet source                                */
/* t : sommet destination                           */
/* Sortie : Flot Max de s à t                       */
/****************************************************/
int fordfulkerson(int* c[], int* f[], int n, int s, int t)
{
    int ch[] = {-1, -1, -1, -1, -1, -1};
    bool visite[] = {false, false, false, false, false, false};
    for (int i = 0; i < n; i++) {
        visite[i] = false;
    }
    
    int flotmax = 0;
    while (chaineaugmentante(c, f, n, ch, s, t, visite)) {
        int incr = increment(c, f, n, ch, s, t);
        flotmax += incr;
        for (int i = 0; i < n; i++) {
            visite[i] = false;
        }
    }
    
    cout << "flotmax = " << flotmax << endl;
    
	return(0);
}



int main() {

    cout << "Écrire dans le main vos propres tests" << endl;
    
    int matrice1[6][6] = {{0,6,6,0,0,0},{6,0,0,5,0,0},
                          {6,0,0,4,3,0},{0,5,4,0,0,7},
                          {0,0,3,0,0,4},{0,0,0,7,4,0}
     };
                
    int matrice2[6][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},
                          {0,0,0,0,0,0},{0,0,0,0,0,0},
                          {0,0,0,0,0,0},{0,0,0,0,0,0}
     };
                         
    int* c[] = {&matrice1[0][0], &matrice1[1][0], &matrice1[2][0], &matrice1[3][0], &matrice1[4][0], &matrice1[5][0]};
    int* f[] = {&matrice2[0][0], &matrice2[1][0], &matrice2[2][0], &matrice2[3][0], &matrice2[4][0], &matrice2[5][0]};

    fordfulkerson(c,f,6,0,5);
    
    affichage(c,f,6);
}
