public class SavingsAccount extends BankAccount{
    private double interestRate;

    public SavingsAccount(double initialAmount, double rate){
        super(initialAmount);
        this.interestRate = rate;
    }

    public double getInterestRate(){
        return this.interestRate;
    }
    
    public void calculateInterest(){
        double interest = this.interestRate * super.getBalance();
        super.deposit(interest);
    }

    public String toString(){
        return "SavingsAccount: balance $" + super.getBalance() + ", interest rate " + getInterestRate();
    }
    public static void main(String[] args) {
        SavingsAccount myAccount = new SavingsAccount(100.0,0.15);
	    myAccount.calculateInterest();
	    System.out.println(myAccount.toString());
    }
}