#include <bits/stdc++.h>
using namespace std;

/*
We are a currency exchange that maintains the current exchange rates between currencies. A user can come to us with some amount in one currency and request the equivalent amount in a different currency. Given a list of exchange rates between currencies, write a function that calculates currency rate between any 2 currencies.
Example -
(GBP, EUR, 10) - read as "1 GBP equals 10 EUR"
(EUR, USD, 1.1) - "1 EUR equals 1.1 USD"
(10 GBP, USD) => ? - "10 GBP equals how many USD?"
Answer: 110
 Explanation: 10 GBP = 10 x (10 EUR) = 10 x (10 x (1.1 USD)) = 110 USD
Example 2 -
 (GBP, EUR, 10) - read as "1 GBP equals 10 EUR"
 (EUR, USD, 1.1) - "1 EUR equals 1.1 USD"
 (USD, JPY, 108.3)
 (10 GBP, JPY) => ? - "10 GBP equals how many JPY?"
Answer: 11913
 Explanation: 10 GBP = 10 x (10 EUR) = 10 x (10 x (1.1 USD)) = 10 x (10 x(1.1 x (108.336 JPY))) = 11913 JPY
Follow up question:
what if graph is not connected? ans - maintain a commonBaseCurrency; example dollar and store the dollar equivalent of each currency


*/

// assumption : we have dollar equivalents of all currencies
// two systems / classes : 1. ExchangeRate (has currencyToDollarMap()) - addCurrency, removeCurrency, getDollarEquivalentOfCurrency()
// 2. CurrencyExchange : getExchangedCurrency(value, sourceCurrency, targetCurrency)

class Currency {
private:
	string code;
public:
	Currency(string code) : code(code) {}
	string getCode()
	{
		return(code);
	}
};

class ExchangeRates {
private:
	map<Currency*, vector<pair<Currency*, double > > > rateMap;
	double getExchangeRate(Currency *source, Currency *target)
	{
		queue<pair<Currency*, double > > q;
		set<Currency*> visited;
		visited.insert(source);
		q.push({source, 1.0});
		while(!q.empty())
		{
			auto current = q.front().first;
			double rate = q.front().second;
			q.pop();
			if (current == target)
				return(rate);
			for (auto targetCurr: rateMap[current])
			{
				if (visited.find(targetCurr.first) == visited.end()){
					q.push({targetCurr.first, rate*targetCurr.second});
					visited.insert(targetCurr.first);
				}
			}
		}
		return(-1);
	}
public:
	ExchangeRates() {}
	void addCurrency(Currency *source, Currency *target, double rate)
	{
		rateMap[source].push_back(pair<Currency*, double>{target, rate});
		rateMap[target].push_back(pair<Currency*, double>{source, 1.0/rate});
	}
	double convert(Currency *source, Currency *target, double value)
	{
		if (source == target)
			return(value);
		double rate = getExchangeRate(source, target);
		if (rate == -1)
		{
			cout<<"Cannot be converted\n";
			return(0.0);
		}	
		return(value * rate);
	}
};

int main() {
	Currency USD("USD");
	Currency EUR("EUR");
	Currency GBP("GBP");
	Currency JPY("JPY");
	
	ExchangeRates exchange;
	exchange.addCurrency(&GBP, &EUR, 10.0);
	exchange.addCurrency(&EUR, &USD, 1.1);
	exchange.addCurrency(&USD, &JPY, 108.3);
	
 	cout<<exchange.convert(&GBP, &USD, 10)<<endl;
 	
 	cout<<exchange.convert(&GBP, &JPY, 10)<<endl;
	return 0;
}