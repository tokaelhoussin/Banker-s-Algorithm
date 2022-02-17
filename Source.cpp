#include<iostream>
#include<string>
#include <cstdlib>
using namespace std;
int main(){
	int n, m, ind=0, counter=0, x,terminate=0;
	int request;
	cout << "Enter the number of processes:"<<"\n";
	cin >> n; 
	cout << "Enter the number of resources:"<<"\n";
	cin >> m;
	//allocation matrix
	int* alloc=new int [n*m];
	cout << "Enter the allocation matrix:"<<"\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> *(alloc + i*m + j);
		}
	}
	//max matrix
	int* max = new int[n*m];
	cout << "Enter the max matrix:"<<"\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> *(max + i*m + j);
		}
	}
	//available matrix
	int* avail= new int[m]; 
	cout << "Enter the avialable matrix:" << "\n";
	for (int i = 0; i < m; i++) {
		
		cin >> avail[i];
	}
	//need matrix calculation
	int* need = new int[n*m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			 *(need + i*m + j)= *(max + i*m + j)- *(alloc + i*m + j);
		}
	}
	//need matrix output
	for (int i = -1; i < n; i++) 
	{
		for (int j = -1; j < m; j++) {
			if (i == -1 && j == -1)
				cout << "   ";
			else if (i == -1)
				cout << "R" << j << " ";
			else if (j == -1)
				cout << "P" << i<<" ";
			else
			    cout << *(need + i*m + j) << "  ";        // or (A + i*N)[j])
		}
		cout << endl;
	}
	cout << "Enter 1 for Safe state sequence or 2 for immediate request safe sequence:"<<"\n";
	cin >> request;
	int* work = new int[m];
	int* finish = new int[n];
	int* ans = new int[n];
	int* Request = new int[m];

	
	if (request == 1) {
		for (int i = 0; i < n; i++) {
			finish[i] = 0;
		}
		for (int i = 0; i < m; i++) {
			work[i] = avail[i];
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				if (finish[i] == 0) {

					int flag = 0;
					for (int j = 0; j < m; j++) {
						if (*(need + i*m + j) > work[j]) {
							flag = 1;
							break;
						}
					}

					if (flag == 0) {
						ans[ind++] = i;
						for (int y = 0; y < m; y++)
							work[y] += *(alloc + i*m + y);
						finish[i] = 1;
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (finish[i] == 1)
				counter++;
		}
		if (counter == n) {
			cout << "Yes, Safe state <";
			for (int i = 0; i < n - 1; i++)
				cout << " P" << ans[i] << ",";
			cout << " P" << ans[n - 1] << ">" << endl;
		}

		else {
			cout << "No" << endl;
		}
	}
	

	else if (request == 2) {
		cout << "Enter the requested process:" << endl;
		cout << "(note:The processes is 0, 1, 2,....n)" << endl;
		cin >> x;
		cout << "Enter the request" << endl;
		for (int i = 0; i < m; i++) {
			cin >> Request[i];
		}
		for (int i = 0; i < m; i++) {
			if (Request[i] <= *(need + x*m + i)) {
				if (Request[i] <= avail[i]) {
					avail[i] = avail[i] - Request[i];
					*(alloc + x*m + i) = *(alloc + x*m + i) + Request[i];
					*(need + x*m + i) = *(need + x*m + i) - Request[i];
					//cout << *(need + x + i) << " ";
				}
				else {
					cout << "No" << endl;
					terminate = 1;
					break;
				}
			}
			else {
				cout << "No" << endl;
				terminate = 1;
				break;
			}
		}
		if (terminate == 0) {
			for (int i = 0; i < n; i++) {
				finish[i] = 0;
			}
			for (int i = 0; i < m; i++) {
				work[i] = avail[i];
			}
			for (int k = 0; k < n; k++) {
				for (int i = 0; i < n; i++) {
					if (finish[i] == 0) {

						int flag = 0;
						for (int j = 0; j < m; j++) {
							if (*(need + i*m + j) > work[j]) {
								flag = 1;
								break;
							}
						}

						if (flag == 0) {
							ans[ind++] = i;
							for (int y = 0; y < m; y++)
								work[y] += *(alloc + i*m + y);
							finish[i] = 1;
						}
					}
				}
			}
			for (int i = 0; i < n; i++) {
				if (finish[i] == 1)
					counter++;
			}
			if (counter == n) {
				cout << "Yes request can be granted with safe state, Safe state <P" << x << "req";
				for (int i = 0; i < n - 1; i++)
					cout << " P" << ans[i] << ",";
				cout << " P" << ans[n - 1] << ">" << endl;
			}

			else {
				cout << "No" << endl;
			}
		}
	}
	delete[] alloc;
	delete[] max;
	delete[] avail;
	delete[] need;
	delete[] work;
	delete[] finish;
	delete[] ans;
	delete[] Request;
	system("pause");
	return 0;
}