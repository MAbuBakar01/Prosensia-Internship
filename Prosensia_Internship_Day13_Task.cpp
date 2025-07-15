#include<iostream>
#include<string>
using namespace std;

class BankAccount{
	protected:
	int accNum;
	string accHolderName;
	double balance=0.00;
	public:
		double amount;
		BankAccount(int aN, string name, double bal){
				 accNum = aN;
	             accHolderName = name;
                 balance = bal;
		}
		void deposit(){
			cout<<"Enter Amount to Deposit: "<<endl;
			cin>>amount;
			balance= balance+amount;
			cout<<amount<<" Rs deposited in your account succefully!"<<endl;
			cout<<"============================="<<endl;
			
		}
		void withdraw(){
			cout<<"Enter Amount to withdraw:";
			cin>>amount;
			if(balance<amount){
				cout<<"You don't have enough funds to withdraw!"<<endl;
				cout<<"============================="<<endl;
			}
			else{
				cout<<"Transaction Successful!"<<endl;
					balance= balance-amount;
					cout<<"============================="<<endl;
			}
		
		}
		void displayAccInfo(){
			cout<<"~~~~~~~~Account Details~~~~~~~~~~"<<endl;
			cout<<"Account Number: "<<accNum<<endl;
			cout<<"Account Holder Name: "<<accHolderName<<endl;
			cout<<"Account Balance: "<<balance<<endl;
			cout<<"============================="<<endl;
		}
	
	
};
int main(){
	BankAccount acc1(2345876, "Asad Ullah", 500.98 );
	acc1.deposit();
	acc1.displayAccInfo();
	acc1.withdraw();
	acc1.displayAccInfo();
	return 0;
}