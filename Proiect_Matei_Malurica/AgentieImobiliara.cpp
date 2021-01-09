#include<iostream>
#include<string>
using namespace std;

class Imobil {
	const int idImobil;
	static int nrImobile;
	char* adresa;
 	const int an_constructie;
	int nr_camere;
	float* suprafataPeCamera;
	static int comision;
	enum tipImobil{Apartament, Garsoniera, Casa, Vila, SpatiuComercial, SpatiuIndustrial, SpatiuBirouri};

public:
	
	
	Imobil() : idImobil(nrImobile++), an_constructie(2000){
		this->adresa = new char[strlen("Necunoscuta") + 1];
		strcpy(this->adresa, "Necunoscuta");
		nr_camere = 0;
		suprafataPeCamera = NULL;
		
	}

	Imobil(const char* adresa, const int an, int nrCamere, float* suprafete) : idImobil(nrImobile++), an_constructie(an) {
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
		this->nr_camere = nrCamere;
		this->suprafataPeCamera = new float[nr_camere];
		for (int i = 0; i < nr_camere; i++) {
			this->suprafataPeCamera[i] = suprafete[i];
		}
	}

	Imobil(const Imobil& imb):idImobil(nrImobile++), an_constructie(imb.an_constructie) {
		this->adresa = new char[strlen(imb.adresa) + 1];
		strcpy(this->adresa, imb.adresa);
		this->nr_camere = imb.nr_camere;
		this->suprafataPeCamera = new float[imb.nr_camere];
		for (int i = 0; i < imb.nr_camere; i++) {
			this->suprafataPeCamera[i] = imb.suprafataPeCamera[i];
		}
	}

	Imobil operator=(const Imobil& imb) {
		if (this->adresa != NULL) {
			delete[] this->adresa;
		}
		this->adresa = new char[strlen(imb.adresa) + 1];
		strcpy(this->adresa, imb.adresa);
		this->nr_camere = imb.nr_camere;
		this->suprafataPeCamera = new float[imb.nr_camere];
		for (int i = 0; i < imb.nr_camere; i++) {
			this->suprafataPeCamera[i] = imb.suprafataPeCamera[i];
		}
		return *this;
	}


	friend ostream& operator<<(ostream& out, Imobil im);
	friend istream& operator>>(istream& in, Imobil& im);

	float calculeazaSuprafataTotala() {
		float supr = 0;
		for (int i = 0; i < nr_camere; i++) {
			supr += suprafataPeCamera[i];
		}
		cout << "Suprafata totala este: " <<supr<< endl;
		return supr;
	}

	bool operator ==(const Imobil& im) {
		if (this->an_constructie == im.an_constructie) {
			cout << "Cele 2 imobile au acelasi an de constructie"<<endl;
		}
		return true;
	}

	bool operator>(const Imobil& im) {
		float supr1 = 0;
		for (int i = 0; i < nr_camere; i++) {
			supr1 += suprafataPeCamera[i];
		}

		float supr2 = 0;
		for (int i = 0; i < im.nr_camere; i++) {
			supr2 += im.suprafataPeCamera[i];
		}

		if (supr1 > supr2) {
			cout << "Primul imobil are suprafata mai mare"<<endl;
		}
		else {
			cout << "Al doilea imobil are suprafata mai mare" << endl;
		}
		return 0;
	}

	~Imobil() {
		if (adresa) {
			delete[] adresa;
		}
		if (suprafataPeCamera) {
			delete[] suprafataPeCamera;
		}
	}
};

ostream& operator<<(ostream& out, Imobil im) {
	out << "----------"<<im.idImobil<<"----------" << endl;
	out << "Adresa: " << im.adresa << endl;
	out << "An constructie: " << im.an_constructie << endl;
	out << "Numar camere: " << im.nr_camere<<endl;
	out << "Suprafata fiecarei camere: " << endl;
	for (int i = 0; i < im.nr_camere; i++) {
		out << im.suprafataPeCamera[i] << " "<<endl;
	}
	out <<"==========================" <<endl;
	return out;
}

istream& operator>>(istream& in, Imobil& im) {
	cout << "Introduceti datele referitoare la imobilul ce doriti sa-l adaugati: "<<endl;
	
	cout << "Introduceti adresa: "<<endl;
	char aux2[30];
	in.getline(aux2, 30);
	if (im.adresa != NULL) {
		delete[] im.adresa;
	}
	im.adresa = new char[strlen(aux2) + 1];
	strcpy(im.adresa, aux2);

	//cout << "Introduceti anul constructiei: " << endl;
	//in >> im.an_constructie;
	cout << "Introduceti numarul de camere: " << endl;
	in >> im.nr_camere;

	cout << "Introduceti suprafata fiecarei camere: " << endl;
	im.suprafataPeCamera = new float[im.nr_camere];
	for (int i = 0; i < im.nr_camere; i++) {
		cout << "Suprafata camera: ";
		in >> im.suprafataPeCamera[i];
	}
	return in;
}

int Imobil::comision = 3;
int Imobil::nrImobile = 0;

class AgentImobiliar {
	char* numeAgent;
	string numarTelefon;
	string email;
	int nrAnunturiActive;
	double rating;

public:
	AgentImobiliar(const char* nume, string nrTel, string email, int nrAnunturi, double rating) {
		this->numeAgent = new char[strlen(nume) + 1];
		strcpy(numeAgent, nume);
		this->numarTelefon = nrTel;
		this->email = email;
		this->nrAnunturiActive = nrAnunturi;
		this->rating = rating;
	}

	friend ostream& operator<<(ostream& out, AgentImobiliar ai);
};

ostream& operator<<(ostream& out, AgentImobiliar ai) {
	out << "==========================" << endl;
	out << "Nume agent: " << ai.numeAgent << endl;
	out << "Numar Telefon: " << ai.numarTelefon << endl;
	out << "Email: " << ai.email << endl;
	out << "Numar anunturi active " << ai.nrAnunturiActive << endl;
	out << "Rating: "<< ai.rating<< endl;
	out << "==========================" << endl;
	return out;
}





int getInput() {
	int input;
	cin >> input;
	return input;
}


void showOptions(){
	cout << "Bine Ati Venit! Pentru a efectua o operatie, selectati din lista de mai jos:";
	cout << endl << "<---------------------------->" << endl;
	cout << endl << "      Main Menu   " << endl;
	cout << endl << "<---------------------------->" << endl;
	cout << "1-Adauga anunt nou " << endl;
	cout << "2-Afiseaza imobile de vanzare " << endl;
	cout << "3-Afiseaza agenti imobiliari " << endl;
	cout << "\n" << endl;
}

void main() {

	showOptions();

	int input = 0;

	float suprafeteImobil1[] = { 5.2, 8, 10 };
	Imobil imobil1("Splaiul Unirii, nr3", 2010, 3, suprafeteImobil1);

	float suprafeteImobil2[] = { 7, 4 };
	Imobil imobil2("Tineretului, nr.24A", 2010, 2, suprafeteImobil2);

	Imobil imobil3;
	Imobil imobil4;
	Imobil imobil5;
	

	AgentImobiliar agent1("Georgescu Teodor", "0732131423", "georgescut@imob.ro", 6, 4.5);
	AgentImobiliar agent2("Mihaescu Lucian", "0721323908", "mihalucian@imob.ro", 3, 4.2);
	AgentImobiliar agent3("Teodoroiu Cristian", "0727323757", "cristianth@imob.ro", 2, 3.8);
	AgentImobiliar agent4("Nanescu Iulian", "0765321344", "naniulian@imob.ro", 9, 4.8);

	do {
		input = getInput();
		switch (input)
		{
		case 1:
			cout << "Introduceti datele mai jos: " << endl;
			cin >> imobil3;
			cout << "Informatiile introduse de dumneavoastra sunt: " << endl;
			cout << imobil3;
			cout << "Va multumim! In scurt timp veti fi contactat de un agent imobiliar la numarul de telefon.	" << endl;
			
			break;
		case 2:
			cout << imobil1;
			cout << imobil2;
			break;
		case 3:
			cout << agent1;
			cout << agent2;
			cout << agent3;
			cout << agent4;
			break;
		default:
			break;
		}
	} while (input != 0);

	
	/*
	Imobil imobil1;
	float suprafeteImobil2[] = { 5.2, 8, 10 };
	Imobil imobil2("Popescu", "Splaiul Unirii, nr3", 2010, 3, suprafeteImobil2);

	float suprafeteImobil3[] = { 7, 4 };
	Imobil imobil3("Ionescu", "Tineretului, nr.24A", 2010, 2, suprafeteImobil3);

	cout << imobil2;
	Imobil imobil4;
	//cin >> imobil4;

	imobil2.calculeazaSuprafataTotala();
	imobil2 > imobil3;
	imobil2 == imobil3;
	*/
}