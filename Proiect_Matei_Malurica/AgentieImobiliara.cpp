#include<iostream>
#include<string>
using namespace std;

class Imobil {
public:
	const int idImobil;
	static int nrImobile;
	char* adresa;
 	const int an_constructie;
	int nr_camere;
	float* suprafataPeCamera;
	static int comision;
	

public:
	
	int getidImobil() {
		return this->idImobil;
	}

	int getNrImobile() {
		return this->nrImobile;
	}

	char* getAdresa() {
		return this->adresa;
	}

	void setAdresa(char* adresa) {
		if (adresa != NULL) {
			delete[] adresa;
		}
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
	}

	int getAnConstructie() {
		return this->an_constructie;
	}

	int getNrCamere() {
		return this->nr_camere;
	}

	void setNrCamere(int nrCamere) {
		nr_camere = nrCamere;
	}

	float* getSuprafataPeCamera() {
		return suprafataPeCamera;
	}

	void set_preturi(float* vector, int nrCamere) {
		if (nrCamere > 1) {
			if (suprafataPeCamera)
				delete[] suprafataPeCamera;
			suprafataPeCamera = new float[nr_camere];
			for (int i = 0; i < nr_camere; i++) {
				suprafataPeCamera[i] = vector[i];
			}
		}
	}
	
	Imobil() : idImobil(nrImobile++), an_constructie(2000){  //constructor fara parametrii
		this->adresa = new char[strlen("Necunoscuta") + 1];
		strcpy(this->adresa, "Necunoscuta");
		nr_camere = 0;
		suprafataPeCamera = NULL;
		
	}

	Imobil(const char* adresa, const int an, int nrCamere, float* suprafete) : idImobil(nrImobile++), an_constructie(an) {
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
		this->nr_camere = nrCamere;												//constructor cu parametrii
		this->suprafataPeCamera = new float[nr_camere];
		for (int i = 0; i < nr_camere; i++) {
			this->suprafataPeCamera[i] = suprafete[i];
		}
	}

	Imobil(const Imobil& imb):idImobil(nrImobile++), an_constructie(imb.an_constructie) {
		this->adresa = new char[strlen(imb.adresa) + 1];
		strcpy(this->adresa, imb.adresa);
		this->nr_camere = imb.nr_camere;									//constructor de copiere
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
		strcpy(this->adresa, imb.adresa);									//operator =
		this->nr_camere = imb.nr_camere;
		this->suprafataPeCamera = new float[imb.nr_camere];
		for (int i = 0; i < imb.nr_camere; i++) {
			this->suprafataPeCamera[i] = imb.suprafataPeCamera[i];
		}
		return *this;
	}


	friend ostream& operator<<(ostream& out, Imobil im);  //opetator de iesire
	friend istream& operator>>(istream& in, Imobil& im);  //operator de intrare

	friend ofstream& operator<<(ofstream& file, Imobil im); //scriere in fisier

	float calculeazaSuprafataTotala() {
		float supr = 0;
		for (int i = 0; i < nr_camere; i++) {
			supr += suprafataPeCamera[i];
		}
		cout << "Suprafata totala este: " <<supr<< endl;
		return supr;
	}

	bool operator ==(const Imobil& im) {								//operator relational compara o egalitate intre 2 obiecte pe baza anului
		if (this->an_constructie == im.an_constructie) {
			cout << "Cele 2 imobile au acelasi an de constructie"<<endl;
		}
		return true;
	}

	bool operator>(const Imobil& im) {
		float supr1 = 0;
		for (int i = 0; i < nr_camere; i++) {					//opetator rel. > compara suprafetele celor 2 obiecte
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

	operator int()
	{
		return nr_camere;					//operator cast
	}

	float& operator[] (int index) 
	{
		if (index >= 0 && index < nr_camere)        //operator index
			return suprafataPeCamera[index];
		else
			throw new exception("Index out of bounds");
	}




	~Imobil() {
		if (adresa) {
			delete[] adresa;					//destructor
		}
		if (suprafataPeCamera) {
			delete[] suprafataPeCamera;
		}
	}

	virtual float calculeazaPretPeSupfafata() {
		float suprafata = 0;								//functie virtuala in clasa de baza
		for (int i = 0; i < nr_camere; i++) {
			suprafata += suprafataPeCamera[i];
		}
		return suprafata;
	}
};

ostream& operator<<(ostream& out, Imobil im) {
	out << "----------"<<im.idImobil<<"----------" << endl;
	out << "Adresa: " << im.adresa << endl;
	out << "An constructie: " << im.an_constructie << endl;
	out << "Numar camere: " << im.nr_camere<<endl;						//operator de iesire-implementare
	out << "Suprafata fiecarei camere: " << endl;
	for (int i = 0; i < im.nr_camere; i++) {
		out << im.suprafataPeCamera[i] << " "<<endl;
	}
	out <<"==========================" <<endl;
	return out;
}

/* ofstream& operator<<(ofstream& file, Imobil im) {
	file << "----------" << im.idImobil << "----------" << endl;
	file << "Adresa: " << im.adresa << endl;
	file << "An constructie: " << im.an_constructie << endl;
	file << "Numar camere: " << im.nr_camere << endl;						//operator de iesire-implementare
	file << "Suprafata fiecarei camere: " << endl;
	for (int i = 0; i < im.nr_camere; i++) {
		file << im.suprafataPeCamera[i] << " " << endl;
	}
	file << "==========================" << endl;
	return file;
}

*/

istream& operator>>(istream& in, Imobil& im) {
	cout << "Introduceti datele referitoare la imobilul ce doriti sa-l adaugati: "<<endl;
	
	cout << "Introduceti adresa: "<<endl;
	char aux2[30];														//operator de intrare-implementare
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
	char* numeAgent;			//clasa suport
	string numarTelefon;
	string email;
	int nrAnunturiActive;
	double rating;

	

public:
	AgentImobiliar(const char* nume, string nrTel, string email, int nrAnunturi, double rating) {
		this->numeAgent = new char[strlen(nume) + 1];
		strcpy(numeAgent, nume);									//constructor cu parametrii clasa suport
		this->numarTelefon = nrTel;
		this->email = email;
		this->nrAnunturiActive = nrAnunturi;
		this->rating = rating;
	}

	friend ostream& operator<<(ostream& out, AgentImobiliar ai);
};

ostream& operator<<(ostream& out, AgentImobiliar ai) {
	out << "==========================" << endl;
	out << "Nume agent: " << ai.numeAgent << endl;								//supraincarcare operator clasa suport
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

class AgentieImobiliara {

	string denumire;
	int nrAgenti;							//clasa de tip multime de obiecte 
	int nrImobile;
	AgentImobiliar** listaAgenti;
	Imobil** listaImobile;

public:
	AgentieImobiliara() {
		this->denumire = "";
		this->nrAgenti = 0;				//constructor default 
		this->nrImobile = 0;
		this->listaAgenti = NULL;
		this->listaImobile = NULL;
	}

	AgentieImobiliara(const string denumire, int nrAgenti, int nrImobile, AgentImobiliar** listaAgenti, Imobil** listaImobile) {
		this->denumire = denumire;
		this->nrAgenti = nrAgenti;
		this->nrImobile = nrImobile;

		this->listaAgenti = new AgentImobiliar * [this->nrAgenti];
	
		for (int i = 0; i < this->nrAgenti; i++)
			this->listaAgenti[i] = listaAgenti[i];

		this->listaImobile = new Imobil * [this->nrImobile];

		for (int i = 0; i < this->nrImobile; i++)
			this->listaImobile[i] = listaImobile[i];
	}

	string getDenumire() {
		return denumire;
	}

	void setDenumire(string denumire) {
		this->denumire = denumire;
	}

	int getNrAgenti() {
		return this->nrAgenti;
	}

	void setNrAgenti(int nrAgenti) {
		this->nrAgenti = nrAgenti;
	}

	int getNrImobile() {
		return this->nrImobile;
	}

	void setNrImobile(int nrImobile) {
		this->nrImobile = nrImobile;
	}

	friend ostream& operator<<(ostream& out, AgentieImobiliara ai);
	friend istream& operator>>(istream& in, AgentieImobiliara& ai);

	AgentieImobiliara operator+=(Imobil& i) {
		{
			Imobil** listaImobileNoi = new Imobil * [nrImobile + 1];

			for (int i = 0; i < nrImobile; i++)
			{
				listaImobileNoi[i] = listaImobile[i];
			}

			nrImobile++;
			listaImobileNoi[nrImobile - 1] = &i;

			delete[] listaImobile;

			listaImobile = listaImobileNoi;

			return *this;
		}

	}

	void adaugareAgent(AgentImobiliar& ai) {
		AgentImobiliar** listaAgentiNoi = new AgentImobiliar * [nrAgenti + 1];

		for (int i = 0; i < nrAgenti; i++)
		{
			listaAgentiNoi[i] = listaAgenti[i];
		}

		nrAgenti++;
		listaAgentiNoi[nrAgenti - 1] = &ai;

		delete[] listaAgenti;

		listaAgenti = listaAgentiNoi;
	}

	AgentieImobiliara operator-=(Imobil& i)
	{
		if (listaImobile != NULL) {
			Imobil** listaImobileNoi = new Imobil * [nrImobile - 1];

			for (int i = 0; i < nrImobile - 1; i++)
			{
				listaImobileNoi[i] = listaImobile[i];
			}

			nrImobile--;

			delete[] listaImobile;

			listaImobile = new Imobil * [nrImobile];
			listaImobile = listaImobileNoi;
		}
		return *this;
	}

	void eliminareAgent(AgentImobiliar& ai) {
		if (listaAgenti != NULL) {
			AgentImobiliar** listaAgentiNoi = new AgentImobiliar * [nrAgenti - 1];

			for (int i = 0; i < nrAgenti - 1; i++)
			{
				listaAgentiNoi[i] = listaAgenti[i];
			}

			nrAgenti--;

			delete[] listaAgenti;

			listaAgenti = new AgentImobiliar * [nrAgenti];
			listaAgenti = listaAgentiNoi;
		}
	}

	//Operator indexare
	Imobil& operator [](int index)
	{
		if (index >= 0 && index < nrImobile)
			return *listaImobile[index];
		else
			throw - 1; //cod asociat indexului invalid
	}
};

ostream& operator<<(ostream& out, AgentieImobiliara ai) {
	out << "==========================" << endl;
	out << "Nume agentie: " << ai.denumire << endl;
	out << "Numar agenti: " << ai.nrAgenti << endl;
	out << "Numar imobile: " << ai.nrImobile << endl;

	out << "Lista agenti: " << endl;

	for (int i = 0; i < ai.nrAgenti; i++)
		out << *ai.listaAgenti[i] << endl;

	out << "Lista imobile: " << endl;

	for (int i = 0; i < ai.nrImobile; i++)
		out << *ai.listaImobile[i] << endl;

	out << "==========================" << endl;
	return out;
}

istream& operator>>(istream& in, AgentieImobiliara& ai) {
	cout << "Introduceti datele referitoare la agentia ce doriti sa o adaugati: " << endl;

	cout << "Introduceti numele agentiei: " << endl;
	in >> ai.denumire;
	cout << "Introduceti numarul de agenti: " << endl;
	in >> ai.nrAgenti;

	/* ai.listaAgenti = new AgentImobiliar[ai.nrAgenti];
	cout << "Introduceti datele agentilor: " << endl;
	for (int i = 0; i < ai.nrAgenti; i++)
		in >> ai.listaAgenti[i];

	cout << "Introduceti datele imobilelor: " << endl;
	for (int i = 0; i < ai.nrImobile; i++)
		in >> ai.listaImobile[i]; */

		return in;
}

class ImobilVandut :public Imobil {
public:
	float pretVanzare;
	bool rate;

	ImobilVandut(const char* adresa, const int an, int nrCamere, float* suprafete, float pretV, bool rate) :Imobil(adresa, an, nrCamere, suprafete) {
		this->pretVanzare = pretV;
		this->rate = rate;
	}

	friend ostream& operator<<(ostream& out, ImobilVandut iv);

	float calculeazaPretPeSupfafata() {
		float suprafata = 0;
		for (int i = 0; i < nr_camere; i++) {
			suprafata += suprafataPeCamera[i];
		}
		float pret = suprafata / pretVanzare;
		return pret;
	}
};

ostream& operator<<(ostream& out, ImobilVandut iv)
{
	out << (Imobil)iv << endl;
	out << "Afisare locatar: " << iv.pretVanzare << endl;
	out << "Afisare chirie: " << iv.rate << endl;

	return out;
}

class ImobilInchiriat : public Imobil {
public:
	float pretInchirierePeLuna;
	int nrLuniInchiriere;

	ImobilInchiriat(const char* adresa, const int an, int nrCamere, float* suprafete, float pretI, int luni) :Imobil(adresa, an, nrCamere, suprafete) {
		this->pretInchirierePeLuna = pretI;
		this->nrLuniInchiriere = luni;
	}

	friend ostream& operator<<(ostream& out, ImobilInchiriat ii);
};

ostream& operator<<(ostream& out, ImobilInchiriat ii)
{
	out << (Imobil)ii << endl;
	out << "Afisare locatar: " << ii.pretInchirierePeLuna << endl;
	out << "Afisare chirie: " << ii.nrLuniInchiriere << endl;

	return out;
}


void main() {


	AgentImobiliar agent1("Georgescu Teodor", "0732131423", "georgescut@imob.ro", 6, 4.5);
	AgentImobiliar agent2("Mihaescu Lucian", "0721323908", "mihalucian@imob.ro", 3, 4.2);
	AgentImobiliar agent3("Teodoroiu Cristian", "0727323757", "cristianth@imob.ro", 2, 3.8);
	AgentImobiliar agent4("Nanescu Iulian", "0765321344", "naniulian@imob.ro", 9, 4.8);

	float suprafeteImobil1[] = { 5.2, 8, 10 };
	Imobil imobil1("Splaiul Unirii, nr3", 2010, 3, suprafeteImobil1);

	float suprafeteImobil2[] = { 7, 4 };
	Imobil imobil2("Tineretului, nr.24A", 2010, 2, suprafeteImobil2);

	Imobil imobil3;
	Imobil imobil4;
	Imobil imobil5;
	

	AgentImobiliar* listaAg[] = { new AgentImobiliar(agent1), new AgentImobiliar(agent2), new AgentImobiliar(agent3), new AgentImobiliar(agent4) };

	Imobil* listaIm[] = { new Imobil(imobil1), new Imobil(imobil2) };

	string x = "BossCo";

	AgentieImobiliara ai(x, 4, 2, listaAg, listaIm);

	//cout << ai << endl;
	cout << ai[3] << endl;

	//showOptions();


	//

	//int input = 0;

	//float suprafeteImobil1[] = { 5.2, 8, 10 };
	//Imobil imobil1("Splaiul Unirii, nr3", 2010, 3, suprafeteImobil1);

	//float suprafeteImobil2[] = { 7, 4 };
	//Imobil imobil2("Tineretului, nr.24A", 2010, 2, suprafeteImobil2);

	//Imobil imobil3;
	//Imobil imobil4;
	//Imobil imobil5;
	//

	//AgentImobiliar agent1("Georgescu Teodor", "0732131423", "georgescut@imob.ro", 6, 4.5);
	//AgentImobiliar agent2("Mihaescu Lucian", "0721323908", "mihalucian@imob.ro", 3, 4.2);
	//AgentImobiliar agent3("Teodoroiu Cristian", "0727323757", "cristianth@imob.ro", 2, 3.8);
	//AgentImobiliar agent4("Nanescu Iulian", "0765321344", "naniulian@imob.ro", 9, 4.8);

	//AgentImobiliar* listaAg[4] = { new AgentImobiliar(agent1), new AgentImobiliar(agent2), new AgentImobiliar(agent3), new AgentImobiliar(agent4) };

	//Imobil* listaIm[2] = { new Imobil(imobil1), new Imobil(imobil2) };

	//string x = "BossCo";

	//AgentieImobiliara ai(x, 4, 2, listaAg, listaIm);

	//

	//do {
	//	input = getInput();
	//	switch (input)
	//	{
	//	case 1:
	//		cout << "Introduceti datele mai jos: " << endl;
	//		cin >> imobil3;
	//		cout << "Informatiile introduse de dumneavoastra sunt: " << endl;
	//		cout << imobil3;
	//		cout << "Va multumim! In scurt timp veti fi contactat de un agent imobiliar la numarul de telefon.	" << endl;
	//		
	//		break;
	//	case 2:
	//		cout << imobil1;
	//		cout << imobil2;
	//		break;
	//	case 3:
	//		cout << agent1;
	//		cout << agent2;
	//		cout << agent3;
	//		cout << agent4;
	//		break;
	//	case 4:
	//		cout << ai << endl;
	//		cout << ai[1] << endl;
	//	default:
	//		break;
	//	}
	//} while (input != 0);

	//
	///*
	//Imobil imobil1;
	//float suprafeteImobil2[] = { 5.2, 8, 10 };
	//Imobil imobil2("Popescu", "Splaiul Unirii, nr3", 2010, 3, suprafeteImobil2);

	//float suprafeteImobil3[] = { 7, 4 };
	//Imobil imobil3("Ionescu", "Tineretului, nr.24A", 2010, 2, suprafeteImobil3);

	//cout << imobil2;
	//Imobil imobil4;
	////cin >> imobil4;

	//imobil2.calculeazaSuprafataTotala();
	//imobil2 > imobil3;
	//imobil2 == imobil3;
	//*/

}