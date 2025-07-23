#include<iostream>
#include<string>
using namespace std;
 class vehicle{
 	string company;
 	string model;
 	int year;
 	int count =0;
 	public:
 	
 		vehicle(){
 			company = "Honda";
 			model = "Civic";
 			year = 2023;
 				count++;
 		
		 }
		 vehicle(string comp, string mod, int yr){
		 	company = comp;
		 	model = mod;
		 	year = yr;
		 	count++;
		 	
		 }
		  void showVehicle(){
		 	cout<<"===========Vehicle Info==========="<<endl;
		 	cout<<"Company: "<<company<<endl;
		 	cout<<"Model: "<<model<<endl;
		 	cout<<"Year: "<<year<<endl;
		 	cout<<"-----------------------------------"<<endl;
		 	cout<<"Total Registerd Vehicals: "<<count<<endl;
		 }
 };
 int main(){
 	vehicle v1;
 	vehicle v2("Toyota", "Camry", 2022);
 	vehicle v3("Suzuki", "Swift", 2020);
 	vehicle v4("Hyundai", "SOnata", 2024);
 	v1.showVehicle();
 	v2.showVehicle();
 	v3.showVehicle();
 	v4.showVehicle();
 	return 0;
 }