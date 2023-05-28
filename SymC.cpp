// SymC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "Conveyor.h"

using namespace std;

void showCV(int CN,Conveyor& CV) 
{
	vector<bool> sQ = CV.getStateQ();
	vector<bool> cQ = CV.getChangeQ();
	cout << "Conveyor " << CN << ": ";
	if (cQ[0] && !sQ[0]) cout << " STOP state: ";
	if (cQ[0] && sQ[0]) cout << " START state: ";
	for (size_t i=0;i<cQ.size();i++)
		if (cQ[i]) cout << "Q" << i<< ":" << (sQ[i]?"on":"off")<<" ";
	vector<int> sI = CV.getStateI();
	vector<bool> cI = CV.getChangeI();
	for (size_t i = 0; i < cI.size(); i++)
		if (cI[i]) cout << "I" << i<< ":"<<sI[i]<<" "; 
	for (int x : CV.getStateI())
		cout << x << ","; 
	cout << endl;
}

int main()
{
	// I0,I1 - container
	// I2 - medicine
	// I3,I4 - container with medicine
	// Q - conveyor: main, container source, tablet source, ready box
	Conveyor CV1,CV2;
	// Включение Q0 если есть в I0
	CV1.addState(cState({ 0,0,0,0 }, { NN, 0,DC, 0,DC }, { 1,0,0,0 }, { 0,0,0,0,0 })); 
	// Включение если тара на линии и есть в I1
	CV1.addState(cState({ 0,0,0,0 }, { DC, 1,NN, 0,DC }, { 1,0,0,0 }, { 0,0,0,0,0 })); 
	// Включение если продукт на линии и есть место в I4
	CV1.addState(cState({ 0,0,0,0 }, { DC, 0,DC, 1,NN }, { 1,0,0,0 }, { 0,0,0,0,0 }));
	// Цикл производства
	CV1.addState(cState({ 1,0,0,0 }, { NN, 0,DC, 0,DC }, { 1,1,0,0 }, { 0,0,0,0,0 })); // Открывает Q1
	CV1.addState(cState({ 1,1,0,0 }, { NN, 0,DC, 0,DC }, { 1,0,0,0 }, { -1,1,0,0,0 })); // Заготовка из I0 в I1, закрывает Q1
	CV1.addState(cState({ 1,0,0,0 }, { DC, 1,NN, 0,DC }, { 1,0,1,0 }, { 0,0,0,0,0 })); // Q2
	CV1.addState(cState({ 1,0,1,0 }, { DC, 1,NN, 0,DC }, { 1,0,0,0 }, { 0,-1,-1,1,0 })); // Заготовка из I1+I2 в I3, закрывает Q2
	CV1.addState(cState({ 1,0,0,0 }, { DC, 0,DC, 1,NN }, { 1,0,0,1 }, { 0,0,0,0,0 })); // Открывает Q3
	CV1.addState(cState({ 1,0,0,1 }, { DC, 0,DC, 1,NN }, { 1,0,0,0 }, { 0,0,0,-1,-1 })); // Заготовка из I3 в I4, закрывает Q3
	// Останов при опустошении или заполнении
	CV1.addState(cState({ 1,0,0,0 }, {  0,  0, DC, 0,DC }, { 0,0,0,0 }, { 0,0,0,0,0 })); 
	CV1.addState(cState({ 1,0,0,0 }, { DC, DC,  0, 0,DC }, { 0,0,0,0 }, { 0,0,0,0,0 })); 
	CV1.addState(cState({ 1,0,0,0 }, { DC, DC, DC,DC, 0 }, { 0,0,0,0 }, { 0,0,0,0,0 })); 
	// Останов ленты при недопустимом состояние
	CV1.addState(cState({ 1,0,0,0 }, { DC,  1, DC, 1,DC }, { 0,0,0,0 }, { 0,0,0,0,0 }));

	// Конвейер 2
	CV2.addState(cState({ 0,0,0,0 }, { NN, 0,DC, 0,DC }, { 1,0,0,0 }, { 0,0,0,0,0 }));
	CV2.addState(cState({ 0,0,0,0 }, { DC, 1,NN, 0,DC }, { 1,0,0,0 }, { 0,0,0,0,0 }));
	CV2.addState(cState({ 0,0,0,0 }, { DC, 0,DC, 1,NN }, { 1,0,0,0 }, { 0,0,0,0,0 }));
	CV2.addState(cState({ 1,0,0,0 }, { NN, 0,DC, 0,DC }, { 1,1,0,0 }, { 0,0,0,0,0 })); 
	CV2.addState(cState({ 1,1,0,0 }, { NN, 0,DC, 0,DC }, { 1,0,0,0 }, { -1,1,0,0,0 }));
	CV2.addState(cState({ 1,0,0,0 }, { DC, 1,NN, 0,DC }, { 1,0,1,0 }, { 0,0,0,0,0 })); 
	CV2.addState(cState({ 1,0,1,0 }, { DC, 1,NN, 0,DC }, { 1,0,0,0 }, { 0,-1,-1,1,0 }));
	CV2.addState(cState({ 1,0,0,0 }, { DC, 0,DC, 1,NN }, { 1,0,0,1 }, { 0,0,0,0,0 }));
	CV2.addState(cState({ 1,0,0,1 }, { DC, 0,DC, 1,NN }, { 1,0,0,0 }, { 0,0,0,-1,-1 }));
	CV2.addState(cState({ 1,0,0,0 }, { 0,  0, DC, 0,DC }, { 0,0,0,0 }, { 0,0,0,0,0 }));
	CV2.addState(cState({ 1,0,0,0 }, { DC, DC,  0, 0,DC }, { 0,0,0,0 }, { 0,0,0,0,0 }));
	CV2.addState(cState({ 1,0,0,0 }, { DC, DC, DC,DC, 0 }, { 0,0,0,0 }, { 0,0,0,0,0 }));
	CV2.addState(cState({ 1,0,0,0 }, { DC,  1, DC, 1,DC }, { 0,0,0,0 }, { 0,0,0,0,0 }));

	int I0, I2, I4;
	cout << "Continer 1 (I0 I2 I4): "; 
	cin >>I0 >>I2 >> I4;
	CV1.setState({ 0,0,0,0 }, { I0, 0, I2, 0, I4 }); 
	cout << "Continer 2 (I0 I2 I4): ";
	cin >> I0 >> I2 >> I4;
	CV2.setState({ 0,0,0,0 }, { I0, 0, I2, 0, I4 }); 

//	CV1.setState({ 0,0,0,0 }, { 1, 1, 7, 0, 10 });
// CV2.setState({ 0,0,0,0 }, { 1, 0, 7, 1, 10 });

	showCV(1, CV1);
	showCV(2, CV2);
	bool b1 = true, b2 = true;
	while (b1 || b2)
	{
		b1 = CV1.step();
		b2 = CV2.step();
		showCV(1, CV1);
		showCV(2, CV2);
	}

}
