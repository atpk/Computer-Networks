#include<bits/stdc++.h>
using namespace std;

int main(int argc, char** argv)
{
// argv[14] is string file
    ofstream fout (argv[14]);

// Set MSS value to 1KB
    const double MSS = 1;
// Set RWS value to  1 MB
    const double RWS = 1000;
// ssthresh is set to 2.5 KB
    double ssthresh = 2; 

    double ki, km, kn, kf, ps;
    int n;
    
// Initialize the values
    ki = stod(argv[2]);
    km = stod(argv[4]);
    kn = stod(argv[6]);
    kf = stod(argv[8]);
    ps = stod(argv[10]);
    n = stoi(argv[12]);

    double CW = ki * MSS * 1.0;

// new line for CW
    fout << "0 " << CW << endl;

// number of segments
    const int NOS = n;

    for(int i = 0; i < NOS; i++){
        int N = ceil(CW/MSS);
        for (int i = 0; i < N; i++) {
            double randNumber = (1.0*(rand()%10))/10;
            if (randNumber < ps) {
                ssthresh = CW/2;
                CW = max((double)4, kf*CW);
            }
            else {
                // randNumber >= ps
                if (CW < ssthresh) {
                    CW = min(CW + km*MSS, RWS);
                }
                else {
                    CW = min(CW + kn*MSS*MSS/CW, RWS);
                }
            }
        }
        fout << i+1 << " " << CW << '\n';
    }

    return 0;
}