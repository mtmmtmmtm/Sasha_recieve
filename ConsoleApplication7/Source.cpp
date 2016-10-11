#include "Header.h"

using namespace std;

/*UDP_Server serv_port1(8888);				//CREATING PORTS
UDP_Server serv_port2(8080);*/

vector<int> Data_Array_Port1;
vector<int> Data_Array_Port2;
											//INICIALISING SCANNING FOR INCOMING DATA THROUGH DIFFERENT PORTS
/*void func_port1() {
	while (1) {
		serv_port1.get_message();			//GETTING DATA
		Data_Array_Port1 = serv_port1.Result_Array;
		for (int i = 0; i < Data_Array_Port1.size(); i++) {
			cout << Data_Array_Port1[i] << " ";
		}
		cout << "   Порт 8888" << endl;
	}
}

void func_port2() {
	while (1) {
		serv_port2.get_message();			//GETTING DATA
		Data_Array_Port2 = serv_port2.Result_Array;
		for(int i = 0; i < Data_Array_Port2.size(); i++) {
			cout << Data_Array_Port2[i] << " ";
		}
		cout << "   Порт 8080" << endl;
	}
}*/

int main() {
	setlocale(0, "Russian");
	UDP_Start_Server Server("8080, 8888);
	
	return 0;

}